#ifndef MAP_H
#define MAP_H

// define constant
#define KEY_SIZE 50
#define VALUE_SIZE 100
#define DATA_SIZE 255

// struct Data
typedef struct {
  int id;
  char key[KEY_SIZE];
  char value[VALUE_SIZE];
} Data;

// struct Node LinkedList
typedef struct Node Node;

struct Node {
  Data data;
  struct Node *next;
};

// struct Map
typedef struct {
  int cnt;
  Node *nodes;
} Map;

// functions

// initialize data in map.
Map *init_map(Map *m);

// get length map.
int length_map(Map *m);

// print all elements in map
void print_map(Map *m);

// print data
void print_data(Data data);

// put data
void put_data(Map *m, char *key, char *value);

// remove data
void remove_data(Map *m, int id);

Data get_data_by_id(Map *m, int id);

// get data by key and value.
Data *get_data(Map *m, char *key, char *value);

#endif
