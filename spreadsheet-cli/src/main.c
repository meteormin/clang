#include "cell_ref.h"
#include "file_io.h"
#include "spreadsheet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help() {
  printf("Command:\n");
  printf("  set <row> <col> <value>         : 특정 셀에 값 입력 (예: 0 0 1)\n");
  printf(
      "  formula <row> <col> <formula>   : 특정 셀에 수식 입력 (예: =A0+B1)\n");
  printf("  calc <row> <col>                : 특정 셀의 값 계산\n");
  printf("  save <filename>                 : 스프레드시트 CSV로 저장\n");
  printf("  load <filename>                 : CSV 파일에서 스프레드시트 "
         "불러오기\n");
  printf("  print                           : 스프레드시트 출력\n");
  printf("  help                            : 명령어 목록 출력\n");
  printf("  exit                            : 프로그램 종료\n");
}

int main() {
  Cell sheet[ROWS][COLS];
  initialize_spreadsheet(sheet);
  char command[50], formula[50], filename[50];
  int row, col, value;

  print_help();

  while (1) {
    printf("\nPlease input command: ");
    scanf("%s", command);

    if (strcmp(command, "set") == 0) {
      scanf("%d %d %d", &row, &col, &value);
      set_cell_value(sheet, row, col, value, NULL);
      printf("Set cell: (%d, %d), value: %d\n", row, col, value);

    } else if (strcmp(command, "formula") == 0) {
      scanf("%d %d %s", &row, &col, formula);
      set_cell_value(sheet, row, col, 0, formula);
      printf("Set cell: (%d, %d) with '%s'\n", row, col, formula);

    } else if (strcmp(command, "calc") == 0) {
      scanf("%d %d", &row, &col);
      CalculationResult result = calculate_cell(sheet, row, col);
      if (result.error) {
        printf("calculation error: %s\n", result.errorMsg);
      } else {
        printf("calculation result(%d, %d): %d\n", row, col, result.result);
      }

      set_cell_value(sheet, row, col, result.result, NULL);

    } else if (strcmp(command, "save") == 0) {
      scanf("%s", filename);
      save_spreadsheet(filename, sheet);
      printf("saved '%s'\n", filename);

    } else if (strcmp(command, "load") == 0) {
      scanf("%s", filename);
      load_spreadsheet(filename, sheet);
      printf("loaded '%s'\n", filename);

    } else if (strcmp(command, "print") == 0) {
      print_spreadsheet(sheet);

    } else if (strcmp(command, "help") == 0) {
      print_help();

    } else if (strcmp(command, "exit") == 0) {
      printf("Bye\n");
      break;

    } else {
      printf("Command not found. Please input 'help' for more information.\n");
    }
  }
}
