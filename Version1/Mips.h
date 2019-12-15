#include "parser.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "VarList.h"

#ifndef MIPS_H
#define MIPS_H

int IT_LABEL;

void giveTab();
void giveEnter();
int getLabel();
void incLabel();
void decLabel();
void mipsSyscall(int);
void mipsLoad(char*);
void mipsStore(char*);
void mipsCompare(char*);
void mipsCompareSub(char*);
void printMips(InstrList*);

#endif