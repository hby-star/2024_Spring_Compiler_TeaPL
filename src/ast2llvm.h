#ifndef __AST2LLVM
#define __AST2LLVM

#include "temp.h"
#include "llvm_ir.h"
#include "TeaplaAst.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

struct MemberInfo
{
    int offset;
    TempDef def;
    MemberInfo(int off = 0, TempDef d = TempDef())
        : offset(off), def(d) {}
};

struct StructInfo
{
    std::unordered_map<std::string, MemberInfo> memberinfos;
};

struct Func_local
{
    std::string name;
    LLVMIR::FuncType ret;
    std::vector<Temp_temp *> args;
    std::list<LLVMIR::L_stm *> irs;
    Func_local(const std::string _name, LLVMIR::FuncType _ret, const std::vector<Temp_temp *> &_args, const std::list<LLVMIR::L_stm *> &_irs)
        : name(_name), ret(_ret), args(_args), irs(_irs) {}
};

std::vector<LLVMIR::L_def *> ast2llvmProg_first(aA_program p);
std::vector<Func_local *> ast2llvmProg_second(aA_program p);
Func_local *ast2llvmFunc(aA_fnDef f);
void ast2llvmBlock(aA_codeBlockStmt b, Temp_label *con_label = nullptr, Temp_label *bre_label = nullptr);
AS_operand *ast2llvmRightVal(aA_rightVal r);
AS_operand *ast2llvmLeftVal(aA_leftVal l);
AS_operand *ast2llvmIndexExpr(aA_indexExpr index);
AS_operand *ast2llvmBoolExpr(aA_boolExpr b, Temp_label *true_label = nullptr, Temp_label *false_label = nullptr);
void ast2llvmBoolBiOpExpr(aA_boolBiOpExpr b, Temp_label *true_label, Temp_label *false_label);
void ast2llvmBoolUOpExpr(aA_boolUOpExpr b, Temp_label *true_label, Temp_label *false_label);
void ast2llvmBoolUnit(aA_boolUnit b, Temp_label *true_label, Temp_label *false_label);
void ast2llvmComOpExpr(aA_comExpr c, Temp_label *true_label, Temp_label *false_label);
AS_operand *ast2llvmArithBiOpExpr(aA_arithBiOpExpr a);
AS_operand *ast2llvmArithUExpr(aA_arithUExpr a);
AS_operand *ast2llvmArithExpr(aA_arithExpr a);
AS_operand *ast2llvmExprUnit(aA_exprUnit e);
AS_operand *ast2llvmArrayExpr(aA_arrayExpr a);
AS_operand *ast2llvmMemberExpr(aA_memberExpr a);
AS_operand *findMemberIndex(string &structId, string &membername);
AS_operand *findVal(string &name);
Name_name *findGlobalVal(string &name);
Temp_temp *findLocalVal(string &name);
string findMember(string &structId);
AS_operand *ast2llvmMemberIndex(aA_leftVal l, string memberId);
AS_operand *getArray(aA_arrayExpr arrExpr);
AS_operand *getMember(aA_memberExpr memberExpr);
AS_operand *loadPtr(AS_operand *res);
void put_right_vals_into_array(Temp_temp *new_arr, vector<aA_rightVal> vals, int len, TempType type, string structname);

LLVMIR::L_prog *ast2llvm(aA_program p);
LLVMIR::L_func *ast2llvmFuncBlock(Func_local *f);
void ast2llvm_moveAlloca(LLVMIR::L_func *f);

int ast2llvmRightVal_first(aA_rightVal r);
int ast2llvmBoolExpr_first(aA_boolExpr b);
int ast2llvmBoolBiOpExpr_first(aA_boolBiOpExpr b);
int ast2llvmBoolUOpExpr_first(aA_boolUOpExpr b);
int ast2llvmBoolUnit_first(aA_boolUnit b);
int ast2llvmComOpExpr_first(aA_comExpr c);
int ast2llvmArithBiOpExpr_first(aA_arithBiOpExpr a);
int ast2llvmArithUExpr_first(aA_arithUExpr a);
int ast2llvmArithExpr_first(aA_arithExpr a);
int ast2llvmExprUnit_first(aA_exprUnit e);

#endif