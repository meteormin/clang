#include "manager.h"
#include <stdio.h>
#include <stdlib.h>

void show_menu(Block memory[]) {
  int choice;
  while (1) {
    printf(
        "1. Allocate Memory\n2. Free Memory\n3. Show Memory Status\n4. Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      handle_allocation(memory);
      break;
    case 2:
      handle_free(memory);
      break;
    case 3:
      show_memory_status(memory);
      break;
    case 4:
      exit(0);
    default:
      printf("Invalid option.\n");
    }
  }
}

void handle_allocation(Block memory[]) {
  int size;
  printf("Enter size to allocate: ");
  scanf("%d", &size);
  int index = allocate_memory(memory, size);
  if (index != -1) {
    printf("Allocated %d bytes at index %d\n", size, index);
  } else {
    printf("Memory allocation failed.\n");
  }
}

void handle_free(Block memory[]) {
  int index;
  printf("Enter index to free: ");
  scanf("%d", &index);
  free_memory(memory, index);
  printf("Freed memory at index %d\n", index);
}

void show_memory_status(Block memory[]) { print_memory(memory); }
