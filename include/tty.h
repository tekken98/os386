#ifndef TTY_H
#define TTY_H
#define TTY_BUF_SIZE 1024
#include "types.h"
struct task_struct;
typedef struct tty_queue{
    ulong head;
    ulong tail;
    struct task_struct * proc_list;
    char buf[TTY_BUF_SIZE];
} tty_queue;
#endif

