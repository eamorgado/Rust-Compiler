#include "abstree.h"
#include "InstructionList.h"
#include "VarList.h"

#ifndef COMPILER_h
#define COMPILER_H

InstrList* compileCmd(Cmd*);
InstrList* compileCmdBlock(CmdBlock*);

InstrList* compileWhile(While*);
InstrList* compileRead(Read*);
InstrList* compilePrint(Print*);
InstrList* compileLet(Let*);
InstrList* compileIf(If*);
InstrList* compileElse(Else*);

InstrList* compileExp(Expr*);
InstrList* compileBoolBlock(BoolBlock*);
InstrList* compileBoolExp(BoolExpr*);

InstrList* compile(CmdBlock*,VarList*);
#endif