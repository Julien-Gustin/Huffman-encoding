CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes -g
LD=gcc
LDFLAGS=

# Files
EXEC=huffman
MODULESHEAP=main.c BinarySequence.c CharVector.c CodingTree.c decoding.c coding.c HeapPriorityQueue.c
OBJECTSHEAP=main.o BinarySequence.o CharVector.o CodingTree.o decoding.o coding.o HeapPriorityQueue.o


MODULESLIST=main.c BinarySequence.c CharVector.c CodingTree.c decoding.c coding.c ListPriorityQueue.c
OBJECTSLIST=main.o BinarySequence.o CharVector.o CodingTree.o decoding.o coding.o ListPriorityQueue.o

## Rules

all: $(EXEC)

heap: $(OBJECTSHEAP)
	$(LD) -o $(EXEC) $(OBJECTSHEAP) $(LDFLAGS)

list: $(OBJECTSLIST)
	$(LD) -o $(EXEC) $(OBJECTSLIST) $(LDFLAGS)

prog: $(OBJECTS)
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

BinarySequence.o: BinarySequence.c
	$(CC) -c BinarySequence.c -o BinarySequence.o $(CFLAGS)

coding.o: coding.c
	$(CC) -c coding.c -o coding.o $(CFLAGS)

decoding.o: decoding.c
	$(CC) -c decoding.c -o decoding.o $(CFLAGS)

HeapPriorityQueue.o: HeapPriorityQueue.c
	$(CC) -c HeapPriorityQueue.c -o HeapPriorityQueue.o $(CFLAGS)

ListPriorityQueue.o: ListPriorityQueue.c
	$(CC) -c ListPriorityQueue.c -o ListPriorityQueue.o $(CFLAGS)

CharVector.o: CharVector.c
	$(CC) -c CharVector.c -o CharVector.o $(CFLAGS)


c:	$(EXEC)
	valgrind ./$(EXEC) -e -o text.txt Alice_in_worderland_Lewis_Carroll.ascii freq.csv


d:	$(EXEC)
	./$(EXEC) -o text2.txt text.txt freq.csv


clean:
	rm -f *.o $(EXEC) *~
