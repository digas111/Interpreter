CC=gcc

CFLAGS = -Wall

all: interpreter

interpreter: main.o instr.o hash.o linkedlist.o read.o
	$(CC) main.o instr.o hash.o linkedlist.o read.o -o interpreter

main.o: main.c
	$(CC) $(CFLAGS) main.c

instr.o: Instr/instr.c
	$(CC) $(CFLAGS) Instr/instr.c

hash.o: Hash/hash.c Hash/labelhash.c Hash/variablehash.c
	$(CC) $(CFLAGS) Hash/hash.c Hash/labelhash.c Hash/variablehash.c

linkedlist.o: LinkedList/linkedList.c
	$(CC) $(CFLAGS) LinkedList/linkedList.c

read.o: Read/read.c
	$(CC) $(CFLAGS) Read/read.c