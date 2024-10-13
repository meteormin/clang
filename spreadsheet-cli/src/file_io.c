#include "file_io.h"
#include <stdio.h>

void save_spreadsheet(const char *filename, Cell sheet[ROWS][COLS]) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    perror("파일 열기 실패");
    return;
  }
  fwrite(sheet, sizeof(Cell), ROWS * COLS, file);
  fclose(file);
}

void load_spreadsheet(const char *filename, Cell sheet[ROWS][COLS]) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("파일 열기 실패");
    return;
  }
  fread(sheet, sizeof(Cell), ROWS * COLS, file);
  fclose(file);
}
