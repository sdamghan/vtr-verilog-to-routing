#include <algorithm>

#include "odin_types.h"
#include "netlist_statistic.h"
#include "vtr_memory.h"

static metric_t* new_metric(void);

static void mark_traversed(nnet_t* net, netlist_t* netlist, int traverse_mark_number);
static void mark_traversed(nnode_t* node, netlist_t* netlist, int traverse_mark_number);

static metric_t* get_upward_stat(nnet_t* net, netlist_t* netlist, int traverse_mark_number);
static metric_t* get_downward_stat(nnet_t* net, netlist_t* netlist, int traverse_mark_number);
static metric_t* get_upward_stat(nnode_t* node, netlist_t* netlist, int traverse_mark_number);
static metric_t* get_downward_stat(nnode_t* node, netlist_t* netlist, int traverse_mark_number);
static metric_t* get_downward_signal_stat(signal_list_t* signals, netlist_t* netlist, int traverse_mark_number);
static metric_t* get_upward_signal_stat(signal_list_t* signals, netlist_t* netlist, int traverse_mark_number);

metric_t* new_metric(void) {
    metric_t* m = (metric_t*)vtr::malloc(sizeof(metric_t));
    init(m);
    return m;
}

void init(metric_t* m) {
    m->min_depth = 0;
    m->max_depth = 0;
    m->avg_depth = 0;
    m->avg_width = 0;
    m->min_fanin = 0;
    m->max_fanin = 0;
    m->min_fanout = 0;
    m->max_fanout = -12;
}

void print_stats(metric_t* m) {
    printf("\n\t%s: %0.4lf\n\t%s: %0.4lf\n\t%s: %0.4lf\n\t%s: %0.4lf\n\t%s: %d\n\t%s: %d\n\t%s: %d\n\t%s: %d\n\n",
           "minimal depth", m->min_depth,
           "maximum depth", m->max_depth,
           "average depth", m->avg_depth,
           "average fan-in", m->avg_width,
           "minimal fan-in", m->min_fanin,
           "maximum fan-in", m->max_fanin,
           "minimal fan-out", m->min_fanout,
           "maximum fan-out", m->max_fanout);
}

void copy(metric_t* dest, metric_t* src) {
    if (dest) {
        init(dest);
        if (src) {
            dest->min_depth = src->min_depth;
            dest->max_depth = src->max_depth;
            dest->avg_depth = src->avg_depth;
            dest->avg_width = src->avg_width;
            dest->min_fanin = src->min_fanin;
            dest->max_fanin = src->max_fanin;
            dest->min_fanout = src->min_fanout;
            dest->max_fanout = src->max_fanout;
        }
    }
}

void add_into(metric_t* dest, metric_t* src) {
    dest->min_depth += src->min_depth;
    dest->max_depth += src->max_depth;
    dest->avg_depth += src->avg_depth;
    dest->avg_width += src->avg_width;

    if (dest->min_fanin == 0) {
        dest->min_fanin = src->min_fanin;
    } else {
        dest->min_fanin = std::min(src->min_fanin, dest->min_fanin);
    }
    dest->max_fanin = std::max(src->max_fanin, dest->max_fanin);

    if (dest->min_fanout == 0) {
        dest->min_fanout = src->min_fanout;
    } else {
        dest->min_fanout = std::min(src->min_fanout, dest->min_fanout);
    }
    dest->max_fanout = std::max(src->max_fanout, dest->max_fanout);
}

inline double circuit_ratio(metric_t* v) {
    return (v->avg_width / v->avg_depth);
}

inline double circuit_effective_ratio(metric_t* v) {
    return (circuit_ratio(v));
}

inline double circuit_area(metric_t* v) {
    return (v->avg_width * v->avg_depth);
}

// will always return a positive value since golden is absolute minimum
// but we use abs() for correctness
inline double circuit_effective_area(metric_t* golden_values, metric_t* calculated_values) {
    return (abs(circuit_area(calculated_values) - circuit_area(golden_values)));
}

// lower is better
// we aim to approach 0
double distance_to_goal(metric_t* golden_values, metric_t* calculated_values) {
    return abs(circuit_effective_ratio(calculated_values) * circuit_effective_area(golden_values, calculated_values));
}

double fitness_calc (netlist_t* netlist, metric_t* m) {
    long long node_count = netlist->total_net_count;
    double area = circuit_area(m);

    double area_efectness = (m->max_depth) / (area*node_count);
    double fan_effectness = (m->max_fanin)+(m->max_fanout);
    // printf("\n\n \t++node_count: %lld\n\t++area: %f\n\t++max_depth: %f\n\t++max_fan-in: %d\n\t++max_fan-out: %d\n\t++area_effectness: %f\n\t++fan_effectness: %f\n\n", 
    //       node_count, area, m->max_depth, m->max_fanin, m->max_fanout, area_efectness, fan_effectness);


    return 1000000 * (area_efectness) / (fan_effectness);
}


static void aggregate(metric_t* dest, metric_t** sources, int source_count, branching_type_e btype) {
    int actual_count = 0;
    init(dest);

    // compute stats from parent
    for (int i = 0; sources && i < source_count; i += 1) {
        metric_t* src = sources[i];
        if (src) {
            actual_count += 1;
            if (dest->min_depth == 0) {
                dest->min_depth = src->min_depth;
            } else {
                dest->min_depth = std::min(src->min_depth, dest->min_depth);
            }
            dest->max_depth = std::max(src->max_depth, dest->max_depth);
            dest->avg_depth += src->avg_depth;
            dest->avg_width += src->avg_width;
        }
    }

    if (actual_count) {
        dest->avg_depth /= actual_count;
        dest->avg_width /= actual_count;
    }

    if (btype == FANIN) {
        for (int i = 0; sources && i < source_count; i += 1) {
        metric_t* src = sources[i];
        if (src) {
            if (dest->min_fanin == 0) {
                dest->min_fanin = src->min_fanin;
            } else {
                dest->min_fanin = std::min(src->min_fanin, dest->min_fanin);
            }
            dest->max_fanin = std::max(src->max_fanin, dest->max_fanin);
        }
    }
    }
    else if (btype == FANOUT) {
        for (int i = 0; sources && i < source_count; i += 1) {
            metric_t* src = sources[i];
            if (src) {
                if (dest->min_fanout == 0) {
                    dest->min_fanout = src->min_fanout;
                } else {
                    dest->min_fanout = std::min(src->min_fanout, dest->min_fanout);
                }
                dest->max_fanout = std::max(src->max_fanout, dest->max_fanout);
            }
        }
    }
}

static void add_net_to_stat(metric_t* dest, int branching_factor, branching_type_e btype) {
    dest->min_depth += 1;
    dest->max_depth += 1;
    dest->avg_depth += 1;
    dest->avg_width += branching_factor;
    if (btype == FANIN) {
        dest->min_fanin  = std::min(dest->min_fanin, branching_factor);
        dest->max_fanin  = std::max(dest->max_fanin, branching_factor);

    } else if (btype == FANOUT) {
        dest->min_fanout = std::min(dest->min_fanout, branching_factor);
        dest->max_fanout  = std::max(dest->max_fanout, branching_factor);
    }
}

static void add_node_to_stat(metric_t* dest, int branching_factor, branching_type_e btype) {
    
    if (btype == FANIN) {
        dest->min_fanin  = std::min(dest->min_fanin, branching_factor);
        dest->max_fanin  = std::max(dest->max_fanin, branching_factor);
        
    } else if (btype == FANOUT) {
        dest->min_fanout = std::min(dest->min_fanout, branching_factor);
        dest->max_fanout  = std::max(dest->max_fanout, branching_factor);

    }
}

static void mark_traversed(nnet_t* net, netlist_t* netlist, int traverse_mark_number) {
    net->traverse_visited = traverse_mark_number;
    netlist->total_net_count += 1;
}

static void mark_traversed(nnode_t* node, netlist_t* /* netlist */, int traverse_mark_number) {
    node->traverse_visited = traverse_mark_number;
}

static metric_t* get_upward_stat(nnet_t* net, netlist_t* netlist, int traverse_mark_number) {
    metric_t* destination = NULL;
    if (net) {
        destination = &(net->stat.upward);

        if (net->traverse_visited != traverse_mark_number) {
            init(destination);

            mark_traversed(net, netlist, traverse_mark_number);
            if (net->driver_pin) {
                metric_t** parent_stat = (metric_t**)vtr::calloc(1, sizeof(metric_t*));
                parent_stat[0] = get_upward_stat(net->driver_pin->node, netlist, traverse_mark_number);
                aggregate(destination, parent_stat, 1, FANIN);
                vtr::free(parent_stat);
            }

            add_net_to_stat(destination, 1, FANIN);
        }
    }
    return destination;
}

static metric_t* get_downward_stat(nnet_t* net, netlist_t* netlist, int traverse_mark_number) {
    metric_t* destination = NULL;
    if (net) {
        destination = &(net->stat.downward);

        if (net->traverse_visited != traverse_mark_number) {
            init(destination);
            mark_traversed(net, netlist, traverse_mark_number);

            if (net->num_fanout_pins) {
                metric_t** child_stat = (metric_t**)vtr::calloc(net->num_fanout_pins, sizeof(metric_t*));
                for (int i = 0; i < net->num_fanout_pins; i++) {
                    if (net->fanout_pins[i]) {
                        child_stat[i] = get_downward_stat(net->fanout_pins[i]->node, netlist, traverse_mark_number);
                    }
                }
                aggregate(destination, child_stat, net->num_fanout_pins, FANOUT);
                vtr::free(child_stat);
            }
            add_net_to_stat(destination, net->num_fanout_pins, FANOUT);
        }
    }
    return destination;
}

static metric_t* get_upward_stat(nnode_t* node, netlist_t* netlist, int traverse_mark_number) {
    metric_t* destination = NULL;
    if (node) {
        destination = &(node->stat.upward);

        if (node->traverse_visited != traverse_mark_number) {
            init(destination);
            mark_traversed(node, netlist, traverse_mark_number);

            if (node->num_input_pins) {
                metric_t** parent_stat = (metric_t**)vtr::calloc(node->num_input_pins, sizeof(metric_t*));
                for (int i = 0; i < node->num_input_pins; i++) {
                    if (node->input_pins[i]) {
                        parent_stat[i] = get_upward_stat(node->input_pins[i]->net, netlist, traverse_mark_number);
                    }
                }
                aggregate(destination, parent_stat, node->num_input_pins, FANIN);
                vtr::free(parent_stat);
            }
            add_node_to_stat(destination, node->num_input_pins, FANIN);
        }
    }
    return destination;
}

static metric_t* get_downward_stat(nnode_t* node, netlist_t* netlist, int traverse_mark_number) {
    metric_t* destination = NULL;

    if (node) {
        destination = &(node->stat.downward);
        if (node->traverse_visited != traverse_mark_number) {
            init(destination);
            mark_traversed(node, netlist, traverse_mark_number);

            if (node->num_output_pins) {
                metric_t** child_stat = (metric_t**)vtr::calloc(node->num_output_pins, sizeof(metric_t*));
                for (int i = 0; i < node->num_output_pins; i++) {
                    if (node->output_pins[i]) {
                        child_stat[i] = get_downward_stat(node->output_pins[i]->net, netlist, traverse_mark_number);
                    }
                }
                aggregate(destination, child_stat, node->num_output_pins, FANOUT);
                vtr::free(child_stat);
            }
            add_node_to_stat(destination, node->num_output_pins, FANOUT);
        }
    }
    return destination;
}

static metric_t* get_downward_signal_stat(metric_t* destination, signal_list_t* signals, netlist_t* netlist, int traverse_mark_number) {
    if (signals) {
        if (signals->count) {
            metric_t** child_stat = (metric_t**)vtr::calloc(signals->count, sizeof(metric_t*));
            for (int i = 0; i < signals->count; i++) {
                if (signals->pins[i]) {
                    // node -> net
                    if (signals->pins[i]->type == OUTPUT) {
                        child_stat[i] = get_downward_stat(signals->pins[i]->net, netlist, traverse_mark_number);
                    }
                    // net -> node
                    else {
                        child_stat[i] = get_downward_stat(signals->pins[i]->node, netlist, traverse_mark_number);
                    }
                }
            }
            aggregate(destination, child_stat, signals->count, FANOUT);
            vtr::free(child_stat);
        }
    }
    return destination;
}

static metric_t* get_upward_signal_stat(metric_t* destination, signal_list_t* signals, netlist_t* netlist, int traverse_mark_number) {
    if (signals) {
        if (signals->count) {
            metric_t** child_stat = (metric_t**)vtr::calloc(signals->count, sizeof(metric_t*));
            for (int i = 0; i < signals->count; i++) {
                if (signals->pins[i]) {
                    // net -> node
                    if (signals->pins[i]->type == INPUT) {
                        child_stat[i] = get_upward_stat(signals->pins[i]->net, netlist, traverse_mark_number);
                    }
                    // node -> net
                    else {
                        child_stat[i] = get_upward_stat(signals->pins[i]->node, netlist, traverse_mark_number);
                    }
                }
            }
            aggregate(destination, child_stat, signals->count, FANIN);

            vtr::free(child_stat);
        }
    }
    return destination;
}

net_stat_t* get_stats(signal_list_t* input_signals, signal_list_t* output_signals, netlist_t* netlist, int traverse_mark_number) {
    net_stat_t* stat = (net_stat_t*)vtr::malloc(sizeof(net_stat_t));
    // we recompute bellow the input since this is were connection can change
    get_downward_signal_stat(&stat->downward, input_signals, netlist, traverse_mark_number);
    // we recompute above the output since this is were connection can change
    get_upward_signal_stat(&stat->upward, output_signals, netlist, traverse_mark_number);
    return stat;
}

net_stat_t* get_stats(nnode_t* node, netlist_t* netlist, int traverse_mark_number) {
    net_stat_t* stat = (net_stat_t*)vtr::malloc(sizeof(net_stat_t));
    copy(&stat->downward, get_downward_stat(node, netlist, traverse_mark_number));
    copy(&stat->upward, get_upward_stat(node, netlist, traverse_mark_number));
    return stat;
}

net_stat_t* get_stats(nnet_t* net, netlist_t* netlist, int traverse_mark_number) {
    net_stat_t* stat = (net_stat_t*)vtr::malloc(sizeof(net_stat_t));
    copy(&stat->downward, get_downward_stat(net, netlist, traverse_mark_number));
    copy(&stat->upward, get_upward_stat(net, netlist, traverse_mark_number));
    return stat;
}

net_stat_t* delete_stat(net_stat_t* stat) {
    if (stat) {
        vtr::free(stat);
        stat = NULL;
    }
    return stat;
}

/*---------------------------------------------------------------------------------------------
 * function: dfs_to_cp() it starts from head and end of the netlist to calculate critical path
 *-------------------------------------------------------------------------------------------*/
void compute_statistics(netlist_t* netlist, int traverse_mark_number) {
    if (netlist) {
        /* start with the primary input list */
        for (int i = 0; i < netlist->num_top_input_nodes; i++) {
            if (netlist->top_input_nodes[i] != NULL) {
                get_downward_stat(netlist->top_input_nodes[i], netlist, traverse_mark_number);
            }
        }

        /* now traverse the ground and vcc pins  */
        get_downward_stat(netlist->vcc_node, netlist, traverse_mark_number);
        get_downward_stat(netlist->pad_node, netlist, traverse_mark_number);
        get_downward_stat(netlist->gnd_node, netlist, traverse_mark_number);

        // increment to get upward stats
        traverse_mark_number += 1;
        // reinit the node count
        netlist->total_net_count = 0;

        bool flag = false;
        metric_t* MAX = NULL;
        for (int i = 0; i < netlist->num_top_output_nodes; i++) {
             
            if (netlist->top_output_nodes[i] != NULL) {
                metric_t* current = get_upward_stat(netlist->top_output_nodes[i], netlist, traverse_mark_number);
                
                if (current != NULL) {
                    if (!flag) {MAX = current; flag=true;}
                    if(current->max_depth > MAX->max_depth)
                        // printf("Stats for Primary Fanout: %s", netlist->top_output_nodes[i]->name);
                        MAX = current;
                }
            }
        }

        print_stats(MAX);
    }
}