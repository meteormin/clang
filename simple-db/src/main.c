#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_SIZE 100
#define MAX_KEY_SIZE 50
#define MAX_VALUE_SIZE 100

Map *m;

void find_all() {
  printf("find all...\n");
  print_map(m);
}

void find_by_key_value(char *key, char *value) {
  Data *data = get_data(m, key, value);
  int find_data_size = sizeof(*data);
  int find_data_cnt = find_data_size / sizeof(Data);

  for (int i = 0; i < find_data_cnt; i++) {
    print_data(data[i]);
  }
}

void put(char *key, char *value) { put_data(m, key, value); }

void rm(int id) { remove_data(m, id); }

void help() {
  printf("\n- h: help.\n");
  printf("- find: find data\n");
  printf("  - find all: find all data\n");
  printf("  - find %%s %%s: find key and value\n");
  printf("- put: put data\n");
  printf("  - put %%s %%s: put key and value\n");
  printf("- rm: remove data\n");
  printf("  - rm %%d: remove by id\n");
  printf("- q: quit.\n");
}

int main() {
  printf("Simple-db.\n");

  m = malloc(sizeof(Map));

  init_map(m);

  char command[MAX_COMMAND_SIZE];

  int id = 0;
  char key[MAX_KEY_SIZE];
  char value[MAX_VALUE_SIZE];

  help();

  while (1) {
    printf("\nEnter command: ");
    fgets(command, MAX_COMMAND_SIZE, stdin);
    command[strcspn(command, "\n")] = 0; // 개행 문자 제거

    if (strcmp(command, "q") == 0) {
      break;
    } else if (strcmp(command, "find all") == 0) {
      find_all();
    } else if (sscanf(command, "find %s %s", key, value) == 2) {
      find_by_key_value(key, value);
    } else if (sscanf(command, "put %s %s", key, value) == 2) {
      put(key, value);
    } else if (sscanf(command, "rm %d", &id) == 1) {
      rm(id);
    } else {
      help();
    }
  }
  return 0;
}
