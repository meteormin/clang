cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름
project(SimpleHTTP)

# 소스 파일
set(SOURCES 
  src/main.c 
  src/http.c 
)

# include 디렉토리 추가
include_directories(include)

# 실행 파일 생성
add_executable(simple-http.out ${SOURCES})
