#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef linux
    #include <unistd.h>
#endif

#include "parser.h"
#include "InstructionList.h"
#include "VarList.h"
#include "Mips.h"
#include "Compiler.h"

int main(int argc, char const *argv[]){
    #ifdef _WIN32
        printf("Compiler Error: system not supported, unable to locate unistd\nTerminating...\n");
        return 1;
    #else
        if(argc != 1){
            yyin = fopen(argv[1],"r");
            if(!yyin){
                printf("'%s': could not open file\n",argv[1]);
                return 1;
            }
            if(yyparse() == 0){
                IT_LABEL = 0;
                InstrList* list = compile(root);
                VarList* v = getCompilerVarList(); 
                
                //Writing mips code
                int fout = open("compilerMips.mips",O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
                dup2(fout,STDOUT_FILENO);
                close(fout);

                printMips(list,v);
                fflush(stdout);

                if(argc == 3){
                    //Writing intermediary code
                    fout = open("compilerIntermediary.pcode",O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
                    dup2(fout,STDOUT_FILENO);
                    close(fout);

                    printInstrList(list);
                    fflush(stdout);
                }                
                

                //printVarList(v);
            }
            return 0;
        }
        printf("No file found\n");
    #endif
    return 0;
}
