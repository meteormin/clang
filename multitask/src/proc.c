#include "proc.h"
#include <stdlib.h>

Process *create_process(int pid, int priority, int burst_time,
                        int arrival_time) {
  Process *p = (Process *)malloc(sizeof(Process));
  p->pid = pid;
  p->priority = priority;
  p->burst_time = burst_time;
  p->arrival_time = arrival_time;
  p->remaining_time = burst_time;
  return p;
}
