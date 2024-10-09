#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "memory.h"

// 사용자 인터페이스 및 메뉴 함수
void show_menu(Block memory[]);
void handle_allocation(Block memory[]);
void handle_free(Block memory[]);
void show_memory_status(Block memory[]);

#endif // MEMORY_MANAGER_H
