#ifndef NETLIST_STATISTIC_HPP
#define NETLIST_STATISTIC_HPP

#include "netlist_utils.h"

void init(metric_t* m);
void copy(metric_t* dest, metric_t* src);
void add_into(metric_t* dest, metric_t* src);
double distance_to_goal(metric_t* golden_values, metric_t* calculated_values);
void compute_statistics(netlist_t* netlist, int traverse_mark_number);

net_stat_t* get_stats(signal_list_t* input_signals, signal_list_t* output_signals, netlist_t* netlist, int traverse_mark_number);
net_stat_t* get_stats(nnode_t* node, netlist_t* netlist, int traverse_mark_number);
net_stat_t* get_stats(nnet_t* net, netlist_t* netlist, int traverse_mark_number);

net_stat_t* delete_stat(net_stat_t* stat);

#endif // NETLIST_STATISTIC_HPP
