#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Map *init_map(Map *m) {
  int data_size = length_map(m);

  printf("initialize Map...");

  m->last = 0;
  m->nodes = NULL;

  print_map(m);

  return m;
}

int length_map(Map *m) { return m->last + 1; }

void print_map(Map *m) {
  int data_size = length_map(m);

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
    printf("[Empty Data]");
    return;
  }

  printf("[Print Data]");
  printf(" - id: %d\n", id);
  printf(" - key: %s\n", key);
  printf(" - value: %s\n", value);
  printf("[End Print]");
}

void put_data(Map *m, char *key, char *value) {
  int data_size = length_map(m);

  if (data_size >= DATA_SIZE) {
    printf("can not put: data is full (DATA_SIZE=%d).", DATA_SIZE);
    return;
  }

  Node *n = m->nodes;
  for (int i = 0; i < data_size; i++) {
    if (n == NULL) {
      Node *new_node = malloc(sizeof(Node));
      strcpy(new_node->data.key, key);
      strcpy(new_node->data.value, value);
      new_node->next = NULL;
      m->last++;
      break;
    }

    n = n->next;
  }
}

void remove_data(Map *m, int id) {

  int data_size = length_map(m);

  Node *remove_node;
  Node *prev_node;
  Node *n = m->nodes;
  int removed = 0;
  for (int i = 0; i < data_size; i++) {
    if (n->data.id == id) {
      remove_node = n;
      if (prev_node != NULL) {
        prev_node->next = remove_node->next;
      } else {
        m->nodes = NULL;
      }
      free(remove_node);
      remove_node = NULL;
      removed = 1;
      break;
    }
    prev_node = n;
  }

  if (removed) {
    printf("success remove: %d", id);
  } else {
    printf("failed remove: %d", id);
  }
}

Data *get_data(Map *m, char *key, char *value) {
  int data_size = length_map(m);

  Data *data = (Data *)malloc(DATA_SIZE * sizeof(Data));
  Node *n = m->nodes;
  int j = 0;
  for (int i = 0; i < data_size; i++) {
    if (n->data.key == key && n->data.value == value) {
      data[j].id = n->data.id;
      strcpy(data[j].key, n->data.key);
      strcpy(data[j].value, n->data.value);
      j++;
    }
  }

  return data;
}
