/*
Copyright (c) 2009 Peter Andrew Jamieson (jamieson.peter@gmail.com)

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PARTIAL_MAP_H
#define PARTIAL_MAP_H

//MEHRSHAD//

#define DEFAULT  0
#define CSLA     1
#define BEC_CSLA 2

struct adder_t {

    short type = DEFAULT;

    signal_list_t *input;
    signal_list_t *output;

    nnode_t *node;
};

adder_t **adders_list;
short* chromosome;

long num_of_adders = 0;

void partial_map_adders(short traverse_number, netlist_t *netlist);
void destroy_adders();
void destroy_adder_cloud (adder_t *adder);
//MEHRSHAD//

// PROTOTYPES
void partial_map_top(netlist_t *netlist);
void instantiate_add_w_carry(short type, nnode_t *node, short mark, netlist_t *netlist);
void instantiate_multi_port_mux(nnode_t *node, short mark, netlist_t *netlist);

#endif

