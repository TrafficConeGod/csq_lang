SOURCES = $(shell find src -name "*.cc")
CURRENT_SOURCES = $(shell find src -name "*.cc")
OBJECTS = $(shell find . -name "*.o")
CC = g++
CFLAGS = -I include -Wall -std=c++17

all: build

build: 
	$(CC) $(CFLAGS) -c $(CURRENT_SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o csq.elf

example: build
	./csq.elf examples/test.csq

clean:
	-rm $(OBJECTS)

rebuild: clean
	$(CC) $(CFLAGS) -c $(SOURCES)