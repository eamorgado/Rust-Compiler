#include <stdio.h>
#include <stdlib.h>

#include "abstree.h"
#include "parser.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "VarList.h"

VarList* vars;
VarList* getCompilerVarList(){
    return vars;
}
InstrList* compile(CmdBlock* block){
    vars = makeVarList();
    return compileCmdBlock(block);
}
InstrList* compileCmdBlock(CmdBlock* block){
    if(!block) return NULL;

    InstrList* next = compileCmdBlock(block->next);
    InstrList* node = compileCmd(block->cmd);

    return !node ? next : concatenateList(node,next);
}

InstrList* compileCmd(Cmd* cmd){
    switch(cmd->kind){
        case C_WHILE: return compileWhile(cmd->command.while_cmd);
        case C_PRINT: return compilePrint(cmd->command.print_cmd);
        case C_READ: return compileRead(cmd->command.read_cmd);
        case C_IF: return compileIf(cmd->command.if_cmd);
        case C_LET: return compileLet(cmd->command.let_cmd);
        default: return NULL;
    }
}


InstrList* compileWhile(While* cmd){
    //[label start] ++ code1 ++ [label l1] ++ code2 ++ [goto start] ++ [label l2]
    int loop_start = getLabel(); incLabel();
    int loop_end = getLabel(); incLabel();

    InstrList* list = makeInstrList();
    //label start
    appendList(makeInstructionLabel(loop_start),list);
    if(cmd->kind == W_EXP) concatenateList(list,compileExp(cmd->condition.exp_val));
    else concatenateList(list,compileBoolBlock(cmd->condition.bool_val));
    //l2
    appendList(makeInstructionJump(0,loop_end),list);
    //code1
    concatenateList(list,compileCmdBlock(cmd->while_block));
    appendList(makeInstructionJump(1,loop_start),list);
    //
    appendList(makeInstructionLabel(loop_end),list);
    return list;
}

InstrList* compileRead(Read* cmd){
    //read(var)
    if(!containsVarList(cmd->varname,vars)) appendVarList(cmd->varname,vars);
    InstrList* list = makeInstrList();
    appendList(makeInstructionRead(cmd->varname),list);
    return list;
}

InstrList* compilePrint(Print* cmd){
    InstrList* list = makeInstrList();
    switch(cmd->kind){
        case P_VAR: 
            appendList(makeInstructionWrite(cmd->printstring.varname),list);
            return list;
            break;
        case P_EXP: 
        case P_BOOL:
        case P_BOOLBLOCK:
        break;
    }
    return NULL;
}
InstrList* compileLet(Let* cmd){
    if(!containsVarList(cmd->varname,vars)) appendVarList(cmd->varname,vars);
    InstrList* list = makeInstrList();
    appendList(makeInstructionLetVar(cmd->varname),freeInstrList);
    InstrList* content = NULL;
    switch(cmd->kind){
        case L_START: concatenateList(list,makeInstrList()); return list; break;
        case L_SH_EXP: content = compileExp(cmd->initialize.exp_value); break;
        case L_SH_BOOL: content = compileBoolExp(cmd->initialize.bool_value); break;
        case L_SH_BLOCK: content = compileBoolBlock(cmd->initialize.bool_block); break;
    }
    concatenateList(list,content);
    appendList(makeInstructionStore(cmd->varname),list);
    return list;
}
InstrList* compileIf(If* cmd){
    InstrList* list = NULL;
    int if_end= getLabel(); incLabel();
    int else_end = getLabel();
    if(cmd->kind == I_ELSE_EXP || cmd->kind == I_ELSE_BO) incLabel();
    if(cmd->kind == I_EXP || cmd->kind == I_ELSE_EXP) list = compileExp(cmd->condition.exp_val);
    else list = compileBoolBlock(cmd->condition.bool_val);
    appendList(makeInstructionJump(0,if_end),list);
    concatenateList(list,compileCmdBlock(cmd->if_block));
    
    if(cmd->kind == I_EXP || cmd->kind == I_BO){
        appendList(makeInstructionLabel(if_end),list);
        return list;
    }

    appendList(makeInstructionJump(1,else_end),list);
    appendList(makeInstructionLabel(if_end),list);
    concatenateList(list,compileCmdBlock(cmd->elseclause.else_val));
    appendList(makeInstructionLabel(else_end),list);
    return list;


}

InstrList* compileExp(Expr* exp){
    InstrList* list = makeInstrList();
    if(exp->kind == E_INT || exp->kind == E_VAR){
        if(exp->kind == E_VAR && !containsVarList(exp->attr.var,vars)) perror("ERROR: Var %s used without being defined",exp->attr.var);
        Instr* ins;
        ins = (exp->kind == E_INT)? makeInstructionNum(exp->attr.value) : makeInstructionVar(exp->attr.var);
        appendList(ins,list);
        return list;
    }
    if(exp->kind != E_OPERATION) return NULL;
    concatenateList(list,compileExp(exp->attr.op.left));
    concatenateList(list,compileExp(exp->attr.op.right));
    Type t;
    switch(exp->attr.op.operator){
        case ADD_OP: t = INS_ADD; break;
        case SUB_OP: t = INS_SUB; break;
        case MULT_OP: t = INS_MUL; break;
        case DIV_OP: t = INS_DIV; break;
        case MOD_OP: t = INS_MOD; break;
    }
    appendList(makeInstruction(t),list);
    return list;   
}
InstrList* compileBoolBlock(BoolBlock* block){
    InstrList* list = NULL;
    if(block->kind == B_NORM){
        list = compileExp(block->block.current_bool.exp_val);
        appendList(makeInstructionNum(0),list);
        appendList(makeInstruction(INS_NEQ),list);
    }else if(block->kind == B_ENORM)
        list = compileBoolExp(block->block.current_bool.bool_val);
    return list;
}
InstrList* compileBoolExp(BoolExpr* exp){
    InstrList* list = makeInstrList();
    if(exp->kind == B_BOOL){
        concatenateList(compileExp(exp->attr.value),list);
        appendList(makeInstructionNum(0),list);
        appendList(makeInstruction(INS_NEQ),list);
        return list;
    }
    Type t;
    switch(exp->attr.op.operator){
        case EQ_OP: t = INS_EQ; break;
        case GRT_OP: t = INS_GT; break;
        case LT_OP: t = INS_LT; break;
        case GRT_EQ_OP: t = INS_GEQ; break;
        case LT_EQ_OP: t = INS_LEQ; break;
    }
    concatenateList(compileExp(exp->attr.op.left),list);
    concatenateList(compileExp(exp->attr.op.right),list);
    appendList(makeInstruction(t),list);
    return list;
}