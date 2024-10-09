#include "scheduler.h"
#include <stdio.h>

void roundRobin(Queue *queue, int time_slice) {
  while (!isEmpty(queue)) {
    Process *current = dequeue(queue);

    if (current->remaining_time > time_slice) {
      printf("Process %d is running for %d units\n", current->pid, time_slice);
      current->remaining_time -= time_slice;
      enqueue(queue, current); // 남은 시간이 있으면 다시 큐에 삽입
    } else {
      printf("Process %d is running for %d units and finished\n", current->pid,
             current->remaining_time);
      current->remaining_time = 0;
      free(current); // 프로세스 종료
    }
  }
}
