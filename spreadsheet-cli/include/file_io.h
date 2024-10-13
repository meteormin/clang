#ifndef FILE_IO_H
#define FILE_IO_H

#include "spreadsheet.h"

// 스프레드시트 저장 함수
void save_spreadsheet(const char *filename, Cell sheet[ROWS][COLS]);

// 스프레드시트 로드 함수
void load_spreadsheet(const char *filename, Cell sheet[ROWS][COLS]);

#endif // FILE_IO_H
