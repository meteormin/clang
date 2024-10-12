#include "data.h"
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_SIZE 100
#define MAX_KEY_SIZE 50
#define MAX_VALUE_SIZE 100
#define FILE_NAME "simple-db.db"

Map *m;

void find_all() {
  printf("find all...\n");
  print_map(m);
}

void find_by_key_value(char *key, char *value) {
  Map *m2 = get_data(m, key, value);
  print_map(m2);
}

void put(char *key, char *value) {
  int next_id = ++m->idx;
  put_data(m, next_id, key, value);
}

void rm(int id) { remove_data(m, id); }

void commit(const char *filename, Map *m) { save_list(filename, m); }

void help() {
  printf("\n- h: help.\n");
  printf("- find: find data\n");
  printf("  - find all: find all data\n");
  printf("  - find %%s %%s: find key and value\n");
  printf("- put: put data\n");
  printf("  - put %%s %%s: put key and value\n");
  printf("- rm: remove data\n");
  printf("  - rm %%d: remove by id\n");
  printf("- commit: commit data(save file).\n");
  printf("- q: quit.\n");
}

int main() {
  printf("Simple-db.\n");

  m = load_list(FILE_NAME);

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
    } else if (strcmp(command, "commit") == 0) {
      commit(FILE_NAME, m);
    } else {
      printf("help:\n");
      help();
    }
  }

  return 0;
}
