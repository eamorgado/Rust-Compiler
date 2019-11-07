%{
    #include <stdlib.h>
    #include "parser.h"

    int yyline = 1;
%}

%option noyywrap

%%

"//".*\n                {/*Comment => consume*/ yyline++;}
[ \t]+                  {/*Tab => consume*/}
\n                      {yyline++;}
\-?[0-9]+             {yylval.int_val = atoi(yytext); return INT;}


"+"         {return ADD_OP;}
"-"         {return SUB_OP;}
"*"         {return MULT_OP;}
"/"         {return DIV_OP;}
"%"         {return MOD_OP;}

"&&"        {return AND_OP;}
"||"        {return OR_OP;}

"=="        {return EQ_OP;}
"!="        {return NOT_EQ_OP;}
">"         {return GRT_OP;}
"<"         {return LT_OP;}
">="        {return GRT_EQ_OP;}
"<="        {return LT_EQ_OP;}

"="         {return ATTR_OP;}

"main"      {return F_MAIN;}
"fn"        {return F_DEC;}

"let"       {return LET_OP;}

"if"        {return IF_OP;}
"else"      {return ELSE_OP;}

"while"     {return WHILE_OP;}
"println!"  {return PRINT_CMD;}
"read_line!" {return READ_CMD;}

"{"         {return OPEN_BRACKET;}
"}"         {return CLOSE_BRACKET;}
"("         {return OPEN_PARENT;}
")"         {return CLOSE_PARENT;}

";"         {return SEMICOLON;}

[a-zA-Z_][a-zA-Z0-9_]*  {yylval.var_val = yytext; return VARNAME;}

.           {yyerror("Unexpected character");}
%%

