#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define TYPE_ATOM(A) ((A)->type)
#define VAR_ATOM(A) ((A)->content.var)
#define NUM_ATOM(A) ((A)->content.num)


#define TYPE_INS(I) ((I)->type)
#define SINGE_INS(I) ((I)->content.v)
#define A1_INS(I) ((I)->content->content_binon->a1)
#define A2_INS(I) ((I)->content->content_binon->a2)


typedef enum{
    INS_VAR,        //Variable was declared
    INS_WRITE,      //print
    INS_READ,       //read

    INS_ADD,
    INS_SUB,
    INS_MUL,
    INS_DIV,
    INS_MOD,

    INS_EQ,
    INS_GT,
    INS_GEQ,
    INS_LT,
    INS_LEQ,
    INS_NEQ,

    INS_LABEL,

    INS_LOAD_VAR,   //Instruction has variable saved
    INS_LOAD_NUM,   //Instruction has num saved
    INS_STORE,

    INS_JFALSE,
    INS_JUNCON
}Type;

typedef struct _atom{
    enum{VAR,NUM}type;
    union{
        char* var;
        int num;
    }content;
}Atom;

typedef struct _instruct{
    Type type;
    union{
        Atom* v;
        struct{
            Atom* a1;
            Atom* a2;
        }content_binon;
    }content;
}Instr;

Atom* makeAtomVar(char*);
Atom* makeAtomNum(int);
void printAtom(Atom*);
void freeAtom(Atom*);

Instr* makeInstruction(Type);
Instr* makeInstructionNum(int);
Instr* makeInstructionVar(char*);
Instr* makeInstructionStore(char*);//address

Instr* makeInstructionRead(char*);
Instr* makeInstructionWrite(char*);
Instr* makeInstructionLabel(int);
Instr* makeInstructionLetVar(char*);

Instr* makeInstructionJump(int,int);

//Instr* makeInstrSingle(int,Atom*);
//Instr* makeInstrComplex(int,Atom*,Atom*);

void freeInstr(Instr*);
void printInstr(Instr*);

#endif