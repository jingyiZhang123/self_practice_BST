
CC=c99
CFLAGS=-c -Wall

all: clean main
	./main

main: bst.o main.o
	$(CC) -o main bst.o main.o

main.o:
	$(CC) $(CFLAGS) main.c

bst.o:
	$(CC) $(CFLAGS) bst.c

clean:
	rm -rf *.o main
