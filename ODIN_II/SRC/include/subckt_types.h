#ifndef __SUBCKT_TYPES_H__
#define __SUBCKT_TYPES_H__
/*
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "odin_types.h"

#define NUM_OF_ODIN_CELL_TYPES 4
#define NUM_OF_YOSYS_CELL_TYPES 218

// global hashmap of yosys subckt types variable
typemap odin_subckt_str({{"multiply", MULTIPLY},
                         {"mult_", MULTIPLY},
                         {"adder", ADD},
                         {"sub", MINUS}},
                        NUM_OF_ODIN_CELL_TYPES);

// global hashmap of yosys subckt types variable
typemap yosys_subckt_str({
                             {"$_ANDNOT_", operation_list_END},
                             {"$_AND_", operation_list_END},          // (A, B, Y)
                             {"$_AOI3_", operation_list_END},         // (A, B, C, Y)
                             {"$_AOI4_", operation_list_END},         // (A, B, C, Y)
                             {"$_BUF_", BUF_NODE},                    // (A, Y)
                             {"$_DFFE_NN0N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NN0P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NN1N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NN1P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NN_", operation_list_END},      // (D, C, E, Q)
                             {"$_DFFE_NP0N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NP0P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NP1N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NP1P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_NP_", operation_list_END},      // (D, C, E, Q)
                             {"$_DFFE_PN0N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PN0P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PN1N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PN1P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PN_", operation_list_END},      // (D, C, E, Q)
                             {"$_DFFE_PP0N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PP0P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PP1N_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PP1P_", operation_list_END},    // (D, C, R, E, Q)
                             {"$_DFFE_PP_", operation_list_END},      // (D, C, E, Q)
                             {"$_DFFSRE_NNNN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NNNP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NNPN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NNPP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NPNN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NPNP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NPPN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_NPPP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PNNN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PNNP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PNPN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PNPP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PPNN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PPNP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PPPN_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSRE_PPPP_", operation_list_END},  // (C, S, R, E, D, Q)
                             {"$_DFFSR_NNN_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_NNP_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_NPN_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_NPP_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_PNN_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_PNP_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_PPN_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFFSR_PPP_", operation_list_END},    // (C, S, R, D, Q)
                             {"$_DFF_NN0_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_NN1_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_NP0_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_NP1_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_N_", operation_list_END},        // (D, C, Q)
                             {"$_DFF_PN0_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_PN1_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_PP0_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_PP1_", operation_list_END},      // (D, C, R, Q)
                             {"$_DFF_P_", operation_list_END},        // (D, C, Q)
                             {"$_DLATCHSR_NNN_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_NNP_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_NPN_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_NPP_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_PNN_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_PNP_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_PPN_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCHSR_PPP_", operation_list_END}, // (E, S, R, D, Q)
                             {"$_DLATCH_NN0_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_NN1_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_NP0_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_NP1_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_N_", operation_list_END},     // (E, D, Q)
                             {"$_DLATCH_PN0_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_PN1_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_PP0_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_PP1_", operation_list_END},   // (E, R, D, Q)
                             {"$_DLATCH_P_", operation_list_END},     // (E, D, Q)
                             {"$_FF_", operation_list_END},           // (D, Q)
                             {"$_MUX16_", operation_list_END},        // (A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, S, T, U, V, Y)
                             {"$_MUX4_", operation_list_END},         // (A, B, C, D, S, T, Y)
                             {"$_MUX8_", operation_list_END},         // (A, B, C, D, E, F, G, H, S, T, U, Y)
                             {"$_MUX_", operation_list_END},          // (A, B, S, Y)
                             {"$_NAND_", operation_list_END},         // (A, B, Y)
                             {"$_NMUX_", operation_list_END},         // (A, B, S, Y)
                             {"$_NOR_", operation_list_END},          // (A, B, Y)
                             {"$_NOT_", operation_list_END},          // (A, Y)
                             {"$_OAI3_", operation_list_END},         // (A, B, C, Y)
                             {"$_OAI4_", operation_list_END},         // (A, B, C, Y)
                             {"$_ORNOT_", operation_list_END},        // (A, B, Y)
                             {"$_OR_", operation_list_END},           // (A, B, Y)
                             {"$_SDFFCE_NN0N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NN0P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NN1N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NN1P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NP0N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NP0P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NP1N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_NP1P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PN0N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PN0P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PN1N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PN1P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PP0N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PP0P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PP1N_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFCE_PP1P_", operation_list_END},  // (D, C, R, E, Q)
                             {"$_SDFFE_NN0N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NN0P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NN1N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NN1P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NP0N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NP0P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NP1N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_NP1P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PN0N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PN0P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PN1N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PN1P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PP0N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PP0P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PP1N_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFFE_PP1P_", operation_list_END},   // (D, C, R, E, Q)
                             {"$_SDFF_NN0_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_NN1_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_NP0_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_NP1_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_PN0_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_PN1_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_PP0_", operation_list_END},     // (D, C, R, Q)
                             {"$_SDFF_PP1_", operation_list_END},     // (D, C, R, Q)
                             {"$_SR_NN_", operation_list_END},        // (S, R, Q)
                             {"$_SR_NP_", operation_list_END},        // (S, R, Q)
                             {"$_SR_PN_", operation_list_END},        // (S, R, Q)
                             {"$_SR_PP_", operation_list_END},        // (S, R, Q)
                             {"$_TBUF_", operation_list_END},         // (A, E, Y)
                             {"$_XNOR_", operation_list_END},         // (A, B, Y)
                             {"$_XOR_", operation_list_END},          // (A, B, Y)
                             {"$add", ADD},                           // (A, B, Y)
                             {"$adff", operation_list_END},           // (CLK, ARST, D, Q)
                             {"$adffe", ADFFE},                       // (CLK, ARST, EN, D, Q)
                             {"$adlatch", operation_list_END},        // (EN, ARST, D, Q)
                             {"$allconst", operation_list_END},       // (Y)
                             {"$allseq", operation_list_END},         // (Y)
                             {"$alu", operation_list_END},            // (A, B, CI, BI, X, Y, CO)
                             {"$and", BITWISE_AND},                   // (A, B, Y)
                             {"$anyconst", operation_list_END},       // (Y)
                             {"$anyseq", operation_list_END},         // (Y)
                             {"$assert", operation_list_END},         // (A, EN)
                             {"$assume", operation_list_END},         // (A, EN)
                             {"$concat", operation_list_END},         // (A, B, Y)
                             {"$cover", operation_list_END},          // (A, EN)
                             {"$dff", FF_NODE},                       // (CLK, D, Q)
                             {"$dffe", DFFE},                         // (CLK, EN, D, Q)
                             {"$dffsr", DFFSR},                       // (CLK, SET, CLR, D, Q)
                             {"$dffsre", operation_list_END},         // (CLK, SET, CLR, EN, D, Q)
                             {"$div", operation_list_END},            // (A, B, Y)
                             {"$divfloor", operation_list_END},       // (A, B, Y)
                             {"$dlatch", operation_list_END},         // (EN, D, Q)
                             {"$dlatchsr", operation_list_END},       // (EN, SET, CLR, D, Q)
                             {"$eq", LOGICAL_EQUAL},                  // (A, B, Y)
                             {"$equiv", operation_list_END},          // (A, B, Y)
                             {"$eqx", operation_list_END},            // (A, B, Y)
                             {"$fa", operation_list_END},             // (A, B, C, X, Y)
                             {"$fair", operation_list_END},           // (A, EN)
                             {"$ff", operation_list_END},             // (D, Q)
                             {"$fsm", operation_list_END},            // (CLK, ARST, CTRL_IN, CTRL_OUT)
                             {"$ge", GTE},                            // (A, B, Y)
                             {"$gt", GT},                             // (A, B, Y)
                             {"$initstate", operation_list_END},      // (Y)
                             {"$lcu", operation_list_END},            // (P, G, CI, CO)
                             {"$le", LTE},                            // (A, B, Y)
                             {"$live", operation_list_END},           // (A, EN)
                             {"$logic_and", LOGICAL_AND},             // (A, B, Y)
                             {"$logic_not", LOGICAL_NOT},             // (A, Y)
                             {"$logic_or", LOGICAL_OR},               // (A, B, Y)
                             {"$lt", LT},                             // (A, B, Y)
                             {"$lut", operation_list_END},            // (A, Y)
                             {"$macc", operation_list_END},           // (A, B, Y)
                             {"$mem", MEMORY},                        // (RD_CLK, RD_EN, RD_ADDR, RD_DATA, WR_CLK, WR_EN, WR_ADDR, WR_DATA)
                             {"$meminit", operation_list_END},        // (ADDR, DATA)
                             {"$memrd", operation_list_END},          // (CLK, EN, ADDR, DATA)
                             {"$memwr", operation_list_END},          // (CLK, EN, ADDR, DATA)
                             {"$mod", operation_list_END},            // (A, B, Y)
                             {"$modfloor", operation_list_END},       // (A, B, Y)
                             {"$mul", MULTIPLY},                      // (A, B, Y)
                             {"$mux", MULTIPORT_nBIT_MUX},            // (A, B, S, Y)
                             {"$ne", operation_list_END},             // (A, B, Y)
                             {"$neg", operation_list_END},            // (A, Y)
                             {"$nex", operation_list_END},            // (A, B, Y)
                             {"$not", BITWISE_NOT},                   // (A, Y)
                             {"$or", BITWISE_OR},                     // (A, B, Y)
                             {"$pmux", PMUX},                         // (A, B, S, Y)
                             {"$pos", operation_list_END},            // (A, Y)
                             {"$pow", operation_list_END},            // (A, B, Y)
                             {"$reduce_and", operation_list_END},     // (A, Y)
                             {"$reduce_bool", LOGICAL_OR},            // (A, Y)
                             {"$reduce_or", LOGICAL_OR},              // (A, Y)
                             {"$reduce_xnor", operation_list_END},    // (A, Y)
                             {"$reduce_xor", operation_list_END},     // (A, Y)
                             {"$sdff", SDFF},                         // (CLK, SRST, D, Q)
                             {"$sdffce", operation_list_END},         // (CLK, SRST, EN, D, Q)
                             {"$sdffe", SDFFE},                       // (CLK, SRST, EN, D, Q)
                             {"$shift", operation_list_END},          // (A, B, Y)
                             {"$shiftx", operation_list_END},         // (A, B, Y)
                             {"$shl", operation_list_END},            // (A, B, Y)
                             {"$shr", operation_list_END},            // (A, B, Y)
                             {"$slice", operation_list_END},          // (A, Y)
                             {"$sop", operation_list_END},            // (A, Y)
                             {"$specify2", operation_list_END},       // (EN, SRC, DST)
                             {"$specify3", operation_list_END},       // (EN, SRC, DST, DAT)
                             {"$specrule", operation_list_END},       // (EN_SRC, EN_DST, SRC, DST)
                             {"$sr", operation_list_END},             // (SET, CLR, Q)
                             {"$sshl", operation_list_END},           // (A, B, Y)
                             {"$sshr", operation_list_END},           // (A, B, Y)
                             {"$sub", MINUS},                         // (A, B, Y)
                             {"$tribuf", operation_list_END},         // (A, EN, Y)
                             {"$xnor", LOGICAL_XNOR},                 // (A, B, Y)
                             {"$xor", LOGICAL_XOR}                    // (A, B, Y)
                         },
                         NUM_OF_YOSYS_CELL_TYPES);

#endif
