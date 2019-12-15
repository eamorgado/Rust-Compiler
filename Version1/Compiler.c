#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "VarList.h"
#include "Mips.h"
#include "Compiler.h"

VarList* vars;
VarList* getCompilerVarList(){
    return vars;
}
InstrList* compile(CmdBlock* block){
    //printf("Started\n");
    vars = makeVarList();
    //printf("Added Var List\n");
    InstrList* list = makeInstrList();
    //printf("Made Instruction List\n");
    appendList(makeInstructionLabel(getLabel()),list); incLabel();
    //printf("Made Label\n");
    list = concatenateList(list,compileCmdBlock(block));
    //printf("Ended compilation\n");
    return list;
}

InstrList* compileCmdBlock(CmdBlock* block){
    if(!block) return NULL;
    InstrList* list = makeInstrList();
    InstrList* tmp = compileCmd(block->cmd);
    list = concatenateList(list,tmp);
    //printf("Compiled command in block\n");
    while(block->next != NULL){
        block = block->next;
        tmp = compileCmd(block->cmd);
        list = concatenateList(list,tmp);
    }
    return  list;
}

InstrList* compileCmd(Cmd* cmd){
    InstrList* list;
    switch(cmd->kind){
        case C_WHILE: list = compileWhile(cmd->command.while_cmd); break;
        case C_PRINT: list = compilePrint(cmd->command.print_cmd); break;
        case C_READ: list = compileRead(cmd->command.read_cmd); break;
        case C_IF: list = compileIf(cmd->command.if_cmd); break;
        case C_LET: list = compileLet(cmd->command.let_cmd); break;
    }
    return list;
}


InstrList* compileWhile(While* cmd){
    //[label start] ++ code1 ++ [label l1] ++ code2 ++ [goto start] ++ [label l2]
    int loop_start = getLabel(); incLabel();
    int loop_end = getLabel(); incLabel();

    InstrList* list = makeInstrList();
    //label start
    appendList(makeInstructionLabel(loop_start),list);
    if(cmd->kind == W_EXP) list = concatenateList(list,compileExp(cmd->condition.exp_val));
    else list = concatenateList(list,compileBoolBlock(cmd->condition.bool_val));
    //l2
    appendList(makeInstructionJumpFalse(loop_end),list);
    //code1
    list = concatenateList(list,compileCmdBlock(cmd->while_block));
    appendList(makeInstructionJumpUn(loop_start),list);
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
    appendList(makeInstructionLetVar(cmd->varname),list);
    InstrList* content = NULL;
    switch(cmd->kind){
        case L_START: list = concatenateList(list,makeInstrList()); appendList(makeInstructionStore(cmd->varname),list); return list; break;
        case L_SH_EXP: content = compileExp(cmd->initialize.exp_value); break;
        case L_SH_BOOL: content = compileBoolExp(cmd->initialize.bool_value); break;
        case L_SH_BLOCK: content = compileBoolBlock(cmd->initialize.bool_block); break;
    }
    list = concatenateList(list,content);
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
    appendList(makeInstructionJumpFalse(if_end),list);
    list = concatenateList(list,compileCmdBlock(cmd->if_block));
    
    if(cmd->kind == I_EXP || cmd->kind == I_BO){
        appendList(makeInstructionLabel(if_end),list);
        return list;
    }

    appendList(makeInstructionJumpUn(else_end),list);
    appendList(makeInstructionLabel(if_end),list);
    list = concatenateList(list,compileCmdBlock(cmd->elseclause.else_val->else_block));
    appendList(makeInstructionLabel(else_end),list);
    return list;


}

InstrList* compileExp(Expr* exp){
    InstrList* list = makeInstrList();
    if(exp->kind == E_INT || exp->kind == E_VAR){
        if(exp->kind == E_VAR && !containsVarList(exp->attr.var,vars)) perror("ERROR: Var used without being defined");
        Instr* ins;
        ins = (exp->kind == E_INT)? makeInstructionNum(exp->attr.value) : makeInstructionVar(exp->attr.var);
        appendList(ins,list);
        return list;
    }
    if(exp->kind != E_OPERATION) return NULL;
    list = concatenateList(list,compileExp(exp->attr.op.left));
    list = concatenateList(list,compileExp(exp->attr.op.right));
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
        list = concatenateList(compileExp(exp->attr.value),list);
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
    list = concatenateList(compileExp(exp->attr.op.left),list);
    list = concatenateList(compileExp(exp->attr.op.right),list);
    appendList(makeInstruction(t),list);
    return list;
}