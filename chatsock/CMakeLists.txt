cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름
project(ChatSock)

set(CMAKE_C_STANDARD 11)

# 소스 파일 설정
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# include 디렉토리 추가
include_directories(${INCLUDE_DIR})

set(SERVER_SOURCES ${SOURCE_DIR}/server.c)
set(CLIENT_SOURCES ${SOURCE_DIR}/client.c)

# 실행 파일 생성
add_executable(server.out ${SERVER_SOURCES})

add_executable(client.out ${CLIENT_SOURCES})

target_link_libraries(server.out pthread)
target_link_libraries(client.out pthread)
