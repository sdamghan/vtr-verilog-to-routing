
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MIN_MR 10
// #define MIN_GS 5
// #define MIN_GC 1000
 
#define MAX_MR 100
// #define MAX_GS 15
// #define MAX_GC 20000
 
#define RATE_MR 10
// #define RATE_GS 1
// #define RATE_GC 1000

#define MR_ITER (((MAX_MR - MIN_MR) + RATE_MR) / RATE_MR)
// #define GS_ITER (((MAX_GS - MIN_GS) + RATE_GS) / RATE_GS)
#define GS_ITER 5
// #define GC_ITER (((MAX_GC - MIN_GC) + RATE_GC) / RATE_GC)
#define GC_ITER 8

int GS_ARRAY[GS_ITER]={1,2,4,8,16};
int GC_ARRAY[GC_ITER]={256,512,1024,2048,4096,8192,16384,32768};

FILE *fp = NULL;
char *filename;

struct stats {
    float mutation_rate;
    int generation_size;
    int generation_count;
    int generation_number;
    float fitness;
    int max_fanin;
    int max_fanout;
    int critical_path;
    char* op;
    int op_number;
    int node_count;
    int RCA_number;
    int CSLA_number;
    int BE_CSLA_number;
} Stat;

void init(struct stats* curr_stat){

    curr_stat->mutation_rate = -1;
    curr_stat->generation_size = -1;
    curr_stat->generation_count = -1;
    curr_stat->generation_number = -1;
    curr_stat->fitness = INT_MAX;
    curr_stat->max_fanin = -1;
    curr_stat->max_fanout = -1;
    curr_stat->critical_path = INT_MAX;
    curr_stat->op = (char*)malloc (32*sizeof(char));
    curr_stat->op_number = -1;
    curr_stat->node_count = INT_MAX;
    curr_stat->RCA_number = -1;
    curr_stat->CSLA_number = -1;
    curr_stat->BE_CSLA_number = -1;
}

void copy_stat(struct stats* copy_stat, struct stats* paste_stat) {

    paste_stat->mutation_rate     = copy_stat->mutation_rate;
    paste_stat->generation_size   = copy_stat->generation_size;
    paste_stat->generation_count  = copy_stat->generation_count;
    paste_stat->generation_number = copy_stat->generation_number;
    paste_stat->fitness           = copy_stat->fitness;
    paste_stat->max_fanin         = copy_stat->max_fanin;
    paste_stat->max_fanout        = copy_stat->max_fanout;
    paste_stat->critical_path     = copy_stat->critical_path;
    paste_stat->op                = copy_stat->op;
    paste_stat->op_number         = copy_stat->op_number;
    paste_stat->node_count        = copy_stat->node_count;
    paste_stat->RCA_number        = copy_stat->RCA_number;
    paste_stat->CSLA_number       = copy_stat->CSLA_number;
    paste_stat->BE_CSLA_number    = copy_stat->BE_CSLA_number;
}

void miss_lines (int num) {

    char line[1024];

    for (int i = 0; i < num; i++) 
        fgets(line, sizeof(line), fp);
}

void scan_stat (struct stats* curr_stat) {

    fscanf(fp, "%d,%f,%d,%d,%d,ADD,%d,%d,%d,%d,%d", 
                &curr_stat->generation_number, &curr_stat->fitness, &curr_stat->critical_path, 
                &curr_stat->max_fanin, &curr_stat->max_fanout, /*curr_stat->op,*/ &curr_stat->op_number, 
                &curr_stat->node_count, &curr_stat->RCA_number, &curr_stat->CSLA_number, &curr_stat->BE_CSLA_number);
}

void print_header () {
    printf("%s\n", "benchmark,mutation_rate,generation_size,generation_count,generation_number,fitness,critical_path,max_fanin,max_fanout,ADD,op_number,node_count,RCA_number,CSLA_number,BE_CSLA_number");
}

void print_stat (struct stats* temp) {

    printf("%s,%.3f,%d,%d,", filename,temp->mutation_rate, temp->generation_size, temp->generation_count);
    printf("%d,%f,%d,%d,%d,%s,%d,%d,%d,%d,%d\n", 
            temp->generation_number, temp->fitness, temp->critical_path, temp->max_fanin,
            temp->max_fanout, "ADD"/*first_min_stat->op*/, temp->op_number, temp->node_count,
            temp->RCA_number, temp->CSLA_number, temp->BE_CSLA_number);
}

void extract_top_in_generation_counts () {
    
    struct stats* curr_stat = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gc = (struct stats*)malloc (sizeof(struct stats));
    init(curr_stat);

    printf("\n[INFO]\tMin Critical Paths Among Different Generation Counts:\n\n");
    print_header();

    while( fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count) != EOF ) {
        
        init(min_stat_gc);
        for (int i = 0; i < curr_stat->generation_count; i++) {
        
            scan_stat (curr_stat);

            if ( curr_stat->node_count < min_stat_gc->node_count )
                copy_stat(curr_stat, min_stat_gc);

        }
        miss_lines(1);

        print_stat (min_stat_gc);

        // if (min_stat_gc->generation_count == GC_ARRAY[GC_ITER-1])   printf("\n\n\n\n");
        init(curr_stat);
    }

    free(curr_stat);
    free(min_stat_gc);
}

void extract_top_in_generation_sizes () {
        
    struct stats* curr_stat = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gs = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gc = (struct stats*)malloc (sizeof(struct stats));

    init(curr_stat);

    printf("\n[INFO]\tMin Critical Paths Among Different Generation Sizes:\n\n");
    print_header();

    while ( fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count) != EOF ) {

        init(min_stat_gs);
        for (int j = 0; j < GC_ITER; j++) {

            init(min_stat_gc);
            for (int i = 0; i < curr_stat->generation_count; i++) {
            
                scan_stat (curr_stat);

                if ( curr_stat->node_count < min_stat_gc->node_count )
                    copy_stat(curr_stat, min_stat_gc);
            }
            miss_lines(1);

            if ( min_stat_gc->node_count < min_stat_gs->node_count )
                copy_stat(min_stat_gc, min_stat_gs);

            if (j < GC_ITER-1)
                fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count);
        }

        print_stat (min_stat_gs);

        // if (min_stat_gs->generation_size == GS_ARRAY[GS_ITER-1])   printf("\n\n\n\n");
        init(curr_stat);
    }

    free(curr_stat);
    free(min_stat_gs);
    free(min_stat_gc);
}

void extract_top_in_mutation_rates () {
        
    struct stats* curr_stat = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gs = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gc = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_mr = (struct stats*)malloc (sizeof(struct stats));

    init(curr_stat);

    printf("\n[INFO]\tMin Critical Paths Among Different Mutation Rates:\n\n");
    print_header();

    while ( fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count) != EOF ) {

        init(min_stat_mr);
        for (int k = 0; k < GS_ITER; k++) {
            
            init(min_stat_gs);
            for (int j = 0; j < GC_ITER; j++) {

                init(min_stat_gc);
                for (int i = 0; i < curr_stat->generation_count; i++) {

                    scan_stat (curr_stat);

                    if ( curr_stat->node_count < min_stat_gc->node_count )
                        copy_stat(curr_stat, min_stat_gc);
                }

                miss_lines(1);

                if ( min_stat_gc->node_count < min_stat_gs->node_count )
                    copy_stat(min_stat_gc, min_stat_gs);

                if (j < GC_ITER-1)
                    fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count);
            }

            if ( min_stat_gs->node_count < min_stat_mr->node_count )
                copy_stat(min_stat_gs, min_stat_mr);

            if (k < GS_ITER-1)
                fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count);
        }

        print_stat (min_stat_mr);

        // if (min_stat_mr->mutation_rate == MAX_MR/100)   printf("\n\n\n\n");
        init(curr_stat);
    }

    free(curr_stat);
    free(min_stat_gs);
    free(min_stat_gc);
    free(min_stat_mr);
}

void extract_top_in_general () {
        
    struct stats* curr_stat = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gs = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_gc = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat_mr = (struct stats*)malloc (sizeof(struct stats));
    struct stats* min_stat = (struct stats*)malloc (sizeof(struct stats));
    
    init(curr_stat);

    printf("\n[INFO]\tGeneral MIN Critical Path:\n\n");
    print_header();

    while ( fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count) != EOF ) {

        init(min_stat);
        for (int z = 0; z < MR_ITER; z++) {

            init(min_stat_mr);
            for (int k = 0; k < GS_ITER; k++) {
                
                init(min_stat_gs);
                for (int j = 0; j < GC_ITER; j++) {

                    init(min_stat_gc);
                    for (int i = 0; i < curr_stat->generation_count; i++) {

                        scan_stat (curr_stat);

                        if ( curr_stat->node_count < min_stat_gc->node_count )
                            copy_stat(curr_stat, min_stat_gc);
                    }

                    miss_lines(1);

                    if ( min_stat_gc->node_count < min_stat_gs->node_count )
                        copy_stat(min_stat_gc, min_stat_gs);

                    if (j < GC_ITER-1)
                        fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count);
                }

                if ( min_stat_gs->node_count < min_stat_mr->node_count )
                    copy_stat(min_stat_gs, min_stat_mr);

                if (k < GS_ITER-1)
                    fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count);
            }

            if ( min_stat_mr->node_count < min_stat->node_count )
                    copy_stat(min_stat_mr, min_stat);

            if (z < MR_ITER-1)
                fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count);
                
        }

        print_stat (min_stat);
    }

    free(curr_stat);
    free(min_stat_gs);
    free(min_stat_gc);
    free(min_stat_mr);
}

void create_db () {
    
    struct stats* curr_stat = (struct stats*)malloc (sizeof(struct stats));
    init(curr_stat);

    print_header();

    while( fscanf(fp, "%f,%d,%d", &curr_stat->mutation_rate, &curr_stat->generation_size, &curr_stat->generation_count) != EOF ) {
        
        for (int i = 0; i < curr_stat->generation_count; i++){
                scan_stat(curr_stat);
                print_stat (curr_stat);
        }

        miss_lines(1);
    }

    free(curr_stat);
}

int main (int argc, char* argv[]) {

    if ( argc < 4 ) {
        
        printf("%s%s%s%s%s%s\n", "[ERROR] Few arguments! \n\n",
                                    "Usage:\n",
                                    "\t[-S]\tFind the min critical path through generation counts\n",
                                    "\t[-C]\tFind the min critical path through generation sizes.\n",
                                    "\t[-M]\tFind the min critical path through mutation rates\n",
                                    "\t[-G]\tFind the min critical path through entire configurations\n\n");
        return 1;
    }

    filename = (char*) malloc (20*sizeof(char));
    filename = argv[3];

    fp = fopen(argv[2], "r");

    if ( fp == NULL ) {
        printf("file open error!\n");
        return 1;
    }
    
    switch (argv[1][1]) {
        
        case 'C':
        {
            extract_top_in_generation_counts ();
            break;
        }

        case 'S':
        {
            extract_top_in_generation_sizes ();
            break;
        }

        case 'M':
        {
            extract_top_in_mutation_rates ();
            break;
        }

        case 'G':
        {
            extract_top_in_general ();
            break;
        }

        case 'T':
        {
            create_db ();
            break;
        }

        default:
        {
            printf("%s%s%s%s%s%s\n", "[ERROR] Wrong arguments! \n\n",
                                    "Usage:\n",
                                    "\t[-S]\tFind the min critical path through generation counts\n",
                                    "\t[-C]\tFind the min critical path through generation sizes.\n",
                                    "\t[-M]\tFind the min critical path through mutation rates\n",
                                    "\t[-G]\tFind the min critical path through entire configurations\n\n");
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}
