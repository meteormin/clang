#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queue.h"

// 라운드 로빈 스케줄링 함수
void roundRobin(Queue *queue, int time_slice);

#endif
