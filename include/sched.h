#ifndef SCHED_H
#define SCHED_H
#define TASK_RUNNING 0
#define TASK_INTERRUPTIBLE  1
#define TASK_UNINTERRUPTIBLE    2
#define TASK_ZOMBIE 4
#define TASK_STOPPED    8
#include "processor.h"
void schedule();
void sleep_on(struct task_struct ** p);
void wake_up(struct task_struct **p);
#endif

