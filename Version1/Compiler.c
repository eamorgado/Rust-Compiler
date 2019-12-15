#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>

#include "abstree.h"
#include "parser.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "Mips.h"
#include "VarList.h"

VarList* vars;

InstrList* compile(CmdBlock* block,VarList* v){
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
    switch(cmd->kind){
        case L_START:
            appendList()
        case L_SH_EXP:
        case L_SH_BOOL:
        case L_SH_BLOCK:
    }
}
InstrList* compileIf(If*);
InstrList* compileElse(Else*);

InstrList* compileExp(Expr*);
InstrList* compileBoolBlock(BoolBlock*);
InstrList* compileBoolExp(BoolExpr*);