#include "ast2llvm.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <list>

using namespace std;
using namespace LLVMIR;

static unordered_map<string, FuncType> funcReturnMap;
static unordered_map<string, StructInfo> structInfoMap;
static unordered_map<string, Name_name *> globalVarMap;
static unordered_map<string, Temp_temp *> localVarMap;
static list<L_stm *> emit_irs;

LLVMIR::L_prog *ast2llvm(aA_program p)
{
    auto defs = ast2llvmProg_first(p);
    auto funcs = ast2llvmProg_second(p);
    vector<L_func *> funcs_block;
    for (const auto &f : funcs)
    {
        funcs_block.push_back(ast2llvmFuncBlock(f));
    }
    for (auto &f : funcs_block)
    {
        ast2llvm_moveAlloca(f);
    }
    return new L_prog(defs, funcs_block);
}

int ast2llvmRightVal_first(aA_rightVal r)
{
    if (r == nullptr)
    {
        return 0;
    }
    switch (r->kind)
    {
    case A_arithExprValKind:
    {
        return ast2llvmArithExpr_first(r->u.arithExpr);
        break;
    }
    case A_boolExprValKind:
    {
        return ast2llvmBoolExpr_first(r->u.boolExpr);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmBoolExpr_first(aA_boolExpr b)
{
    switch (b->kind)
    {
    case A_boolBiOpExprKind:
    {
        return ast2llvmBoolBiOpExpr_first(b->u.boolBiOpExpr);
        break;
    }
    case A_boolUnitKind:
    {
        return ast2llvmBoolUnit_first(b->u.boolUnit);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmBoolBiOpExpr_first(aA_boolBiOpExpr b)
{
    int l = ast2llvmBoolExpr_first(b->left);
    int r = ast2llvmBoolExpr_first(b->right);
    if (b->op == A_and)
    {
        return l && r;
    }
    else
    {
        return l || r;
    }
}

int ast2llvmBoolUOpExpr_first(aA_boolUOpExpr b)
{
    if (b->op == A_not)
    {
        return !ast2llvmBoolUnit_first(b->cond);
    }
    return 0;
}

int ast2llvmBoolUnit_first(aA_boolUnit b)
{
    switch (b->kind)
    {
    case A_comOpExprKind:
    {
        return ast2llvmComOpExpr_first(b->u.comExpr);
        break;
    }
    case A_boolExprKind:
    {
        return ast2llvmBoolExpr_first(b->u.boolExpr);
        break;
    }
    case A_boolUOpExprKind:
    {
        return ast2llvmBoolUOpExpr_first(b->u.boolUOpExpr);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmComOpExpr_first(aA_comExpr c)
{
    auto l = ast2llvmExprUnit_first(c->left);
    auto r = ast2llvmExprUnit_first(c->right);
    switch (c->op)
    {
    case A_lt:
    {
        return l < r;
        break;
    }
    case A_le:
    {
        return l <= r;
        break;
    }
    case A_gt:
    {
        return l > r;
        break;
    }
    case A_ge:
    {
        return l >= r;
        break;
    }
    case A_eq:
    {
        return l == r;
        break;
    }
    case A_ne:
    {
        return l != r;
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmArithBiOpExpr_first(aA_arithBiOpExpr a)
{
    auto l = ast2llvmArithExpr_first(a->left);
    auto r = ast2llvmArithExpr_first(a->right);
    switch (a->op)
    {
    case A_add:
    {
        return l + r;
        break;
    }
    case A_sub:
    {
        return l - r;
        break;
    }
    case A_mul:
    {
        return l * r;
        break;
    }
    case A_div:
    {
        return l / r;
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmArithUExpr_first(aA_arithUExpr a)
{
    if (a->op == A_neg)
    {
        return -ast2llvmExprUnit_first(a->expr);
    }
    return 0;
}

int ast2llvmArithExpr_first(aA_arithExpr a)
{
    switch (a->kind)
    {
    case A_arithBiOpExprKind:
    {
        return ast2llvmArithBiOpExpr_first(a->u.arithBiOpExpr);
        break;
    }
    case A_exprUnitKind:
    {
        return ast2llvmExprUnit_first(a->u.exprUnit);
        break;
    }
    default:
        assert(0);
        break;
    }
    return 0;
}

int ast2llvmExprUnit_first(aA_exprUnit e)
{
    if (e->kind == A_numExprKind)
    {
        return e->u.num;
    }
    else if (e->kind == A_arithExprKind)
    {
        return ast2llvmArithExpr_first(e->u.arithExpr);
    }
    else if (e->kind == A_arithUExprKind)
    {
        return ast2llvmArithUExpr_first(e->u.arithUExpr);
    }
    else
    {
        assert(0);
    }
    return 0;
}

std::vector<LLVMIR::L_def *> ast2llvmProg_first(aA_program p)
{
    vector<L_def *> defs;
    defs.push_back(L_Funcdecl("getch", vector<TempDef>(), FuncType(ReturnType::INT_TYPE)));
    defs.push_back(L_Funcdecl("getint", vector<TempDef>(), FuncType(ReturnType::INT_TYPE)));
    defs.push_back(L_Funcdecl("putch", vector<TempDef>{TempDef(TempType::INT_TEMP)}, FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("putint", vector<TempDef>{TempDef(TempType::INT_TEMP)}, FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("putarray", vector<TempDef>{TempDef(TempType::INT_TEMP), TempDef(TempType::INT_PTR, -1)}, FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("_sysy_starttime", vector<TempDef>{TempDef(TempType::INT_TEMP)}, FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("_sysy_stoptime", vector<TempDef>{TempDef(TempType::INT_TEMP)}, FuncType(ReturnType::VOID_TYPE)));
    for (const auto &v : p->programElements)
    {
        switch (v->kind)
        {
        case A_programNullStmtKind:
        {
            break;
        }
        case A_programVarDeclStmtKind:
        {
            if (v->u.varDeclStmt->kind == A_varDeclKind)
            {
                if (v->u.varDeclStmt->u.varDecl->kind == A_varDeclScalarKind)
                {
                    if (v->u.varDeclStmt->u.varDecl->u.declScalar->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                                             Name_newname_struct(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declScalar->id), *v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType));
                        TempDef def(TempType::STRUCT_TEMP, 0, *v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, def, vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                                             Name_newname_int(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declScalar->id)));
                        TempDef def(TempType::INT_TEMP, 0);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, def, vector<int>()));
                    }
                }
                else if (v->u.varDeclStmt->u.varDecl->kind == A_varDeclArrayKind)
                {
                    if (v->u.varDeclStmt->u.varDecl->u.declArray->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                                             Name_newname_struct_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declArray->id), v->u.varDeclStmt->u.varDecl->u.declArray->len, *v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType));
                        TempDef def(TempType::STRUCT_PTR, v->u.varDeclStmt->u.varDecl->u.declArray->len, *v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id, def, vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                                             Name_newname_int_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declArray->id), v->u.varDeclStmt->u.varDecl->u.declArray->len));
                        TempDef def(TempType::INT_PTR, v->u.varDeclStmt->u.varDecl->u.declArray->len);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id, def, vector<int>()));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else if (v->u.varDeclStmt->kind == A_varDefKind)
            {
                if (v->u.varDeclStmt->u.varDef->kind == A_varDefScalarKind)
                {
                    if (v->u.varDeclStmt->u.varDef->u.defScalar->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id,
                                             Name_newname_struct(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defScalar->id), *v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType));
                        TempDef def(TempType::STRUCT_TEMP, 0, *v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id, def, vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id,
                                             Name_newname_int(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defScalar->id)));
                        TempDef def(TempType::INT_TEMP, 0);
                        vector<int> init;
                        init.push_back(ast2llvmRightVal_first(v->u.varDeclStmt->u.varDef->u.defScalar->val));
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id, def, init));
                    }
                }
                else if (v->u.varDeclStmt->u.varDef->kind == A_varDefArrayKind)
                {
                    if (v->u.varDeclStmt->u.varDef->u.defArray->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id,
                                             Name_newname_struct_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defArray->id), v->u.varDeclStmt->u.varDef->u.defArray->len, *v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType));
                        TempDef def(TempType::STRUCT_PTR, v->u.varDeclStmt->u.varDef->u.defArray->len, *v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id, def, vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id,
                                             Name_newname_int_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defArray->id), v->u.varDeclStmt->u.varDef->u.defArray->len));
                        TempDef def(TempType::INT_PTR, v->u.varDeclStmt->u.varDef->u.defArray->len);
                        vector<int> init;
                        for (auto &el : v->u.varDeclStmt->u.varDef->u.defArray->vals)
                        {
                            init.push_back(ast2llvmRightVal_first(el));
                        }
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id, def, init));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else
            {
                assert(0);
            }
            break;
        }
        case A_programStructDefKind:
        {
            StructInfo si;
            int off = 0;
            vector<TempDef> members;
            for (const auto &decl : v->u.structDef->varDecls)
            {
                if (decl->kind == A_varDeclScalarKind)
                {
                    if (decl->u.declScalar->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_TEMP, 0, *decl->u.declScalar->type->u.structType);
                        MemberInfo info(off++, def);
                        si.memberinfos.emplace(*decl->u.declScalar->id, info);
                        members.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_TEMP, 0);
                        MemberInfo info(off++, def);
                        si.memberinfos.emplace(*decl->u.declScalar->id, info);
                        members.push_back(def);
                    }
                }
                else if (decl->kind == A_varDeclArrayKind)
                {
                    if (decl->u.declArray->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR, decl->u.declArray->len, *decl->u.declArray->type->u.structType);
                        MemberInfo info(off++, def);
                        si.memberinfos.emplace(*decl->u.declArray->id, info);
                        members.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_PTR, decl->u.declArray->len);
                        MemberInfo info(off++, def);
                        si.memberinfos.emplace(*decl->u.declArray->id, info);
                        members.push_back(def);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            structInfoMap.emplace(*v->u.structDef->id, std::move(si));
            defs.push_back(L_Structdef(*v->u.structDef->id, members));
            break;
        }
        case A_programFnDeclStmtKind:
        {
            FuncType type;
            if (v->u.fnDeclStmt->fnDecl->type == nullptr)
            {
                type.type = ReturnType::VOID_TYPE;
            }
            else if (v->u.fnDeclStmt->fnDecl->type->type == A_nativeTypeKind)
            {
                type.type = ReturnType::INT_TYPE;
            }
            else if (v->u.fnDeclStmt->fnDecl->type->type == A_structTypeKind)
            {
                type.type = ReturnType::STRUCT_TYPE;
                type.structname = *v->u.fnDeclStmt->fnDecl->type->u.structType;
            }
            else
            {
                assert(0);
            }
            if (funcReturnMap.find(*v->u.fnDeclStmt->fnDecl->id) == funcReturnMap.end())
                funcReturnMap.emplace(*v->u.fnDeclStmt->fnDecl->id, std::move(type));
            vector<TempDef> args;
            for (const auto &decl : v->u.fnDeclStmt->fnDecl->paramDecl->varDecls)
            {
                if (decl->kind == A_varDeclScalarKind)
                {
                    if (decl->u.declScalar->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR, 0, *decl->u.declScalar->type->u.structType);
                        args.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_TEMP, 0);
                        args.push_back(def);
                    }
                }
                else if (decl->kind == A_varDeclArrayKind)
                {
                    if (decl->u.declArray->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR, -1, *decl->u.declArray->type->u.structType);
                        args.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_PTR, -1);
                        args.push_back(def);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            defs.push_back(L_Funcdecl(*v->u.fnDeclStmt->fnDecl->id, args, type));
            break;
        }
        case A_programFnDefKind:
        {
            if (funcReturnMap.find(*v->u.fnDef->fnDecl->id) == funcReturnMap.end())
            {
                FuncType type;
                if (v->u.fnDef->fnDecl->type == nullptr)
                {
                    type.type = ReturnType::VOID_TYPE;
                }
                else if (v->u.fnDef->fnDecl->type->type == A_nativeTypeKind)
                {
                    type.type = ReturnType::INT_TYPE;
                }
                else if (v->u.fnDef->fnDecl->type->type == A_structTypeKind)
                {
                    type.type = ReturnType::STRUCT_TYPE;
                    type.structname = *v->u.fnDef->fnDecl->type->u.structType;
                }
                else
                {
                    assert(0);
                }
                funcReturnMap.emplace(*v->u.fnDef->fnDecl->id, std::move(type));
            }
            break;
        }
        default:
            assert(0);
            break;
        }
    }
    return defs;
}

std::vector<Func_local *> ast2llvmProg_second(aA_program p)
{
    vector<Func_local *> funcs;
    for (const auto &v : p->programElements)
    {
        switch (v->kind)
        {
        case A_programNullStmtKind:
        {
            break;
        }
        case A_programVarDeclStmtKind:
        {
            break;
        }
        case A_programStructDefKind:
        {
            break;
        }
        case A_programFnDeclStmtKind:
        {
            break;
        }
        case A_programFnDefKind:
        {
            funcs.push_back(ast2llvmFunc(v->u.fnDef));
            break;
        }
        default:
            assert(0);
            break;
        }
    }
    return funcs;
}

Func_local *ast2llvmFunc(aA_fnDef f)
{
    emit_irs.clear();
    localVarMap.clear();

    // 处理函数参数
    vector<Temp_temp *> args;
    for (const auto &decl : f->fnDecl->paramDecl->varDecls)
    {
        if (decl->kind == A_varDeclScalarKind)
        {
            Temp_temp *temp;
            if (decl->u.declScalar->type->type == A_structTypeKind)
            {
                temp = Temp_newtemp_struct(*decl->u.declScalar->type->u.structType);
            }
            else
            {
                temp = Temp_newtemp_int();
            }
            localVarMap.emplace(*decl->u.declScalar->id, temp);
            args.push_back(temp);
        }
        else if (decl->kind == A_varDeclArrayKind)
        {
            Temp_temp *temp;
            if (decl->u.declArray->type->type == A_structTypeKind)
            {
                temp = Temp_newtemp_struct_ptr(decl->u.declArray->len, *decl->u.declArray->type->u.structType);
            }
            else
            {
                temp = Temp_newtemp_int_ptr(decl->u.declArray->len);
            }
            localVarMap.emplace(*decl->u.declArray->id, temp);
            args.push_back(temp);
        }
        else
        {
            assert(0);
        }
    }

    // 处理函数体
    for (const auto &v : f->stmts)
    {
        // 跳过空语句
        if (v->kind == A_nullStmtKind)
        {
            continue;
        }
        // 变量声明语句
        else if (v->kind == A_varDeclStmtKind)
        {
            // 仅声明
            if (v->u.varDeclStmt->kind == A_varDeclKind)
            {
                // 标量声明
                if (v->u.varDeclStmt->u.varDecl->kind == A_varDeclScalarKind)
                {
                    // STRUCT 声明
                    if (v->u.varDeclStmt->u.varDecl->u.declScalar->type->type == A_structTypeKind)
                    {
                        Temp_temp *temp = Temp_newtemp_struct(*v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType);
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                    }
                    // INT 声明
                    else
                    {
                        Temp_temp *temp = Temp_newtemp_int();
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                    }
                }
                // 数组声明
                else if (v->u.varDeclStmt->u.varDecl->kind == A_varDeclArrayKind)
                {
                    // STRUCT 数组声明
                    if (v->u.varDeclStmt->u.varDecl->u.declArray->type->type == A_structTypeKind)
                    {
                        Temp_temp *temp = Temp_newtemp_struct_ptr(v->u.varDeclStmt->u.varDecl->u.declArray->len, *v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType);
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                    }
                    // INT 数组声明
                    else
                    {
                        Temp_temp *temp = Temp_newtemp_int_ptr(v->u.varDeclStmt->u.varDecl->u.declArray->len);
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            // 定义
            else if (v->u.varDeclStmt->kind == A_varDefKind)
            {
                // 标量定义
                if (v->u.varDeclStmt->u.varDef->kind == A_varDefScalarKind)
                {
                    // STRUCT 定义
                    if (v->u.varDeclStmt->u.varDef->u.defScalar->type->type == A_structTypeKind)
                    {
                        Temp_temp *temp = Temp_newtemp_struct(*v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType);
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                        emit_irs.push_back(L_Store(ast2llvmRightVal(v->u.varDeclStmt->u.varDef->u.defScalar->val), AS_Operand_Temp(temp)));
                    }
                    // INT 定义
                    else
                    {
                        Temp_temp *temp = Temp_newtemp_int();
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                        emit_irs.push_back(L_Store(ast2llvmRightVal(v->u.varDeclStmt->u.varDef->u.defScalar->val), AS_Operand_Temp(temp)));
                    }
                }
                // 数组定义
                // 暂时不支持
                else if (v->u.varDeclStmt->u.varDef->kind == A_varDefArrayKind)
                {
                    // STRUCT 数组定义
                    if (v->u.varDeclStmt->u.varDef->u.defArray->type->type == A_structTypeKind)
                    {
                        Temp_temp *temp = Temp_newtemp_struct_ptr(v->u.varDeclStmt->u.varDef->u.defArray->len, *v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType);
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                        for (int i = 0; i < v->u.varDeclStmt->u.varDef->u.defArray->vals.size(); i++)
                        {
                            emit_irs.push_back(L_Store(ast2llvmRightVal(v->u.varDeclStmt->u.varDef->u.defArray->vals[i]), AS_Operand_Temp(temp)));
                        }
                    }
                    // INT 数组定义
                    else
                    {
                        Temp_temp *temp = Temp_newtemp_int_ptr(v->u.varDeclStmt->u.varDef->u.defArray->len);
                        localVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id, temp);

                        // 翻译为 IR
                        emit_irs.push_back(L_Alloca(AS_Operand_Temp(temp)));
                        for (int i = 0; i < v->u.varDeclStmt->u.varDef->u.defArray->vals.size(); i++)
                        {
                            emit_irs.push_back(L_Store(ast2llvmRightVal(v->u.varDeclStmt->u.varDef->u.defArray->vals[i]), AS_Operand_Temp(temp)));
                        }
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else
            {
                assert(0);
            }
        }
        // 赋值语句
        else if (v->kind == A_assignStmtKind)
        {
            // 普通变量
            if (v->u.assignStmt->leftVal->kind == A_varValKind)
            {
                Temp_temp *temp = localVarMap[*v->u.assignStmt->leftVal->u.id];
                emit_irs.push_back(L_Load(AS_Operand_Temp(temp), ast2llvmRightVal(v->u.assignStmt->rightVal)));
                emit_irs.push_back(L_Store(AS_Operand_Temp(temp), ast2llvmLeftVal(v->u.assignStmt->leftVal)));
            }
            // 数组成员
            else if (v->u.assignStmt->leftVal->kind == A_arrValKind)
            {
                Temp_temp *temp = localVarMap[*v->u.assignStmt->leftVal->u.arrExpr->arr->u.id];
                emit_irs.push_back(L_Load(AS_Operand_Temp(temp), ast2llvmRightVal(v->u.assignStmt->rightVal)));
                emit_irs.push_back(L_Store(ast2llvmRightVal(v->u.assignStmt->rightVal), ast2llvmIndexExpr(v->u.assignStmt->leftVal->u.arrExpr->idx)));
            }
            // 结构体成员
            else if (v->u.assignStmt->leftVal->kind == A_memberValKind)
            {
                Temp_temp *temp = localVarMap[*v->u.assignStmt->leftVal->u.structExpr->id];
                emit_irs.push_back(L_Store(ast2llvmRightVal(v->u.assignStmt->rightVal), ast2llvmIndexExpr(v->u.assignStmt->leftVal->u.structExpr->indexExpr)));
            }
            else
            {
                assert(0);
            }
        }
        // 函数调用语句
        else if (v->kind == A_callStmtKind)
        {
        }
        // if 语句
        else if (v->kind == A_ifStmtKind)
        {
        }
        // while 语句
        else if (v->kind == A_whileStmtKind)
        {
        }
        // return 语句
        else if (v->kind == A_returnStmtKind)
        {
        }
        // continue 语句
        else if (v->kind == A_continueStmtKind)
        {
            continue;
        }
        // break 语句
        else if (v->kind == A_breakStmtKind)
        {
            continue;
        }
        else
        {
            assert(0);
        }
    }
    return new Func_local(*f->fnDecl->id, funcReturnMap[*f->fnDecl->id], args, emit_irs);
}

void ast2llvmBlock(aA_codeBlockStmt b, Temp_label *con_label, Temp_label *bre_label)
{
}

AS_operand *ast2llvmRightVal(aA_rightVal r)
{
}

AS_operand *ast2llvmLeftVal(aA_leftVal l)
{
}

AS_operand *ast2llvmIndexExpr(aA_indexExpr index)
{
}

AS_operand *ast2llvmBoolExpr(aA_boolExpr b, Temp_label *true_label, Temp_label *false_label)
{
}

void ast2llvmBoolBiOpExpr(aA_boolBiOpExpr b, Temp_label *true_label, Temp_label *false_label)
{
}

void ast2llvmBoolUnit(aA_boolUnit b, Temp_label *true_label, Temp_label *false_label)
{
}

void ast2llvmComOpExpr(aA_comExpr c, Temp_label *true_label, Temp_label *false_label)
{
}

AS_operand *ast2llvmArithBiOpExpr(aA_arithBiOpExpr a)
{
}

AS_operand *ast2llvmArithUExpr(aA_arithUExpr a)
{
}

AS_operand *ast2llvmArithExpr(aA_arithExpr a)
{
}

AS_operand *ast2llvmExprUnit(aA_exprUnit e)
{
}

LLVMIR::L_func *ast2llvmFuncBlock(Func_local *f)
{
}

void ast2llvm_moveAlloca(LLVMIR::L_func *f)
{
    auto first_block = f->blocks.front();
    for (auto i = ++f->blocks.begin(); i != f->blocks.end(); ++i)
    {
        for (auto it = (*i)->instrs.begin(); it != (*i)->instrs.end();)
        {
            if ((*it)->type == L_StmKind::T_ALLOCA)
            {
                first_block->instrs.insert(++first_block->instrs.begin(), *it);
                it = (*i)->instrs.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}