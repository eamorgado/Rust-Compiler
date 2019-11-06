#ifndef ABSTRACT_TREE_H
#define ABSTRACT_TREE_H

/*------------------------------------------------------------------------------
                            Types definitions
------------------------------------------------------------------------------*/
typedef struct express{
    enum{E_INT, E_OPERATION, E_VAR}kind;
    union{
        int value; //value for integers
        char* var; //value for vars
        struct {
            int operator; //+ - * / %
            struct express* left;
            struct express* right;
        }op;
    }attr;
}Expr;

typedef struct boolexp{
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

typedef struct boolstring{
    enum{B_AND, B_OR, B_NORM, B_EAND, B_EOR, B_ENORM}kind;
    struct{
        union{
            BoolExpr* bool_val;
            Expr* exp_val;
        }current_bool;
        struct boolstring* next;
    }block;
}BoolBlock;

typedef struct letstatement{
    enum{L_START, L_SH_EXP, L_SH_BOOL, L_SH_BLOCK}kind;
    char* varname;
    struct{
        Expr* exp_value;
        BoolExpr* bool_value;
        BoolBlock* bool_block;
    }initialize;
}Let;

typedef struct println_macro{
    enum{P_VAR, P_EXP, P_BOOL, P_BOOLBLOCK}kind;
    union{
        char* varname;
        Expr* exp;
        BoolExpr* bool;
        BoolBlock* block;
    }printstring;
}Print;

typedef struct read_line{
    char* varname;
}Read;

typedef struct instruction_cmd{
    enum{C_WHILE, C_PRINT, C_READ, C_IF, C_LET}kind;
    union{
        Let* let_cmd;
        Print* print_cmd;
        Read* read_cmd;
        struct if_command* if_cmd;
        struct while_command* while_cmd;
    }command;
}Cmd;

typedef struct command_sequence{
    Cmd* cmd;
    struct command_sequence* next;
}CmdBlock;

struct while_command{
    enum{W_EXP, W_BOOL}kind;
    union{
        BoolBlock* bool_val;
        Expr* exp_val;
    }condition;
    CmdBlock* while_block;
};

struct if_command{
    enum{I_EXP, I_BO, I_ELSE_EXP, I_ELSE_BO}kind;
    union{
        BoolBlock* bool_val;
        Expr* exp_val;
    }condition;
    union{
        struct else_command* else_val;
    }elseclause;
    CmdBlock* if_block;
};

struct else_command{
    CmdBlock* else_block;
};

typedef struct while_command While;
typedef struct if_command If;
typedef struct else_command Else;
/*------------------------------------------------------------------------------
                                Constructors
------------------------------------------------------------------------------*/

//Expressions-------------------------------------------------------------------
Expr* expInt(int);
Expr* expVar(char*);
Expr* expOp(int,Expr*,Expr*);

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
Let* letShadowExp(char*,Expr*);
Let* letShadowBool(char*,BoolExpr*);
Let* letShadowBoolBlock(char*,BoolBlock*);

//If----------------------------------------------------------------------------
If* ifExp(Expr*,CmdBlock*);
If* ifBoolExp(BoolBlock*,CmdBlock*);
If* ifElseExp(Expr*,CmdBlock*,Else*);
If* ifElseBoolExp(BoolBlock*,CmdBlock*,Else*);
Else* elseExp(CmdBlock*);

//Print-------------------------------------------------------------------------
Print* printExp(Expr*);
Print* printVar(char*);
Print* printBool(BoolExpr*);
Print* printBoolBlock(BoolBlock*);

//Read--------------------------------------------------------------------------
Read* readLine(char*);

//While-------------------------------------------------------------------------
While* whileExp(Expr*,CmdBlock*);
While* whileBool(BoolBlock*,CmdBlock*);

//Comand and Comand block possible commands-------------------------------------
Cmd* cmdLet(Let*);
Cmd* cmdLetMut(Let*);
Cmd* cmdIf(If*);
Cmd* cmdWhile(While*);
Cmd* cmdPrint(Print*);
Cmd* cmdRead(Read*);

CmdBlock* addCmdBlock(Cmd*,CmdBlock*);


#endif