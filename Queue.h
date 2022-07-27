#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queue_s
{
    void *data;
    struct queue_s *next;
} queue_t;

typedef struct Queue_head_s
{
    queue_t *elm;
    int count;
    int max_depth;
} queue_head_t;

queue_head_t *queue_init (queue_head_t *queue, int depth);

int enqueue (queue_head_t **pHead, void *elm);

int dequeue (queue_head_t **pHead, void *elm);

void *get_first_item (queue_head_t *pHead);
void *get_next_item (queue_head_t *pHead, void *element);
#endif
