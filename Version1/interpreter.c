#include <stdio.h>
#include "parser.h"

void print(Cmd* cmd){
    if(cmd->kind == P_EXP) printf("It worked\n");
}

int main(int argc, char** argv){
    if(argc != 1){
        yyin = fopen(argv[1],"r");
        if(!yyin){
            printf("'%s': could not open file\n",argv[1]);
            return 1;
        }
        if(yyparse() == 0){
            //print(root->cmd);
            //while(root->next != NULL) root = root->next;
            printf("Exit success\n");
            return 0;
        }
        printf("error parsing\n");
        return 1;
    }
    printf("No file given\n");
}