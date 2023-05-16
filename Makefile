PROJ_NAME_1=main_convolucao
PROJ_NAME_2=main_bin
PROJ_NAME_3=main_operations

CC=gcc
CFLAGS=-lm -g -Wall

C_SOURCE=$(wildcard ./source/*.c)

C_HEADERS=$(wildcard ./headers/*.h)

OBJECTS=$(C_SOURCE:./source/%.c=./objects/%.o)

all: $(PROJ_NAME_1) $(PROJ_NAME_2) $(PROJ_NAME_3)

$(PROJ_NAME_1): $(OBJECTS) ./objects/main_convolucao.o
	$(CC) -o $@ $^ $(CFLAGS)

$(PROJ_NAME_2): $(OBJECTS) ./objects/main_bin.o
	$(CC) -o $@ $^ $(CFLAGS)

$(PROJ_NAME_3): $(OBJECTS) ./objects/main_operations.o
	$(CC) -o $@ $^ $(CFLAGS)

./objects/%.o: ./source/%.c ./headers/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_convolucao.o: main_convolucao.c $(C_HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_bin.o: main_bin.c $(C_HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_operations.o: main_operations.c $(C_HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf ./objects/*.o $(PROJ_NAME_1) $(PROJ_NAME_2)