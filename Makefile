CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRC = src/main.c src/disco.c src/arquivo.c src/alocacao.c
OUT = main

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
