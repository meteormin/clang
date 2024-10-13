#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#define ROWS 10
#define COLS 10

// 셀 데이터 구조체
typedef struct {
  int value;        // 셀 값
  char formula[20]; // 참조/수식을 위한 문자열 저장 (예: "=A1+B1")
} Cell;

// 스프레드시트 초기화 함수
void initialize_spreadsheet(Cell sheet[ROWS][COLS]);

// 셀 값 입력 함수
void set_cell_value(Cell sheet[ROWS][COLS], int row, int col, int value,
                    const char *formula);

// 스프레드시트 출력 함수
void print_spreadsheet(Cell sheet[ROWS][COLS]);

#endif // SPREADSHEET_H
