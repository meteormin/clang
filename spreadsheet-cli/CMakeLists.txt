cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름
project(SpreadsheetCLI)

# 소스 파일
set(SOURCES 
  src/main.c 
  src/spreadsheet.c
  src/file_io.c
  src/cell_ref.c
)

# include 디렉토리 추가
include_directories(include)

# 실행 파일 생성
add_executable(spreadsheet.out ${SOURCES})
