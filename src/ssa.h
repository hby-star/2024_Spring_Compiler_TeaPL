#ifndef __SSA
#define __SSA


#include "temp.h"
#include "llvm_ir.h"
#include "graph.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>

LLVMIR::L_prog* SSA(LLVMIR::L_prog*prog);
void combine_addr(LLVMIR::L_func* fun);
void mem2reg(LLVMIR::L_func* fun);
void Dominators(GRAPH::Graph<LLVMIR::L_block*>& bg);
std::unordered_set<LLVMIR::L_block *> Intersect(std::unordered_set<LLVMIR::L_block *> &a, std::unordered_set<LLVMIR::L_block *> &b);
std::unordered_set<LLVMIR::L_block *> Union(std::unordered_set<LLVMIR::L_block *> &a, std::unordered_set<LLVMIR::L_block *> &b);
bool Set_eq(std::unordered_set<LLVMIR::L_block *> &a, std::unordered_set<LLVMIR::L_block *> &b);
void tree_Dominators(GRAPH::Graph<LLVMIR::L_block*>& bg);
void computeDF(GRAPH::Graph<LLVMIR::L_block*>& bg,GRAPH::Node<LLVMIR::L_block*>* r);
void Place_phi_fu(GRAPH::Graph<LLVMIR::L_block*>& bg,LLVMIR:: L_func*fun);
void Rename(GRAPH::Graph<LLVMIR::L_block*>& bg, LLVMIR:: L_func*fun, std::ostream& debugLog);
void printf_domi();
void printf_D_tree();
void printf_DF();
#endif