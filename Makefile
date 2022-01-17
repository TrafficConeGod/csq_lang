SOURCES = $(shell find src/frontend -name "*.cpp")
OBJECTS = $(shell find . -name "*.o")
CC = g++
CFLAGS = -I include -Wall -std=c++17

all: build

build: 
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o csq.elf

run: build
	./csq.elf

clean:
	rm $(OBJECTS)
	rm kernel
