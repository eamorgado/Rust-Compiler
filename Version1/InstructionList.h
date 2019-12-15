#include "Instruction.h"

#ifndef INSTRUCTION_LIST_H
#define INSTRUCTION_LIST_H

#define NEXTINS(IN) ((IN)->next)
#define VALINS(IN) ((IN)->instruction)

#define FIRSTINS(IL) ((IL)->first)
#define LASTINS(IL) ((IL)->last)
#define SIZEINS(IL) ((IL)->size)

typedef struct _instnode{
    Instr* instruction;
    struct _instnode* next;
}InstrNode;

typedef struct _instlist{
    int size;
    InstrNode* first;
    InstrNode* last;
}InstrList;

InstrNode* makeInstrNode();
InstrNode* makeInstrNodeComplex(Instr*);
void printInstructionNode(InstrNode*);
void freeInstrNode(InstrNode*,InstrNode*);

InstrList* makeInstrList();
Instr* headList(InstrList*);
Instr* tailList(InstrList*);

void prependList(Instr*,InstrList*);
void appendList(Instr*,InstrList*);

void removeFirstInstrList(InstrList*);
void removeLastInstrList(InstrList*);

InstrList* concatenateList(InstrList*,InstrList*);

void freeInstrList(InstrList*);
void printInstrList(InstrList*);

#endif