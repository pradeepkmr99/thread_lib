#ifndef __MYTHREAD_LIB__
#define __MYTHREAD_LIB__

#include<ucontext.h>
#include "Queue.h"

typedef int mythread_id_t;

typedef enum mythread_e_ {
    THREAD_RUNNING,
    THREAD_SLEEP,
    THREAD_SUSPEND,
    THREAD_EXIT,
} mythread_state_e;

typedef struct mythread_s {
    mythread_state_e state;
    ucontext_t contxt;
    mythread_id_t id; 
    void (*thread_func)();
} mythread_t;

static is_mythread_sleeping (mythread_t *t1)
{
    return (t1->state == THREAD_SLEEP);
}

#define mythread_suspend(idx)   {   \
    mythread_t *t1; \
    t1 = get_first_item(run_queue_thread); \
    if (t1->id == idx) { \
        t1->state = THREAD_SUSPEND; \
        swapcontext(&t1->contxt, &uctx_main); \
    } else { \
        while (t1 = get_next_item(run_queue_thread, t1)) { \
            if (t1->id == idx) { \
                break; \
            } \
        } \
        t1->state = THREAD_SUSPEND; \
        swapcontext(&t1->contxt, &uctx_main); \
    } \
}

#define schedule_nexttask(th1)  \
          { \
            th1->state = THREAD_RUNNING; \
            swapcontext(&uctx_main, &th1->contxt); \
          }

ucontext_t uctx_main;
queue_head_t *run_queue_thread;
queue_head_t *wait_queue_thread;

void mythread_exit(mythread_id_t idx);
mythread_id_t mythread_create(mythread_t *thread1, void (*func)());
void mythread_wakeup(mythread_id_t idx);
void mythread_sleep(mythread_id_t idx);
void scheduler_run(void);
void init_mythread_lib() __attribute__((constructor));
#endif
