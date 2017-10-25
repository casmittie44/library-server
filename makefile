CC = gcc
CDEBUG = -g -Wall
CFLAGS = -Wall

default: debug
debug:	delimited.o server.c hacking.h
	$(CC) $(CDEBUG) -o server server.c delimited.o hacking.h

test:	delimited.o test.c
	$(CC) $(CDEBUG) -o test test.c delimited.o

delimited.o:	delimited.c delimited.h
	$(CC) $(CDEBUG) -c delimited.c

clean:
	rm -rf *.o test data
