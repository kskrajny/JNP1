CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++17
LDFLAGS =

.PHONY: all clean

all: main

main: main.o parser.o operations.o
	$(CC) $(LDFLAGS) -o $@ $^

operations.o: operations.cpp operations.h
	$(CC) $(CFLAGS) -c $<

parser.o: parser.cpp parser.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main
