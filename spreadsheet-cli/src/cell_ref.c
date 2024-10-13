#include "cell_ref.h"
#include <stdio.h>

// 간단한 셀 참조 및 수식 계산 함수 (예: "=A0+B1"을 분석하여 계산)
CalculationResult calculate_cell(Cell sheet[ROWS][COLS], int row, int col) {
  CalculationResult result = {.result = 0, .error = 0, .errorMsg = ""};

  if (sheet[row][col].formula[0] == '=') {
    // 수식 파싱 및 계산 (예: "=A0+B1")
    int row1 = 0, row2 = 0;
    char col1 = 0, col2 = 0;
    char op;

    if (sscanf(sheet[row][col].formula, "=%c%d%c%c%d", &col1, &row1, &op, &col2,
               &row2) == 5) {
      int val1 = sheet[row1][col1 - 'A'].value;
      int val2 = sheet[row2][col2 - 'A'].value;

      switch (op) {
      case '+':
        result.result = val1 + val2;
        break;
      case '-':
        result.result = val1 - val2;
        break;
      case '*':
        result.result = val1 * val2;
        break;
      case '/':
        if (val2 == 0) {
          result.error = 1;
          snprintf(result.errorMsg, sizeof(result.errorMsg),
                   "error: zero division");
        } else {
          result.result = val1 / val2;
        }
        break;
      default:
        result.error = 1;
        snprintf(result.errorMsg, sizeof(result.errorMsg),
                 "error: invalid operator '%c'", op);
        break;
      }
    } else {
      result.error = 1;
      snprintf(result.errorMsg, sizeof(result.errorMsg),
               "error: invalid formula '%s'", sheet[row][col].formula);
    }
  } else {
    result.result = sheet[row][col].value;
  }

  return result;
}
