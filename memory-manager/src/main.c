#include "manager.h"
#include "memory.h"
#include <stdio.h>

int main() {
  printf("Memory Manager\n");

  // 초기화
  Block memory[MEMORY_SIZE];
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i].size = 1;         // 각 블록 크기를 1 바이트로 설정
    memory[i].is_allocated = 0; // 초기 상태는 비어 있음
  }

  // 사용자 인터페이스 시작
  show_menu(memory);

  return 0;
}
