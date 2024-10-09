#include "memory.h"
#include <stdio.h>

// 메모리 초기화
void init_memory(Block memory[]) {
  for (int i = 0; i < MEMORY_SIZE; i++) {
    memory[i].size = 0;
    memory[i].is_allocated = 0;
  }
}

// 메모리 할당 함수 - First Fit
int allocate_memory(Block memory[], int requested_size) {
  int start_index = -1;
  int free_count = 0;

  for (int i = 0; i < MEMORY_SIZE; i++) {
    if (memory[i].is_allocated) {
      free_count = 0;
    } else {
      free_count++;
      if (free_count == requested_size) {
        start_index = i - requested_size + 1;
        break;
      }
    }
  }

  if (start_index != -1) {
    for (int i = start_index; i < start_index + requested_size; i++) {
      memory[i].is_allocated = 1; // 사용 중으로 설정
      memory[i].size = requested_size;
    }
    return start_index;
  }

  return -1; // 할당 실패 시
}

// 메모리 해제 함수
void free_memory(Block memory[], int index) {
  int block_size = memory[index].size;

  for (int i = index; i < index + block_size; i++) {
    memory[i].is_allocated = 0; // 해제
    memory[i].size = 0;
  }
}

// 메모리 상태 출력 함수
void print_memory(Block memory[]) {
  for (int i = 0; i < MEMORY_SIZE; i++) {
    printf("%c", memory[i].is_allocated
                     ? '#'
                     : '.'); // 빈 블록은 '.', 할당된 블록은 '#'으로 표시
  }
  printf("\n");
}
