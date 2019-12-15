#include "parser.h"
#include "InstructionList.h"
#include "VarList.h"
#include "Mips.h"

#ifndef COMPILER_h
#define COMPILER_H


InstrList* compile(CmdBlock*);
InstrList* compileCmd(Cmd*);
InstrList* compileCmdBlock(CmdBlock*);

InstrList* compileWhile(While*);
InstrList* compileRead(Read*);
InstrList* compilePrint(Print*);
InstrList* compileLet(Let*);
InstrList* compileIf(If*);

InstrList* compileExp(Expr*);
InstrList* compileBoolBlock(BoolBlock*);
InstrList* compileBoolExp(BoolExpr*);

VarList* getCompilerVarList();
#endif