PROJ_NAME=main

CC=gcc
CFLAGS=-lm -g -Wall

C_SOURCE=$(wildcard ./source/*.c)

C_HEADERS=$(wildcard ./headers/*.h)

OBJECTS=$(C_SOURCE:./source/%.c=./objects/%.o)

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJECTS) ./objects/main.o
	$(CC) -o $@ $^ $(CFLAGS)

./objects/%.o: ./source/%.c ./headers/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main.o: ./source/main.c $(C_HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf ./objects/*.o $(PROJ_NAME)