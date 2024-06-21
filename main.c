#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define BOARD_SIZE 9
#define TOTAL_CELLS (BOARD_SIZE * BOARD_SIZE)

typedef struct {
  int row;
  int col;
} RowColumn;

int collectInput(int *newBoard) {
  newBoard[3] = 8;
  newBoard[5] = 1;
  newBoard[16] = 4;
  newBoard[17] = 3;
  newBoard[18] = 5;
  newBoard[31] = 7;
  newBoard[33] = 9;
  newBoard[42] = 1;
  newBoard[46] = 2;
  newBoard[49] = 3;
  newBoard[54] = 6;
  newBoard[61] = 7;
  newBoard[62] = 5;
  newBoard[65] = 3;
  newBoard[66] = 4;
  newBoard[75] = 2;
  newBoard[78] = 6;
  return 0;
}

RowColumn indexToRowColumn(int index) {
  RowColumn rc;
  rc.row = index / BOARD_SIZE;
  rc.col = index % BOARD_SIZE;
  return rc;
}

int rowColumnToIndex(int row, int column) { return row * BOARD_SIZE + column; }

bool acceptable(int *board, int index, int value) {
  RowColumn rc = indexToRowColumn(index);

  // Check column
  for (int r = 0; r < BOARD_SIZE; ++r) {
    if (board[rowColumnToIndex(r, rc.col)] == value) {
      return false;
    }
  }

  // Check row
  for (int c = 0; c < BOARD_SIZE; ++c) {
    if (board[rowColumnToIndex(rc.row, c)] == value) {
      return false;
    }
  }

  // Check 3x3 box
  int startRow = (rc.row / 3) * 3;
  int startCol = (rc.col / 3) * 3;
  for (int r = startRow; r < startRow + 3; ++r) {
    for (int c = startCol; c < startCol + 3; ++c) {
      if (board[rowColumnToIndex(r, c)] == value) {
        return false;
      }
    }
  }

  return true;
}

int getPossibleMoves(int *board, int index, int *moves) {
  int count = 0;
  for (int value = 1; value <= BOARD_SIZE; ++value) {
    if (acceptable(board, index, value)) {
      moves[count++] = value;
    }
  }
  return count;
}

void writeSolveTimeToFile(long duration) {
  FILE *file = fopen("solve_time.txt", "a");
  fprintf(file, "%ld ms,", duration);
  fclose(file);
}

bool solve(int *board, int index, int *backtrack) {
  while ((index < TOTAL_CELLS) && (board[index] != 0)) {
    ++index;
  }
  if (index >= TOTAL_CELLS) {
    return true;
  }
  int moves[TOTAL_CELLS];
  int numMoves = getPossibleMoves(board, index, moves);
  if (numMoves == 0) {
    return false;
  }

  for (int i = 0; i < numMoves; ++i) {
    board[index] = moves[i];
    if (solve(board, index, backtrack)) {
      return true;
    }
  }

  board[index] = 0;
  (*backtrack)++;
  return false;
}

void solveBruteForce() {
  int board[TOTAL_CELLS] = {0};
  collectInput(board);
  int backtrack = 0;
  int index = 0;
  clock_t startTime = clock();

  bool solutionFound = solve(board, index, &backtrack);
  clock_t endTime = clock();
  long solutionTime = (endTime - startTime) * 1000 / CLOCKS_PER_SEC;

  printf("Solution found: %s\n", solutionFound ? "Yes" : "No");
  printf("Backtrack count: %d\n", backtrack);
  printf("Solution time: %ld ms\n", solutionTime);

  writeSolveTimeToFile(solutionTime);
}

int main() {
  for (int i = 0; i < 10; ++i) {
    printf("Solving...\n");
    solveBruteForce();
  }
  return 0;
}
