INTERPRETER_OBJS=scanner.o parser.o abstree.o interpreter.o
INTERM=scanner.c parser.c parser.h 
INTERPRETER=./interpreter

COMPILER_OBJS= scanner.o parser.o abstree.o Node.o VarList.o Instruction.o InstructionList.o Mips.o Compiler.o
COMPILER_INTERM=scanner.c parser.c parser.h Node.c VarList.c Instruction.c InstructionList.c Mips.c Compiler.c
COMPILER=./Main

CFLAGS=-g 

all: $(INTERPRETER) 
interpreter: $(INTERPRETER)
compiler: $(COMPILER)


scanner.c: scanner.flex parser.h
	flex -o scanner.c scanner.flex

parser.c parser.h: parser.bison
	bison --defines=parser.h -o parser.c parser.bison

Node.c: Node.h
	$(CC) -o Node Node.c

VarList.c: VarList.h
	$(CC) -o VarList VarList.c

Instruction.c: Instruction.h
	$(CC) -o Instruction Instruction.c

InstructionList.c: Instruction.c Instruction.h InstructionList.h
	$(CC) -o InstructionList InstructionList.c


Mips.c: parser.c parser.h Instruction.c InstructionList.c VarList.c
	$(CC) -o Mips Mips.c


$(INTERPRETER): $(INTERPRETER_OBJS)
	$(CC) -o $(INTERPRETER) $(INTERPRETER_OBJS)

$(COMPILER): $(COMPILER_OBJS)
	$(CC) -o $(COMPILER_INTERM) $(COMPILER_OBJS)

clean:
	rm -f $(INTERPRETER) $(INTERPRETER_OBJS) $(INTERM)
	rm -r $(COMPILER) $(COMPILER_OBJS)


test: $(INTERPRETER)
	$(INTERPRETER) example1.txt
