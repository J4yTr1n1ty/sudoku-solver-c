CC=gcc
CFLAGS=-Wall -Wextra -O3 -Ofast -march=native -mtune=native -ffast-math -flto

all: SudokuSolver

SudokuSolver: main.c
	$(CC) $(CFLAGS) -o build/solver main.c

clean:
	rm -f SudokuSolver
