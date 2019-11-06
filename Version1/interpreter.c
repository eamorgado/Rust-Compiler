#include <stdio.h>
#include "parser.h"
#include "printer.h"

int main(int argc, char** argv){
    if(argc != 1){
        yyin = fopen(argv[1],"r");
        if(!yyin){
            printf("'%s': could not open file\n",argv[1]);
            return 1;
        }
        if(yyparse() == 0){
            do{
                printCmdBlock(root,0);
                root = root->next;
            }while(root != NULL);
            printf("\n\nSuccess");
            return 0;
        }
        printf("error parsing\n");
        return 1;
    }
    printf("No file given\n");
}