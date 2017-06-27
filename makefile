CC = gcc
CDEBUG = -g -Wall
CFLAGS = -Wall

default: test

test:	delimited.o test.c
	$(CC) $(CDEBUG) -o test test.c delimited.o

delimited.o:	delimited.c delimited.h
	$(CC) $(CDEBUG) -c delimited.c

clean:
	rm -rf *.o test data
