#include "spreadsheet.h"
#include <stdio.h>
#include <string.h>

void initialize_spreadsheet(Cell sheet[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      sheet[i][j].value = 0;
      strcpy(sheet[i][j].formula, "");
    }
  }
}

void set_cell_value(Cell sheet[ROWS][COLS], int row, int col, int value,
                    const char *formula) {
  sheet[row][col].value = value;
  if (formula != NULL) {
    strncpy(sheet[row][col].formula, formula, 19);
    sheet[row][col].formula[19] = '\0'; // Null-terminate for safety
  }
}

void print_spreadsheet(Cell sheet[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%4d ", sheet[i][j].value);
    }
    printf("\n");
  }
}
