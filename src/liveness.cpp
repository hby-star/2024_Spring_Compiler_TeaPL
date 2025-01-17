#include "liveness.h"
#include <unordered_map>
#include <unordered_set>
#include "graph.hpp"
#include "llvm_ir.h"
#include "temp.h"

using namespace std;
using namespace LLVMIR;
using namespace GRAPH;

struct inOut
{
    TempSet_ in;
    TempSet_ out;
};

struct useDef
{
    TempSet_ use;
    TempSet_ def;
};

static unordered_map<GRAPH::Node<LLVMIR::L_block *> *, inOut> InOutTable;
static unordered_map<GRAPH::Node<LLVMIR::L_block *> *, useDef> UseDefTable;

list<AS_operand **> get_all_AS_operand(L_stm *stm)
{
    list<AS_operand **> AS_operand_list;
    switch (stm->type)
    {
    case L_StmKind::T_BINOP:
    {
        AS_operand_list.push_back(&(stm->u.BINOP->left));
        AS_operand_list.push_back(&(stm->u.BINOP->right));
        AS_operand_list.push_back(&(stm->u.BINOP->dst));
    }
    break;
    case L_StmKind::T_LOAD:
    {
        AS_operand_list.push_back(&(stm->u.LOAD->dst));
        AS_operand_list.push_back(&(stm->u.LOAD->ptr));
    }
    break;
    case L_StmKind::T_STORE:
    {
        AS_operand_list.push_back(&(stm->u.STORE->src));
        AS_operand_list.push_back(&(stm->u.STORE->ptr));
    }
    break;
    case L_StmKind::T_LABEL:
    {
    }
    break;
    case L_StmKind::T_JUMP:
    {
    }
    break;
    case L_StmKind::T_CMP:
    {
        AS_operand_list.push_back(&(stm->u.CMP->left));
        AS_operand_list.push_back(&(stm->u.CMP->right));
        AS_operand_list.push_back(&(stm->u.CMP->dst));
    }
    break;
    case L_StmKind::T_CJUMP:
    {
        AS_operand_list.push_back(&(stm->u.CJUMP->dst));
    }
    break;
    case L_StmKind::T_MOVE:
    {
        AS_operand_list.push_back(&(stm->u.MOVE->src));
        AS_operand_list.push_back(&(stm->u.MOVE->dst));
    }
    break;
    case L_StmKind::T_CALL:
    {
        AS_operand_list.push_back(&(stm->u.CALL->res));
        for (auto &arg : stm->u.CALL->args)
        {
            AS_operand_list.push_back(&arg);
        }
    }
    break;
    case L_StmKind::T_VOID_CALL:
    {
        for (auto &arg : stm->u.VOID_CALL->args)
        {
            AS_operand_list.push_back(&arg);
        }
    }
    break;
    case L_StmKind::T_RETURN:
    {
        if (stm->u.RETURN->ret != nullptr)
            AS_operand_list.push_back(&(stm->u.RETURN->ret));
    }
    break;
    case L_StmKind::T_PHI:
    {
        AS_operand_list.push_back(&(stm->u.PHI->dst));
        for (auto &phi : stm->u.PHI->phis)
        {
            AS_operand_list.push_back(&(phi.first));
        }
    }
    break;
    case L_StmKind::T_ALLOCA:
    {
        AS_operand_list.push_back(&(stm->u.ALLOCA->dst));
    }
    break;
    case L_StmKind::T_GEP:
    {
        AS_operand_list.push_back(&(stm->u.GEP->new_ptr));
        AS_operand_list.push_back(&(stm->u.GEP->base_ptr));
        AS_operand_list.push_back(&(stm->u.GEP->index));
    }
    break;
    default:
    {
        printf("%d\n", (int)stm->type);
        assert(0);
    }
    }
    return AS_operand_list;
}

//   done
std::list<AS_operand **> get_def_operand(L_stm *stm)
{
    list<AS_operand **> AS_operand_list;
    switch (stm->type)
    {
    case L_StmKind::T_BINOP:
    {
        AS_operand_list.push_back(&(stm->u.BINOP->dst));
    }
    break;
    case L_StmKind::T_LOAD:
    {
        AS_operand_list.push_back(&(stm->u.LOAD->dst));
    }
    break;
    case L_StmKind::T_STORE:
    {
        // AS_operand_list.push_back(&(stm->u.STORE->ptr));
    }
    break;
    case L_StmKind::T_LABEL:
    {
    }
    break;
    case L_StmKind::T_JUMP:
    {
    }
    break;
    case L_StmKind::T_CMP:
    {
        AS_operand_list.push_back(&(stm->u.CMP->dst));
    }
    break;
    case L_StmKind::T_CJUMP:
    {
    }
    break;
    case L_StmKind::T_MOVE:
    {
        AS_operand_list.push_back(&(stm->u.MOVE->dst));
    }
    break;
    case L_StmKind::T_CALL:
    {
        AS_operand_list.push_back(&(stm->u.CALL->res));
    }
    break;
    case L_StmKind::T_VOID_CALL:
    {
    }
    break;
    case L_StmKind::T_RETURN:
    {
    }
    break;
    case L_StmKind::T_PHI:
    {
        AS_operand_list.push_back(&(stm->u.PHI->dst));
    }
    break;
    case L_StmKind::T_ALLOCA:
    {
        // AS_operand_list.push_back(&(stm->u.ALLOCA->dst));
    }
    break;
    case L_StmKind::T_GEP:
    {
        // AS_operand_list.push_back(&(stm->u.GEP->new_ptr));
    }
    break;
    default:
    {
        printf("%d\n", (int)stm->type);
        assert(0);
    }
    }
    return AS_operand_list;
}

list<Temp_temp *> get_def(L_stm *stm)
{
    auto AS_operand_list = get_def_operand(stm);
    list<Temp_temp *> Temp_list;
    for (auto AS_op : AS_operand_list)
    {
        if ((*AS_op)->kind == OperandKind::TEMP)
            Temp_list.push_back((*AS_op)->u.TEMP);
    }
    return Temp_list;
}

//   done
std::list<AS_operand **> get_use_operand(L_stm *stm)
{
    list<AS_operand **> AS_operand_list;
    switch (stm->type)
    {
    case L_StmKind::T_BINOP:
    {
        AS_operand_list.push_back(&(stm->u.BINOP->left));
        AS_operand_list.push_back(&(stm->u.BINOP->right));
    }
    break;
    case L_StmKind::T_LOAD:
    {
        // AS_operand_list.push_back(&(stm->u.LOAD->ptr));
    }
    break;
    case L_StmKind::T_STORE:
    {
        AS_operand_list.push_back(&(stm->u.STORE->src));
        // AS_operand_list.push_back(&(stm->u.STORE->ptr));
    }
    break;
    case L_StmKind::T_LABEL:
    {
    }
    break;
    case L_StmKind::T_JUMP:
    {
    }
    break;
    case L_StmKind::T_CMP:
    {
        AS_operand_list.push_back(&(stm->u.CMP->left));
        AS_operand_list.push_back(&(stm->u.CMP->right));
    }
    break;
    case L_StmKind::T_CJUMP:
    {
        AS_operand_list.push_back(&(stm->u.CJUMP->dst));
    }
    break;
    case L_StmKind::T_MOVE:
    {
        AS_operand_list.push_back(&(stm->u.MOVE->src));
    }
    break;
    case L_StmKind::T_CALL:
    {
        for (auto &arg : stm->u.CALL->args)
        {
            if (arg->kind == OperandKind::TEMP && (arg->u.TEMP->type == TempType::INT_TEMP || (arg->u.TEMP->type == TempType::INT_PTR && arg->u.TEMP->len == 0)))
            {
                AS_operand_list.push_back(&arg);
            }
        }
    }
    break;
    case L_StmKind::T_VOID_CALL:
    {
        for (auto &arg : stm->u.VOID_CALL->args)
        {
            if (arg->kind == OperandKind::TEMP && (arg->u.TEMP->type == TempType::INT_TEMP || (arg->u.TEMP->type == TempType::INT_PTR && arg->u.TEMP->len == 0)))
            {
                AS_operand_list.push_back(&arg);
            }
        }
    }
    break;
    case L_StmKind::T_RETURN:
    {
        if (stm->u.RETURN->ret != nullptr)
            AS_operand_list.push_back(&(stm->u.RETURN->ret));
    }
    break;
    case L_StmKind::T_PHI:
    {
        for (auto &phi : stm->u.PHI->phis)
        {
            AS_operand_list.push_back(&(phi.first));
        }
    }
    break;
    case L_StmKind::T_ALLOCA:
    {
    }
    break;
    case L_StmKind::T_GEP:
    {
        // AS_operand_list.push_back(&(stm->u.GEP->base_ptr));
        AS_operand_list.push_back(&(stm->u.GEP->index));
    }
    break;
    default:
    {
        printf("%d\n", (int)stm->type);
        assert(0);
    }
    }
    return AS_operand_list;
}

list<Temp_temp *> get_use(L_stm *stm)
{
    auto AS_operand_list = get_use_operand(stm);
    list<Temp_temp *> Temp_list;
    for (auto AS_op : AS_operand_list)
    {
        if ((*AS_op)->kind == OperandKind::TEMP)
            Temp_list.push_back((*AS_op)->u.TEMP);
    }
    return Temp_list;
}

static void init_INOUT()
{
    InOutTable.clear();
    UseDefTable.clear();
}

TempSet_ &FG_Out(GRAPH::Node<LLVMIR::L_block *> *r)
{
    return InOutTable[r].out;
}
TempSet_ &FG_In(GRAPH::Node<LLVMIR::L_block *> *r)
{
    return InOutTable[r].in;
}
TempSet_ &FG_def(GRAPH::Node<LLVMIR::L_block *> *r)
{
    return UseDefTable[r].def;
}
TempSet_ &FG_use(GRAPH::Node<LLVMIR::L_block *> *r)
{
    return UseDefTable[r].use;
}

// done
static void Use_def(GRAPH::Node<LLVMIR::L_block *> *r, GRAPH::Graph<LLVMIR::L_block *> &bg, std::vector<Temp_temp *> &args)
{
    // 处理参数，函数参数视为第一个block的def
    for (auto arg : args)
    {
        TempSet_add(&UseDefTable[r].def, arg);
    }

    // 处理每个block
    for (auto block_node : bg.mynodes)
    {
        auto block = block_node.second->info;
        for (auto stm : block->instrs)
        {
            auto def = get_def(stm);
            auto use = get_use(stm);
            for (auto d : def)
            {
                TempSet_add(&UseDefTable[block_node.second].def, d);
            }
            for (auto u : use)
            {
                if (UseDefTable[block_node.second].def.find(u) == UseDefTable[block_node.second].def.end())
                    TempSet_add(&UseDefTable[block_node.second].use, u);
            }
        }
    }
}

// ./compiler tests/public/BFS.tea tests/public/BFS.ll < tests/public/BFS.in

static int gi = 0;
static bool LivenessIteration(GRAPH::Node<LLVMIR::L_block *> *r, GRAPH::Graph<LLVMIR::L_block *> &bg)
{
    // 活跃性计算迭代
    bool changed = false;
    gi++;
    for (auto block_node : bg.mynodes)
    {
        auto block = block_node.second->info;
        TempSet_ old_in = FG_In(block_node.second);
        TempSet_ old_out = FG_Out(block_node.second);

        // in[n] = use[n] U (out[n] - def[n])
        TempSet_ new_in = FG_use(block_node.second);
        for (auto x : FG_Out(block_node.second))
        {
            if (FG_def(block_node.second).find(x) == FG_def(block_node.second).end())
            {
                TempSet_add(&new_in, x);
            }
        }
        FG_In(block_node.second) = new_in;

        // out[n] = U (in[s]) s in succ[n]
        FG_Out(block_node.second) = TempSet_();
        for (auto succ : block_node.second->succs)
        {
            FG_Out(block_node.second) = *(TempSet_union(&FG_Out(block_node.second), &FG_In(bg.mynodes[succ])));
        }

        // 检测是否有变化
        if (old_in != FG_In(block_node.second) || old_out != FG_Out(block_node.second))
        {
            changed = true;
        }
    }

    return changed;
}

void PrintTemps(FILE *out, TempSet set)
{
    if (set)
    {
        for (auto x : *set)
        {
            if (x)
            {
                printf("%d  ", x->num);
            }
        }
    }
}

void Show_Liveness(FILE *out, GRAPH::Graph<LLVMIR::L_block *> &bg)
{
    fprintf(out, "\n\nNumber of iterations=%d\n\n", gi);
    for (auto block_node : bg.mynodes)
    {
        fprintf(out, "----------------------\n");
        printf("block %s \n", block_node.second->info->label->name.c_str());
        fprintf(out, "def=\n");
        PrintTemps(out, &FG_def(block_node.second));
        fprintf(out, "\n");
        fprintf(out, "use=\n");
        PrintTemps(out, &FG_use(block_node.second));
        fprintf(out, "\n");
        fprintf(out, "In=\n");
        PrintTemps(out, &FG_In(block_node.second));
        fprintf(out, "\n");
        fprintf(out, "Out=\n");
        PrintTemps(out, &FG_Out(block_node.second));
        fprintf(out, "\n");
    }
}
// 以block为单位
void Liveness(GRAPH::Node<LLVMIR::L_block *> *r, GRAPH::Graph<LLVMIR::L_block *> &bg, std::vector<Temp_temp *> &args)
{
    init_INOUT();
    // checked
    Use_def(r, bg, args);
    gi = 0;
    bool changed = true;
    while (changed)
        changed = LivenessIteration(r, bg);
}
