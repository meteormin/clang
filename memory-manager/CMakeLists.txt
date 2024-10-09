cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름
project(memory-manager)

# 소스 파일
set(SOURCES 
  src/main.c 
  src/memory.c
  src/manager.c
)

# include 디렉토리 추가
include_directories(include)

# 실행 파일 생성
add_executable(memory-manager.out ${SOURCES})
