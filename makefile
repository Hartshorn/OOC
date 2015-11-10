c = Set.c
h = new.h Set.h Object.h
m = main.c
t = sets bags

sets = main.o Set.o
bags = main.o Bag.o

CFLAGS = -Wall -std=c99 -O0
CC = gcc

all: $(CC) $(CFLAGS) 

clean: rm -f $t *.o


