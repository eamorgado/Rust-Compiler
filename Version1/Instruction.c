#include <stdlib.h>
#include "Instruction.h"

Atom* makeAtomVar(char* name){
    Atom* atom = (Atom*)malloc(sizeof(Atom));
    if(!atom) perror("makeAtomVar: ERROR making atom");
    TYPE_ATOM(atom) = VAR;
    VAR_ATOM(atom) = name;
    return atom;
}
Atom* makeAtomNum(int num){
    Atom* atom = (Atom*)malloc(sizeof(Atom));
    if(!atom) perror("makeAtomNum: ERROR making atom");
    TYPE_ATOM(atom) = NUM;
    NUM_ATOM(atom) = num;
    return atom;
}

void printAtom(Atom* atom){
    if(TYPE_ATOM(atom) == VAR)
        printf("%s",VAR_ATOM(atom));
    else printf("%d",NUM_ATOM(atom));
}

/*Instr* makeInstrSingle(Atom* atom){
    Instr* instr = (Instr*)malloc(sizeof(Instr));
    if(!instr) perror("makeInstrSingle: ERROR making instruction");
    TYPE(instr) = I_SINGLE;
    SINGE_INS(instr) = atom;
    return instr;
}
Instr* makeInstrBinop(int op,Atom* a1,Atom* a2){
    Instr* instr = (Instr*)malloc(sizeof(Instr));
    if(!instr) perror("makeInstrSingle: ERROR making instruction");
    KIND_INS(instr) = I_BINOM;
    BIN_INS(instr) = op;
    A1_INS(instr) = a1;
    A2_INS(instr) = a2;
}*/

Instr* makeInstruction(Type type){
    //Makes empty instruction
    Instr* instr = (Instr*)malloc(sizeof(Instr));
    if(!instr) perror("makeInstruction: ERROR making instruction");
    TYPE_INS(instr) = type;
    return instr; 
}

Instr* makeInstructionNum(int num){
    Instr* instr = makeInstruction(INS_LOAD_NUM);
    SINGE_INS(instr) = makeAtomNum(num);
    return instr;
}

Instr* makeInstructionVar(char* name){
    Instr* instr = makeInstruction(INS_LOAD_VAR);
    SINGE_INS(instr) = makeAtomVar(name);
    return instr;
}

Instr* makeInstructionStore(char* var){
    Instr* instr = makeInstruction(INS_STORE);
    SINGE_INS(instr) = makeAtomVar(var);
    return instr;
}

Instr* makeInstructionRead(char* var){
    Instr* instr = makeInstruction(INS_READ);
    SINGE_INS(instr) = makeAtomVar(var);
    return instr;
}

Instr* makeInstructionWrite(char* var){
    Instr* instr = makeInstruction(INS_PRINT);
    SINGE_INS(instr) = makeAtomVar(var);
    return instr;
}

Instr* makeInstructionLabel(int label){
    Instr* instr = makeInstruction(INS_LABEL);
    SINGE_INS(instr) = makeAtomNum(label);
    return instr;
}

Instr* makeInstructionLetVar(char* var){
    Instr* instr = makeInstruction(INS_VAR);
    SINGE_INS(instr) = makeAtomVar(var);
    return instr;
}


void freeInstr(Instr*){
    
}
void printInstr(Instr* instr){
    int flag = 0;
    switch(TYPE_INS(instr)){
        case INS_ADD: flag = 1; printf("ADI\n"); break;
        case INS_SUB: flag = 1; printf("SBI\n"); break;
        case INS_MUL: flag = 1; printf("MPI\n"); break;
        case INS_DIV: flag = 1; printf("DVI\n"); break;
        case INS_MOD: flag = 1; printf("MOD\n"); break;
        case INS_EQ: flag = 1; printf("EQU\n"); break;
        case INS_GT: flag = 1; printf("GES\n"); break;
        case INS_GEQ: flag = 1; printf("GEQ\n"); break;
        case INS_LT: flag = 1; printf("LES\n"); break;
        case INS_LEQ: flag = 1; printf("LEQ\n"); break;
        case INS_NEQ: flag = 1; printf("NEQ\n"); break;
    }
    if(flag) return;
    switch(TYPE_INS(instr)){
        case INS_READ: printf("READ "); break;
        case INS_PRINT: printf("WRT "); break;
        case INS_LABEL: printf("L "); break;
        case INS_LOAD_VAR: printf("LOD "); break;
        case INS_LOAD_NUM: printf("LDC "); break;
        case INS_STORE: printf("STO "); break;
    }
    printAtom(SINGE_INS(instr));
    printf("\n");
}