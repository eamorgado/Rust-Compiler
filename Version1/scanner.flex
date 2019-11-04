//Flex file for rust

DECIMAL [0-9]

%{
    #include <stdlib.h>
    #include "parser.h"

    int yyline = 1;
%}

%option noywrap

%%

"//".*\n                {/*Comment => consume*/ yyline++;}
[ \t]+                  {/*Tab => consume*/}
\n                      {yyline++;}
[a-zA-Z_][a-zA-Z0-9_]*  {return TOKEN_VAR;}
\-?DECIMAL+.DECIMAL*    {yylval.doubleVal = atof(yytext); return DOUBLE;}
\-?DECIMAL+             {yylval.intValue = atoi(yytext); return INT;}


"+"         {return ADD_OP;}
"-"         {return SUB_OP;}
"*"         {return MULT_OP;}
"/"         {return DIV_OP;}
"%"         {return MOD_OP;}

"&&"        {return AND_OP;}
"||"        {return OR_OP;}

"!"         {return NOT_OP;}
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
"break"     {return BRK_OP;}
"true"      {yylval.boolVal = 1; return TRUE_VAL;}
"false"     {yylval.boolVal = 0; return FALSE_VAL;}
"println!"  {return PRINT_CMD;}
"io::stdin().read_line" {return READ_CMD;}
"use"       {return USE_CMD;}
"std::io"   {return STD_IO;}

"{"         {return OPEN_BRACKET;}
"}"         {return CLOSE_BRACKET;}
"("         {return OPEN_PARENT;}
")"         {return CLOSE_PARENT;}

";"         {return SEMICOLON;}

.           {yyerror("Unexpected character");}
%%

