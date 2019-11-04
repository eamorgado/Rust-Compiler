#ifndef ABSTRACT_TREE_H
#define ABSTRACT_TREE_H

/*------------------------------------------------------------------------------
                            Types definitions
------------------------------------------------------------------------------*/
typedef struct _Expr{
    enum{E_INTEGER, E_OPERATION, E_VAR}kind;
    union{
        int value; //value for integers
        char* var; //value for vars
        struct {
            int operator; //+ - * / %
            struct _Expr* left;
            struct _Expr* right;
        }op;
    }attr;
}Expr;

typedef struct _Let{
    enum{LET_START, LET_SHADOW}kind;
    union{
        struct{
            char* var;
            Expr* value;
        }op;
    }attr;
}Let;

typedef struct _BoolExpr{
    enum{B_BOOL, B_BOOLOP}kind; //{true,false} {!, ==, !=, <,>,<=,>=}
    union{
        Expr* value; //var with value true or false
        struct{
            int operator;
            Expr* left;
            Expr* right;
        }op;
    }attr;
}BoolExpr;

typedef struct _BoolBlock{
    enum{B_AND, B_OR, B_NORM, B_EAND, B_EOR, B_ENORM}kind;
    struct{
        union{
            BoolExpr* bool_val;
            Expr* exp_val;
        }current_bool;
        struct _BoolBlock* next;
    }block;
}BoolBlock;

typedef struct _CharBlock{
    char* val;
    struct _CharBlock* next;
}CharBlock;

typedef struct _Print{
    char* string_val;
    CharBlock* vars;
}Print;

typedef struct _Read{
    char* string_val;
    CharBlock* vars;
}Read;

typedef struct _Cmd{
    enum{E_WHILE, E_PRINT, E_READ, E_IF, E_LET}kind;
    union{
        Let* let;
        Print* print;
        Read* read;
        If* If;
        While* While;
    }type;
}Cmd;

typedef struct _CmdBlock{
    Cmd* cmd;
    struct _CmdBlock* next;
}CmdBlock;

typedef struct _While{
    enum{W_EXP, W_BOOL}kind;
    union{
        BoolBlock* bool_val;
        Expr* exp_val;
    }condition;
    CmdBlock* while_block;
}While;

typedef struct _If{
    enum{I_EXP, I_BO, I_ELSE_EXP, I_ELSE_BO}kind;
    union{
        BoolBlock* bool_val;
        Expr* exp_val;
    }condition;
    union{
        Else* else_val;
    }elseclause;
    CmdBlock* if_block;
}If;

typedef struct _Else{
    CmdBlock* else_block;
}Else;



/*------------------------------------------------------------------------------
                                Constructors
------------------------------------------------------------------------------*/

//Expressions-------------------------------------------------------------------
Expr* expInt(int);
Expr* expVar(char*);
Expr* exprOp(int,Expr*,Expr*);

//Bool Expressions--------------------------------------------------------------
BoolExpr* boolNorm(Expr*);
BoolExpr* boolExp(int,Expr*,Expr*); //== != < > >= <=

//Bool Block any sequence with || or &&-----------------------------------------
BoolBlock* boolAnd(BoolExpr*,BoolBlock*);
BoolBlock* boolOr(BoolExpr*,BoolBlock*);
BoolBlock* boolBlock(BoolExpr*,BoolBlock*);

BoolBlock* boolExpAnd(Expr*,BoolBlock*);
BoolBlock* boolExpOr(Expr*,BoolBlock*);
BoolBlock* boolExpBlock(Expr*,BoolBlock*);

//Let---------------------------------------------------------------------------
Let* letCmd(char*);
Let* letShadow(char*,Expr*);

//If----------------------------------------------------------------------------
If* ifExp(Expr*,CmdBlock*);
If* ifBoolExp(BoolBlock*,CmdBlock*);
If* ifElseExp(Expr*,CmdBlock*,Else*);
If* ifElseBoolExp(BoolBlock*,CmdBlock*,Else*);
Else* elseExp(CmdBlock*);

//CharBlock any sequence inside {}----------------------------------------------
CharBlock* addCharBlock(char*,CharBlock*);

//Print-------------------------------------------------------------------------
Print* printExp(char*,CharBlock*);

//Read--------------------------------------------------------------------------
Read* readExp(char*,CharBlock*);

//While-------------------------------------------------------------------------
While* whileExp(Expr*,CmdBlock*);
While* whileBool(BoolBlock*,CmdBlock*);

//Comand and Comand block possible commands-------------------------------------
Cmd* cmdAttrib(Attrib*);
Cmd* cmdLet(Let*);
Cmd* cmdLetMut(Let*);
Cmd* cmdIf(If*);
Cmd* cmdWhile(While*);
Cmd* cmdPrint(Print*);
Cmd* cmdRead(Read*);

CmdBlock* addCmdBlock(Cmd*,CmdBlock*);


#endif