#ifndef QUEUE_H
#define QUEUE_H

#include "proc.h"

// 큐 노드 구조체
typedef struct Node {
  Process *process;
  struct Node *next;
} Node;

// 큐 구조체
typedef struct {
  Node *front;
  Node *rear;
} Queue;

// 큐 관련 함수들
void initQueue(Queue *q);
void enqueue(Queue *q, Process *process);
Process *dequeue(Queue *q);
int isEmpty(Queue *q);

#endif // !
