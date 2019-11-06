#ifndef PRINTER_H
#define PRINTER_H

#include "parser.h"

void givePieces(int);
void printCmdBlock(CmdBlock*,int);
void printCmd(Cmd*,int);
void printWhile(While*,int);
void printPrint(Print*,int);
void printRead(Read*,int);
void printIf(If*,int);
void printLet(Let*,int);
void pprintExp(Expr*,int);
void pprintBool(BoolExpr*,int);
void pprintBoolblock(BoolBlock*,int);

#endif