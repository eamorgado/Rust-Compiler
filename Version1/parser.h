/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 63 "parser.bison" /* yacc.c:1909  */

    #include <stdio.h>
    #include <stdlib.h>
    #include "abstree.h"
    
    extern int yylex();
    extern int yyline;
    extern char* yytext;
    extern FILE* yyin;
    extern void yyerror(const char* errormsg);

    CmdBlock* root;

#line 58 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    READ_CMD = 258,
    PRINT_CMD = 259,
    ADD_OP = 260,
    SUB_OP = 261,
    MULT_OP = 262,
    MOD_OP = 263,
    DIV_OP = 264,
    AND_OP = 265,
    OR_OP = 266,
    NOT_OP = 267,
    EQ_OP = 268,
    NOT_EQ_OP = 269,
    GRT_OP = 270,
    LT_OP = 271,
    GRT_EQ_OP = 272,
    LT_EQ_OP = 273,
    ATTR_O = 274,
    F_MAIN = 275,
    F_DEC = 276,
    LET_OP = 277,
    IF_OP = 278,
    ELSE_OP = 279,
    WHILE_OP = 280,
    OPEN_BRACKET = 281,
    CLOSE_BRACKET = 282,
    OPEN_PARENT = 283,
    CLOSE_PARENT = 284,
    SEMICOLON = 285,
    VARNAME = 286,
    INT = 287,
    ATTR_OP = 288,
    LT = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 32 "parser.bison" /* yacc.c:1909  */

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

#line 121 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
