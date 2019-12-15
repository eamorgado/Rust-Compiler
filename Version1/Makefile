OBJS=scanner.o parser.o abstree.o interpreter.o
INTERM=scanner.c parser.c parser.h 
PROGRAM=./interpreter
CFLAGS=-g 


COMPILER_OBJS=scanner.o parser.o abstree.o Instruction.o InstructionList.o Node.o VarList.o Mips.o Compiler.o rustCompiler.o
COMPILER=./rustCompiler

all: $(PROGRAM) $(COMPILER)

scanner.c: scanner.flex parser.h
	flex -o scanner.c scanner.flex

parser.c parser.h: parser.bison
	bison --defines=parser.h -o parser.c parser.bison

Instruction: Instruction.c Instruction.h
	$(CC) -o Instruction Instruction.c

InstructionList: InstructionList.c InstructionList.h
	$(CC) -o InstructionList InstructionList.c

Node: Node.c Node.h
	$(CC) -o Node Node.c

VarList: VarList.c VarList.h
	$(CC) -o VarList VarList.c

Mips: Mips.c Mips.h
	$(CC) -o Mips Mips.c

Compiler: Compiler.c Compiler.h
	$(CC)  -o Compiler Compiler.c

compiler: $(COMPILER)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)

$(COMPILER): $(COMPILER_OBJS)
	$(CC) -o $(COMPILER) $(COMPILER_OBJS)

clean:
	rm -f $(PROGRAM) $(OBJS) $(INTERM)
	rm -f $(COMPILER) $(COMPILER_OBJS)
	rm -f compilerIntermediary.pcode || true
	rm -f compilerMips.mips || true

int_test_1: $(PROGRAM)
	$(PROGRAM) example1.txt

int_test_2: $(PROGRAM)
	$(PROGRAM) example2.rst

int_test_3: $(PROGRAM)
	$(PROGRAM) example3.txt

comp_test_1: $(COMPILER)
	rm -f compilerIntermediary.pcode || true
	rm -f compilerMips.mips || true
	$(COMPILER) example1.txt

comp_test_3: $(COMPILER)
	rm -f compilerIntermediary.pcode || true
	rm -f compilerMips.mips || true
	$(COMPILER) example3.txt
