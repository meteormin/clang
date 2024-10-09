#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 1024 // 총 메모리 크기 (바이트)

// 메모리 블록 구조체 정의
typedef struct Block {
  int size;         // 블록 크기
  int is_allocated; // 할당 여부 (1: 할당, 0: 비할당)
} Block;

void init_memory(Block memory[]);

// 메모리 상태 출력
void print_memory(Block memory[]);

// 최초 적합(First Fit) 메모리 할당
int allocate_memory(Block memory[], int size);

// 메모리 해제
void free_memory(Block memory[], int index);

#endif // MEMORY_H
