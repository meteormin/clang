#include "proc.h"
#include "queue.h"
#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Queue queue;
  initQueue(&queue);

  int time_slice;
  int num_processes;

  // 타임 슬라이스 입력
  printf("Enter time slice for Round Robin scheduling: ");
  scanf("%d", &time_slice);

  // 프로세스 개수 입력
  printf("Enter the number of processes to simulate: ");
  scanf("%d", &num_processes);

  // 각 프로세스 정보를 입력받아 큐에 추가
  for (int i = 0; i < num_processes; i++) {
    int pid, priority, burst_time, arrival_time;

    printf("\nEnter details for Process %d\n", i + 1);
    printf("PID: ");
    scanf("%d", &pid);
    printf("Priority: ");
    scanf("%d", &priority);
    printf("Burst Time: ");
    scanf("%d", &burst_time);
    printf("Arrival Time: ");
    scanf("%d", &arrival_time);

    Process *new_process =
        create_process(pid, priority, burst_time, arrival_time);
    enqueue(&queue, new_process);
  }

  printf("\nStarting Round Robin Scheduling Simulation...\n\n");
  roundRobin(&queue, time_slice);

  return 0;
}
