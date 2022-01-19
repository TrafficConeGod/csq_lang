SOURCES = $(shell find src -name "*.cc")
OBJECTS = $(shell find . -name "*.o")
CC = g++
CFLAGS = -I include -Wall -std=c++17

all: build

build: 
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o csq.elf

example: build
	cd examples; ../csq.elf test.csq

.PHONY: clean
clean:
	-rm $(OBJECTS)