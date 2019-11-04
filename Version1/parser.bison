//Tokens
%token USE_CMD STD_IO
%token READ_CMD PRINT_CMD
%token ADD_OP SUB_OP MULT_OP MOD_OP DIV_OP
%token AND_OP OR_OP NOT_OP EQ_OP NOT_EQ_OP
%token TRUE_VAL FALSE_VAL TOKEN_VAR
%token GRT_OP LT_OP GRT_EQ_OP LT_EQ_OP
%token ATTR_O
%token F_MAIN F_DEC
%token LET_OP
%token IF_OP ELSE_OP
%token WHILE_OP BRK_OP
%token OPEN_BRACKET CLOSE_BRACKET
%token OPEN_PARENT CLOSE_PARENT
%token SEMICOLON COMA
%token VARNAME STRING INT


//Token precedence
%left USE_CMD STD_IO F_DEC F_MAIN LET_OP MUTAB_OP WHILE_OP IF_OP ELSE_OP OPEN_BRACKET CLOSE_BRACKET OPEN_PARENT CLOSE_PARENT SEMICOLON AND_OP OR_OP NOT_OP
%left LET_OP ATTR_OP
%left GRT_OP GRT_EQ_OP LT LT_EQ_OP EQ_OP NOT_EQ_OP
%left ADD_OP SUB_OP
%left MULT_OP DIV_OP MOD_OP
%left INT TRUE_VAL FALSE_VAL TOKEN_VAR


//root grammar symbol
%start program;


%union{
    int int_val;
    int bool_val;
    Expr* expr_val;
    BoolExpr* boolexpr_val;
    BoolOp* boolop_val;
    While* while_value;
    If* if_val;
    Else* else_val;
}

%type <int_val> INT;
%type <bool_val> 