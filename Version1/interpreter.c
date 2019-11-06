#include <stdio.h>
#include "parser.h"



void giveSpaces(int n){
    for(int i = 0; i < n; i++)
        printf(" ");
}

void printCmdBlock(CmdBlock* node, int n){
    do{
        printCmd(node->cmd,n);
        node = node->next;
    }while(node != NULL);
}

void printCmd(Cmd* cmd, int n){
    switch(cmd->kind){
        case C_WHILE: printWhile(cmd->command.while_cmd,n); break;
        case C_PRINT: printPrint(cmd->command.print_cmd,n); break;
        case C_READ: printRead(cmd->command.read_cmd,n); break;
        case C_IF: printIf(cmd->command.if_cmd,n); break;
        case C_LET: printLet(cmd->command.let_cmd,n); break;
    }
}

void printWhile(While* cmd, int n){
    giveSpaces(n);
    printf("while\n");
    if(cmd->kind == W_EXP) pprintExp(cmd->condition.exp_val,n);
    else pprintBoolBlock(cmd->condition.bool_val,n);
    printCmdBlock(cmd->while_block,n);
}

void printPrint(Print* cmd, int n){
    giveSpaces(n);
    printf("println!\n");
    giveSpaces(n);
    switch(cmd->kind){
        case P_VAR: printf("%s\n",cmd->printstring.varname); break;
        case P_EXP: pprintExp(cmd->printstring.exp,n); break;
        case P_BOOL: pprintBool(cmd->printstring.bool,n); break;
        case P_BOOLBLOCK: pprintBoolBlock(cmd->printstring.block,n); break;
    }
}

void printRead(Read* cmd, int n){
    giveSpaces(n);
    printf("read_line!\n");
    giveSpaces(n);
    printf("%s\n",cmd->varname);
}

void printIf(If* cmd, int n){
    giveSpaces(n);
    printf("if\n");
    switch(cmd->kind){
        case I_EXP: case I_ELSE_EXP:
            pprintExp(cmd->condition.exp_val,n);  
        break;
        case I_BO: case I_ELSE_BO:
            pprintBoolBlock(cmd->condition.bool_val,n);
        break;
    }
    printCmdBlock(cmd->if_block,n);
    if(cmd->kind == I_ELSE_EXP || cmd->kind == I_ELSE_BO)
        printElse(cmd->elseclause.else_val,n);
}

void printElse(CmdBlock* cmd, int n){
    giveSpaces(n);
    printf("else\n");
    printCmdBlock(cmd,n);
}

void printLet(Let* cmd, int n){
    giveSpaces(n);
    printf("let\n");
    giveSpaces(n);
    printf("\n\nhere\n\n");
    printf("%s\n",cmd->varname);
    switch(cmd->kind){
        case L_SH_EXP: pprintExp(cmd->initialize.exp_value,n); break;
        case L_SH_BOOL: pprintBool(cmd->initialize.bool_value,n); break;
        case L_SH_BLOCK: pprintBoolBlock(cmd->initialize.bool_block,n); break;
    }
}

void pprintExp(Expr* exp, int n){
    giveSpaces(n);
    switch(exp->kind){
        case E_INT:  printf("%d\n",exp->attr.value); break;
        case E_OPERATION:
            switch(exp->attr.op.operator){
                case ADD_OP: printf("+\n"); break;
                case SUB_OP: printf("-\n"); break;
                case MULT_OP: printf("*\n"); break;
                case DIV_OP: printf("/\n"); break;
                case MOD_OP: printf("%c\n",'%'); break;
            }
            pprintExp(exp->attr.op.left,n);
            pprintExp(exp->attr.op.right,n);
        break;
        case E_VAR: printf("%s\n",exp->attr.var); break;
    }
}

void pprintBool(BoolExpr* bool, int n){
    if(bool->kind == B_BOOL) pprintExp(bool->attr.value,n);
    else{
        char c; int op = bool->attr.op.operator;
        switch(op){
            case GRT_OP: case GRT_EQ_OP: c = '>'; break;
            case LT_OP: case LT_EQ_OP: c = '<'; break;
            case NOT_EQ_OP: c = '!'; break;
            case EQ_OP: c = '='; break;    
        }
        printf("%c",c);
        if(op == GRT_EQ_OP || op == LT_EQ_OP || op == NOT_EQ_OP || op == EQ_OP)
            printf("=");
        printf("\n");
        pprintExp(bool->attr.op.left,n);
        pprintExp(bool->attr.op.right,n);
    }
}

void pprintBoolBlock(BoolBlock* b, int n){
    int k = b->kind;
    switch(k){
        case B_EAND: case B_EOR: case B_ENORM:  
            pprintExp(b->block.current_bool.exp_val,n);
        break;
        case B_AND: case B_OR: case B_NORM:
            pprintBool(b->block.current_bool.bool_val,n);
        break;
    }
    if(k != B_ENORM || k != B_NORM){
        giveSpaces(n);
        char c = (k == B_EAND || k == B_AND)? '&' : '|';
        printf("%c%c\n",c,c);
    }
    if(b->block.next != NULL){
        b = b->block.next;
        pprintBoolBlock(b,n);
    }
}



int main(int argc, char** argv){
    if(argc != 1){
        yyin = fopen(argv[1],"r");
        if(!yyin){
            printf("'%s': could not open file\n",argv[1]);
            return 1;
        }
        if(yyparse() == 0){
            printf("fn main()\n");
            printCmdBlock(root,0);
            while(root->next != NULL){
                printCmdBlock(root,0);
                root = root->next;
            }
            printf("\n\nSuccess");
            return 0;
        }
        printf("error parsing\n");
        return 1;
    }
    printf("No file given\n");
}