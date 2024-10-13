#ifndef CELL_REF_H
#define CELL_REF_H

#include "spreadsheet.h"

typedef struct {
  int result; // 계산 결과
  int error;  // 오류 상태를 나타내는 플래그 (0: 성공, 1: 오류)
  char errorMsg[50]; // 오류 메시지
} CalculationResult;

// 셀 참조를 이용한 계산 기능
CalculationResult calculate_cell(Cell sheet[ROWS][COLS], int row, int col);

#endif // CELL_REF_H
