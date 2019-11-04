#include <stdlib.h>
#include <string.h>
#include "abstree.h"

//Expressions-------------------------------------------------------------------
Expr* expInt(int v){
    Expr* node = (Expr*)malloc(sizeof(Expr));
    node->kind = E_INTEGER;
    node->attr.value = v;
    return node;
}

Expr* expVar(char* var){
    Expr* node = (Expr*)malloc(sizeof(Expr));
    node->kind = E_VAR;
    node->attr.var = var;
    return node;
}

Expr* exprOp(int op, Expr* left, Expr* right){
    Expr* node = (Expr*)malloc(sizeof(Expr));
    node->kind = E_OPERATION;
    node->attr.op.operator = op;
    node->attr.op.left = left;
    node->attr.op.right = right;
    return node;
}

//Bool Expressions--------------------------------------------------------------
BoolExpr* boolNorm(Expr* exp){
    BoolExpr* node = (BoolExpr*)malloc(sizeof(BoolExpr));
    node->kind = B_BOOL;
    node->attr.value = exp;
    return node;
}

BoolExpr* boolExp(int op, Expr* left, Expr* right){
    BoolExpr* node = (BoolExpr*)malloc(sizeof(BoolExpr));
    node->kind = B_BOOLOP;
    node->attr.op.operator = op;
    node->attr.op.left = left;
    node->attr.op.right = right;
    return node;
}

//Bool Block any sequence with || or &&-----------------------------------------
BoolBlock* boolAnd(BoolExpr* val, BoolBlock* next){
    BoolBlock* node = (BoolBlock*)malloc(sizeof(BoolBlock));
    node->kind = B_AND;
    node->block.current_bool.bool_val = val;
    node->block.next = next;
    return node;
}

BoolBlock* boolOr(BoolExpr* val, BoolBlock* next){
    BoolBlock* node = (BoolBlock*)malloc(sizeof(BoolBlock));
    node->kind = B_OR;
    node->block.current_bool.bool_val = val;
    node->block.next = next;
    return node;
}

BoolBlock* boolBlock(BoolExpr* val, BoolBlock* next){
    BoolBlock* node = (BoolBlock*)malloc(sizeof(BoolBlock));
    node->kind = B_NORM;
    node->block.current_bool.bool_val = val;
    node->block.next = next;
    return node;
}

BoolBlock* boolExpAnd(Expr* exp, BoolBlock* next){
    BoolBlock* node = (BoolBlock*)malloc(sizeof(BoolBlock));
    node->kind = B_EAND;
    node->block.current_bool.exp_val = exp;
    node->block.next = next;
    return node;
}

BoolBlock* boolExpOr(Expr* exp, BoolBlock* next){
    BoolBlock* node = (BoolBlock*)malloc(sizeof(BoolBlock));
    node->kind = B_EOR;
    node->block.current_bool.exp_val = exp;
    node->block.next = next;
    return node;
}

BoolBlock* boolExpBlock(Expr* exp, BoolBlock* next){
    BoolBlock* node = (BoolBlock*)malloc(sizeof(BoolBlock));
    node->kind = B_ENORM;
    node->block.current_bool.exp_val = exp;
    node->block.next = next;
    return node;
}


//Let---------------------------------------------------------------------------
Let* letCmd(char* varname){
    Let* node = (Let*)malloc(sizeof(Let));
    node->kind = LET_START;
    node->attr.op.var = varname;
    node->attr.op.value = NULL;
    return node;
}

Let* letShadow(char* varname, Expr* exp){
    Let* node = (Let*)malloc(sizeof(Let));
    node->kind = LET_SHADOW;
    node->attr.op.var = varname;
    node->attr.op.value = exp;
    return node;
}

//If----------------------------------------------------------------------------
If* ifExp(Expr* exp, CmdBlock* block){
    If* node = (If*)malloc(sizeof(If));
    node->kind = I_EXP;
    node->condition.exp_val = exp;
    node->if_block = block;
    return node;
}

If* ifBoolExp(BoolBlock* bool, CmdBlock* block){
    If* node = (If*)malloc(sizeof(If));
    node->kind = I_BO;
    node->condition.bool_val = bool;
    node->if_block = block;
    return node;
}

If* ifElseExp(Expr* exp, CmdBlock* block, Else* else_block){
    If* node = (If*)malloc(sizeof(If));
    node->kind = I_ELSE_EXP;
    node->condition.exp_val = exp;
    node->if_block = block;
    node->elseclause.else_val = else_block;
    return node;
}

If* ifElseBoolExp(BoolBlock* bool, CmdBlock* block, Else* else_block){
    If* node = (If*)malloc(sizeof(If));
    node->kind = I_ELSE_BO;
    node->condition.bool_val = bool;
    node->if_block = block;
    node->elseclause.else_val = else_block;
    return node;
}

Else* elseExp(CmdBlock* block){
    Else* node = (Else*)malloc(sizeof(Else));
    node->else_block = block;
    return node;
}

//CharBlock any sequence inside {}----------------------------------------------
CharBlock* addCharBlock(char* sentence, CharBlock* block){
    CharBlock* node = (CharBlock*)malloc(sizeof(CharBlock));
    node->val = sentence;
    node->next = block;
    return node;
}

//Print-------------------------------------------------------------------------
Print* printExp(char* sentence, CharBlock* var_block){
    Print* node = (Print*)malloc(sizeof(Print));
    node->string_val = sentence;
    node->vars = var_block;
    return node;
}

//Read--------------------------------------------------------------------------
Read* readExp(char* string, CharBlock* var_block){
    Read* node = (Read*)malloc(sizeof(Read));
    node->string_val = string;
    node->vars = var_block;
    return node;
}

//While-------------------------------------------------------------------------
While* whileExp(Expr* exp, CmdBlock* block){
    While* node = (While*)malloc(sizeof(While));
    node->kind = W_EXP;
    node->condition.exp_val = exp;
    node->while_block = block;
    return node;
}

While* whileBool(BoolBlock* bool, CmdBlock* block){
    While* node = (While*)malloc(sizeof(While));
    node->kind = W_BOOL;
    node->condition.bool_val = bool;
    node->while_block = block;
    return node;
}

//Comand and Comand block possible commands-------------------------------------
Cmd* cmdLet(Let*);
Cmd* cmdIf(If*);
Cmd* cmdWhile(While*);
Cmd* cmdPrint(Print*);
Cmd* cmdRead(Read*);

CmdBlock* addCmdBlock(Cmd*,CmdBlock*);