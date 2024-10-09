#include "queue.h"
#include <stdlib.h>

// 큐 초기화
void initQueue(Queue *q) { q->front = q->rear = NULL; }

// 큐에 프로세스 삽입
void enqueue(Queue *q, Process *process) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->process = process;
  newNode->next = NULL;
  if (q->rear == NULL) {
    q->front = q->rear = newNode;
  } else {
    q->rear->next = newNode;
    q->rear = newNode;
  }
}

// 큐에서 프로세스 제거
Process *dequeue(Queue *q) {
  if (q->front == NULL)
    return NULL;
  Node *temp = q->front;
  Process *process = temp->process;
  q->front = q->front->next;
  if (q->front == NULL)
    q->rear = NULL;
  free(temp);
  return process;
}

// 큐가 비었는지 확인
int isEmpty(Queue *q) { return q->front == NULL; }
