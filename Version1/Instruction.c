#include <stdlib.h>
#include <stdio.h>
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

void freeAtom(Atom* atom){
    if(TYPE_ATOM(atom) == VAR) free(VAR_ATOM(atom));
    free(atom);
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
    Instr* instr = makeInstruction(INS_WRITE);
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

Instr* makeInstructionJumpFalse(int label){
    Instr* instr = makeInstruction(INS_JFALSE);
    SINGE_INS(instr) = makeAtomNum(label);
    return instr;
}
Instr* makeInstructionJumpUn(int label){
    Instr* instr = makeInstruction(INS_JUNCON);
    SINGE_INS(instr) = makeAtomNum(label);
    return instr;
}


void freeInstr(Instr* instr){
    freeAtom(SINGE_INS(instr));  
    free(instr);  
}

void printInstr(Instr* instr){
    int flag = 0;
    switch(TYPE_INS(instr)){
        case INS_ADD: flag = 1; printf("ADD\n"); break;
        case INS_SUB: flag = 1; printf("SUB\n"); break;
        case INS_MUL: flag = 1; printf("MULT\n"); break;
        case INS_DIV: flag = 1; printf("DIV\n"); break;
        case INS_MOD: flag = 1; printf("MOD\n"); break;
        case INS_EQ: flag = 1; printf("EQUAL\n"); break;
        case INS_GT: flag = 1; printf("GREATER_THAN\n"); break;
        case INS_GEQ: flag = 1; printf("GREATER_EQUAL\n"); break;
        case INS_LT: flag = 1; printf("LESS_THAN\n"); break;
        case INS_LEQ: flag = 1; printf("LESS_EQUAL\n"); break;
        case INS_NEQ: flag = 1; printf("NON_EQUAL\n"); break;
    }
    if(flag) return;
    switch(TYPE_INS(instr)){
        case INS_VAR: printf("DECLARE "); break;
        case INS_READ: printf("READ "); break;
        case INS_WRITE: printf("WRITE "); break;
        case INS_LABEL: printf("LABEL "); break;
        case INS_LOAD_VAR: printf("LOAD_VAR "); break;
        case INS_LOAD_NUM: printf("LOAD_CONST "); break;
        case INS_STORE: printf("STORE "); break;
        case INS_JFALSE: printf("JUMP_ON_FALSE L"); break;
        case INS_JUNCON: printf("JUMP_UNCONDITIONAL L"); break;
    }
    printAtom(SINGE_INS(instr));
    printf("\n");
}