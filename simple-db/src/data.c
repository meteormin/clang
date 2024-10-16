#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Map *init_map(Map *m) {
  int data_size = length_map(m);

  printf("initialize Map...\n");

  m->cnt = 0;
  m->idx = 0;
  m->nodes = NULL;

  print_map(m);

  return m;
}

int length_map(Map *m) { return m->cnt; }

void print_map(Map *m) {
  int data_size = length_map(m);

  if (data_size == 0) {
    printf("data is empty\n");
    return;
  }

  Node *n = m->nodes;
  for (int i = 0; i < data_size; i++) {
    if (n == NULL)
      break;

    print_data(n->data);

    n = n->next;
  }
}

void print_data(Data datum) {
  int id = datum.id;
  char *key = datum.key;
  char *value = datum.value;

  if (id == 0) {
    printf("[Empty Data]\n");
    return;
  }

  printf("[%d] %s, %s\n", id, key, value);
}

void put_data(Map *m, int id, char *key, char *value) {
  int data_size = length_map(m);

  if (data_size >= DATA_SIZE) {
    printf("can not put: data is full (DATA_SIZE=%d).", DATA_SIZE);
    return;
  }

  if (data_size == 0) {
    Node *first_node = malloc(sizeof(Node));

    first_node->data.id = id;
    strcpy(first_node->data.key, key);
    strcpy(first_node->data.value, value);

    first_node->next = NULL;

    m->cnt++;

    printf("[Put Data]\n");
    print_data(first_node->data);

    m->nodes = first_node;

    return;
  }

  Node *n = m->nodes;
  while (n != NULL) {
    if (n->next == NULL) {
      Node *new_node = malloc(sizeof(Node));

      new_node->data.id = id;
      strcpy(new_node->data.key, key);
      strcpy(new_node->data.value, value);

      new_node->next = NULL;

      m->cnt++;

      printf("[Put Data]\n");
      print_data(new_node->data);

      n->next = new_node;
      n = new_node;

      break;
    }

    n = n->next;
  }
}

void remove_data(Map *m, int id) {

  int data_size = length_map(m);

  Node *remove_node = NULL;
  Node *prev_node = NULL;
  Node *n = m->nodes;
  int removed = 0;
  for (int i = 0; i < data_size; i++) {
    if (n != NULL && n->data.id == id) {
      remove_node = n;

      if (prev_node == NULL) {
        m->nodes = remove_node->next;
      } else {
        prev_node->next = remove_node->next;
      }

      free(remove_node);

      removed = 1;

      m->cnt--;

      break;
    }
    prev_node = n;
    n = n->next;
  }

  if (removed) {
    printf("success remove: %d", id);
  } else {
    printf("failed remove: %d", id);
  }
}

Map *get_data(Map *m, char *key, char *value) {
  int data_size = length_map(m);

  Map *m2 = malloc(sizeof(Map));
  init_map(m2);

  int j = 0;

  Node *n = m->nodes;
  Node *n2 = m2->nodes;
  for (int i = 0; i < data_size; i++) {
    if (strcmp(n->data.key, key) == 0 && strcmp(n->data.value, value) == 0) {
      printf("find match...\n");
      put_data(m2, n->data.id, n->data.key, n->data.value);
      j++;
    }

    n = n->next;
  }

  printf("found %d\n", j);

  return m2;
}

void save_list(const char *filename, Map *m) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    perror("Failed to open file");
    return;
  }

  // Map의 메타 정보 저장 (cnt와 idx)
  fwrite(&m->cnt, sizeof(int), 1, file);
  fwrite(&m->idx, sizeof(int), 1, file);

  Node *current = m->nodes;
  while (current != NULL) {
    fwrite(&(current->data), sizeof(Data), 1, file);
    current = current->next;
  }

  fclose(file);

  printf("save file: %s\n", filename);
}

Map *load_list(const char *filename) {
  Map *m = malloc(sizeof(Map));
  init_map(m);

  FILE *file = fopen(filename, "rb");
  printf("open file");

  if (file == NULL) {
    perror("Failed to open file");
    return m;
  }

  fread(&m->cnt, sizeof(int), 1, file);
  fread(&m->idx, sizeof(int), 1, file);

  Node *tail = NULL;
  Data temp_data;
  while (fread(&temp_data, sizeof(Data), 1, file) == 1) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
      perror("Failed to allocate memory");
      fclose(file);
      return NULL;
    }

    new_node->data = temp_data;
    new_node->next = NULL;

    if (m->nodes == NULL) {
      m->nodes = new_node;
    } else {
      tail->next = new_node;
    }

    m->cnt++;
    printf("load %d", m->cnt);

    tail = new_node;
  }

  fclose(file);

  return m;
}
