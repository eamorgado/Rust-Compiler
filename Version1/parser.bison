//Tokens
%token READ_CMD PRINT_CMD
%token ADD_OP SUB_OP MULT_OP MOD_OP DIV_OP
%token AND_OP OR_OP NOT_OP EQ_OP NOT_EQ_OP
%token GRT_OP LT_OP GRT_EQ_OP LT_EQ_OP
%token ATTR_O
%token F_MAIN F_DEC
%token LET_OP
%token IF_OP ELSE_OP
%token WHILE_OP
%token OPEN_BRACKET CLOSE_BRACKET
%token OPEN_PARENT CLOSE_PARENT
%token SEMICOLON
%token VARNAME INT


//Token precedence
%left F_DEC F_MAIN LET_OP ATTR_OP
//Token precedence
%left SEMICOLON
%left AND_OP OR_OP
%left GRT_OP GRT_EQ_OP LT LT_EQ_OP EQ_OP NOT_EQ_OP
%left ADD_OP SUB_OP
%left MULT_OP DIV_OP MOD_OP



//root grammar symbol
%start program;


%union{
    int int_val;
    Expr* exp_val;
    BoolExpr* boolexp_val;
    BoolBlock* boolblock_val;
    char* var_val;
    Print* print_val;
    Read* read_val;
    Let* let_val;
    Cmd* cmd_val;
    CmdBlock* cmdblock_val;
    While* while_val;
    If* if_val;
    Else* else_val;
}

%type <int_val> INT;
%type <exp_val> exp;
%type <boolexp_val> bool_exp;
%type <boolblock_val> bool_block;
%type <var_val> VARNAME;
%type <let_val> let;
%type <print_val> println;
%type <read_val> read_line;
%type <cmd_val> cmd;
%type <cmdblock_val> cmd_block;
%type <while_val> while;
%type <if_val> if;
%type <else_val> else;


%code requires{
    #include <stdio.h>
    #include <stdlib.h>
    #include "abstree.h"
    
    extern int yylex();
    extern int yyline;
    extern char* yytext;
    extern FILE* yyin;
    extern void yyerror(const char* errormsg);

    CmdBlock* root;
}


%%

program:
    F_DEC F_MAIN OPEN_PARENT CLOSE_PARENT OPEN_BRACKET cmd_block CLOSE_BRACKET
        {root = $6;};

cmd_block:  cmd cmd_block   {$$ = addCmdBlock($1,$2);}
        |   cmd             {$$ = addCmdBlock($1,NULL);};


cmd:  let       {$$ = cmdLet($1);}
    | while     {$$ = cmdWhile($1);}
    | println   {$$ = cmdPrint($1);}
    | read_line {$$ = cmdRead($1);}
    | if        {$$ = cmdIf($1);};


println:   PRINT_CMD OPEN_PARENT exp CLOSE_PARENT SEMICOLON        {$$ = printExp($3);}
       |   PRINT_CMD OPEN_PARENT VARNAME CLOSE_PARENT SEMICOLON    {$$ = printVar($3);}
       |   PRINT_CMD OPEN_PARENT bool_exp CLOSE_PARENT SEMICOLON   {$$ = printBool($3);}
       |   PRINT_CMD OPEN_PARENT bool_block CLOSE_PARENT SEMICOLON {$$ = printBoolBlock($3);};

read_line:  READ_CMD OPEN_PARENT VARNAME CLOSE_PARENT SEMICOLON     {$$ = readLine($3);};

let:     LET_OP VARNAME SEMICOLON                       {$$ = letCmd($2);}
    |    LET_OP VARNAME ATTR_OP exp SEMICOLON           {$$ = letShadowExp($2,$4);}
    |    LET_OP VARNAME ATTR_OP bool_exp SEMICOLON      {$$ = letShadowBool($2,$4);}
    |    LET_OP VARNAME ATTR_OP bool_block SEMICOLON    {$$ = letShadowBoolBlock($2,$4);}

exp:    INT             {$$ = expInt($1);}
    |   VARNAME         {$$ = expVar($1);}
    |   exp ADD_OP exp  {$$ = expOp(ADD_OP,$1,$3);}
    |   exp SUB_OP exp  {$$ = expOp(SUB_OP,$1,$3);}
    |   exp MULT_OP exp {$$ = expOp(MULT_OP,$1,$3);}
    |   exp DIV_OP exp  {$$ = expOp(DIV_OP,$1,$3);}
    |   exp MOD_OP exp  {$$ = expOp(MOD_OP,$1,$3);};

bool_exp:   exp EQ_OP exp       {$$ = boolExp(EQ_OP,$1, $3);}
        |   exp NOT_EQ_OP exp   {$$ = boolExp(NOT_EQ_OP,$1,$3);}
        |   exp GRT_OP exp      {$$ = boolExp(GRT_OP,$1,$3);}
        |   exp LT_OP exp       {$$ = boolExp(LT_OP,$1,$3);}
        |   exp GRT_EQ_OP exp   {$$ = boolExp(GRT_EQ_OP,$1,$3);}
        |   exp LT_EQ_OP exp    {$$ = boolExp(LT_EQ_OP,$1,$3);};

bool_block: bool_exp AND_OP bool_block  {$$ = boolAnd($1,$3);}
        |   bool_exp OR_OP bool_block   {$$ = boolOr($1,$3);}
        |   bool_exp                    {$$ = boolBlock($1,NULL);}
        |   exp AND_OP bool_block       {$$ = boolExpAnd($1,$3);}  
        |   exp OR_OP bool_block        {$$ = boolExpOr($1,$3);}
        |   exp                         {$$ = boolExpBlock($1,NULL);};

while:  WHILE_OP OPEN_PARENT exp CLOSE_PARENT OPEN_BRACKET cmd_block CLOSE_BRACKET          {$$ = whileExp($3,$6);}
    |   WHILE_OP OPEN_PARENT bool_block CLOSE_PARENT OPEN_BRACKET cmd_block CLOSE_BRACKET   {$$ = whileBool($3,$6);};

if:   IF_OP exp OPEN_BRACKET cmd_block CLOSE_BRACKET               {$$ = ifExp($2,$4);}
  |   IF_OP bool_block OPEN_BRACKET cmd_block CLOSE_BRACKET        {$$ = ifBoolExp($2,$4);}
  |   IF_OP exp OPEN_BRACKET cmd_block CLOSE_BRACKET else          {$$ = ifElseExp($2,$4,$6);}
  |   IF_OP bool_block OPEN_BRACKET cmd_block CLOSE_BRACKET else   {$$ = ifElseBoolExp($2,$4,$6);};

else: ELSE_OP OPEN_BRACKET cmd_block CLOSE_BRACKET  {$$ = elseExp($3);};


%%
void yyerror(const char* err){
    printf("Line %d: %s - '%s'\n",yyline,err,yytext);
}