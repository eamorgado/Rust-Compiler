#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "parser.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "Mips.h"

void giveTab(){
    printf("\t");
}
void giveEnter(){
    giveTab();
    printf("addi $a0, $0, '\\n'\n");
    mipsSyscall(11);
}

int getLabel(){return IT_LABEL;}
void incLabel(){IT_LABEL++;}
void decLabel(){IT_LABEL--;}

void mipsSyscall(int syscall_number){
    giveTab();
    printf("li $v0, %d\n",syscall_number);
    giveTab();
    printf("Syscall\n");
}

void mipsLoad(char* mips_register){
    giveTab();
    printf("lw %s, 4($sp)\n",mips_register);
    giveTab();
    printf("addi $sp, $sp, 4\n");
}

void mipsStore(char* mips_register){
    giveTab();
    printf("sw %s, 0($sp)\n",mips_register);
    giveTab();
    printf("addi $sp, $sp, -4\n");
}

void mipsCompare(char* type){
    int comp_true = getLabel(); incLabel();
    int comp_false = getLabel(); incLabel();
    //prepare the registers
    mipsLoad("$t1");
    mipsLoad("$t2");
    //Give compare comand, beq, ...
    giveTab();
    printf("%s $t1, $t2, L%d\n",type,comp_true);
    //Re-update $t1 value - conditional false
    giveTab();
    printf("addi $t1, $0, 0\n");
    mipsStore("$t1");
    //Jump to false code
    giveTab();
    printf("j L%d\n",comp_false);
    //True label
    printf("L%d:\n",comp_true);
    giveTab();
    printf("addi $t1, $0, 1\n");
    mipsStore("$t1");
    //False label
    printf("L%d:\n",comp_false);
}

void mipsCompareSub(char* type){
    int comp_true = getLabel(); incLabel();
    int comp_false = getLabel(); incLabel();
    //prepare the registers
    mipsLoad("$t1");
    mipsLoad("$t2"); giveTab();

    printf("sub $t2, $t2, $t1\n"); giveTab();
    printf("%s $t2, L%d\n",type,comp_true); giveTab();
    printf("addi $t1, $0, 0\n");
    mipsStore("$t1"); 
    
    giveTab();
    printf("j L%d\n",comp_false);

    printf("L%d:\n",comp_true); giveTab();
    printf("addi $t1, $t0, 1\n");
    mipsStore("$t1");
    printf("L%d:\n",comp_false);

}
void printMips(InstrList* list, VarList* vlist){
    giveTab();
    printf(".data\n");

    Node* vars = NULL;
    if(vlist) vars = FIRSTVAR(vlist);
    while(vars){
        printf("%s:\t.space 4\n",NAMENODE(vars));
        vars = NEXTNODE(vars);
    }
    
    printf("\n\t.text\n\n");
    InstrNode* node = FIRSTINS(list);

    while(node){
        Type t = TYPE_INS(VALINS(node));
        switch(t){
            case INS_VAR: break;
            case INS_EQ: mipsCompare("beq"); break;            
            case INS_NEQ: mipsCompare("bne"); break;
            case INS_GT: mipsCompareSub("bgtz"); break;            
            case INS_LT: mipsCompareSub("bltz"); break;
            case INS_GEQ: mipsCompareSub("bgez"); break;
            case INS_LEQ: mipsCompareSub("blez"); break;
            case INS_JFALSE: 
                mipsLoad("$t1"); giveTab();
                printf("beq $t1, $0, L%d\n",NUM_ATOM(SINGE_INS(VALINS(node))));
                break;
            case INS_JUNCON:
                giveTab();
                printf("j L%d\n",NUM_ATOM(SINGE_INS(VALINS(node))));
                break;
            case INS_LABEL: printf("L%d:\n",NUM_ATOM(SINGE_INS(VALINS(node)))); break;
            case INS_READ: 
                mipsSyscall(5); giveTab();
                printf("sw $v0, %s\n",VAR_ATOM(SINGE_INS(VALINS(node))));
                break;
            case INS_WRITE:
                giveTab();
                printf("lw $a0, %s\n",VAR_ATOM(SINGE_INS(VALINS(node))));
                mipsSyscall(1); giveEnter();
                break;
            case INS_LOAD_VAR:
                giveTab();
                printf("lw $t1, %s\n",VAR_ATOM(SINGE_INS(VALINS(node))));
                mipsStore("$t1");
                break;
            case INS_LOAD_NUM:
                giveTab();
                printf("addi $t1, $0, %d\n",NUM_ATOM(SINGE_INS(VALINS(node))));
                mipsStore("$t1");
                break;
            case INS_STORE:
                mipsLoad("$t1"); giveTab();
                printf("sw $t1, %s\n",VAR_ATOM(SINGE_INS(VALINS(node))));
                break;
            default: //add, sub, mult, div, mod
                mipsLoad("$t1");
                mipsLoad("$t2"); giveTab();
                switch(t){
                    case INS_ADD: printf("add $t2, $t1, $t2\n"); break;
                    case INS_SUB: printf("sub $t2, $t2, $t1\n"); break;
                    case INS_MOD:
                        printf("div $t1, $t2\n"); giveTab();
                        printf("mfhi\n");
                        break;
                    default:
                        if(t == INS_MUL) printf("mult $t1, $t2\n"); 
                        else printf("div $t1, $t2\n");
                        giveTab();
                        printf("mflo $t2\n");
                        break;
                }
                mipsStore("$t2");
                break;
        }
        node = NEXTINS(node);
    }
    mipsSyscall(10);
}