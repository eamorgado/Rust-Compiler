#include <stdlib.h>
#include "Instruction.h"
#include "InstructionList.h"

InstrNode* makeInstrNode(){
    InstrNode* node = (InstrNode*)malloc(sizeof(InstrNode));
    if(!node) perror("makeInstrNode: ERROR making node");
    return node;
}
InstrNode* makeInstrNodeComplex(Instr* instr){
    InstrNode* node = makeInstrNode();
    VALINS(node) = instr;
    NEXTINS(node) = NULL;
    return node;
}

InstrList* makeInstrList(){
    InstrList* list = (InstrList*)malloc(sizeof(InstrList));
    if(!list) perror("makeInstrList: ERROR making list");
    SIZEINS(list) = 0;
    FIRSTINS(list) = LASTINS(list) = NULL;
}

Instr* headList(InstrList* list){
    if(SIZEINS(list) == 0) return NULL;
    return VALINS(FIRSTINS(list));
}

Instr* tailList(InstrList* list){
    if(SIZEINS(list) == 0) return NULL;
    return VALINS(LASTINS(list));
}


void prependList(Instr* instr,InstrList* list){
    InstrNode* node = makeInstrNodeComplex(instr);
    if(SIZEINS(list) == 0) LASTINS(list) = node;
    else NEXTINS(node) = FIRSTINS(list);
    FIRSTINS(list) = node;
    SIZEINS(list)++;
}

void appendList(Instr* instr,InstrList* list){
    InstrNode* node = makeInstrNodeComplex(instr);
    if(SIZEINS(list) == 0) FIRSTINS(list) = node;
    else NEXTINS(LASTINS(list)) = node;
    LASTINS(list) = node;
    SIZEINS(list)++;
}


void removeFirstInstrList(InstrList* list){
    if(SIZEINS(list) == 0) return;
    InstrNode* node = FIRSTINS(list);
    if(SIZEINS(list) == 1) FIRSTINS(list) = LASTINS(list) = NULL;
    else FIRSTINS(list) = NEXTINS(node);
    freeInstr(VALINS(node));
    free(node);
    SIZEINS(list)--;
}
void removeLastInstrList(InstrList* list){
    if(SIZEINS(list) == 0) return;
    if(SIZEINS(list) == 1){removeFirstInstrList(list); return;}
    InstrNode* node = FIRSTINS(list);
    while(NEXTINS(NEXTINS(node)) != NULL) node = NEXTINS(node);
    LASTINS(list) = node;
    node = NEXTINS(node);
    NEXTINS(LASTINS(list)) = NULL;
    freeInstr(VALINS(node));
    free(node);
    SIZEINS(list)--; 

}


InstrList* concatenateList(InstrList*,InstrList*);


void freeInstrList(InstrList*);
void printInstrList(InstrList*);