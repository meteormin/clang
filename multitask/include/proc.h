#ifndef PROC_H
#define PROC_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pid;
  int priority;
  int burst_time;
  int arrival_time;
  int remaining_time;
} Process;

Process *create_process(int pid, int priority, int burst_time,
                        int arrival_time);

#endif
