#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Queue.h"

queue_head_t *queue_init (queue_head_t *queue, int depth)
{ 
    queue = (queue_head_t *) malloc(sizeof(queue_head_t));
    queue->elm = NULL;
    queue->count = 0;
    queue->max_depth = depth;

    return queue;
}

int enqueue (queue_head_t **pHead, void *elm) 
{

    queue_t *pTmp, *pPrev;

    if (*pHead == NULL) {
        printf("Queue: Not Initialized");
        return -1; 
    }
  
    if (!((*pHead)->elm)) {
        (*pHead)->elm = (queue_t *)malloc(sizeof(queue_t));
        (*pHead)->elm->data = elm;
        (*pHead)->elm->next = NULL;
        (*pHead)->count  = 1;
        return 1;
      
    } else {
       if ((*pHead)->count >= (*pHead)->max_depth) {
            printf("Queue depth: excess number of entries\n");
            return 0;
        }

        pTmp = pPrev = (*pHead)->elm;
        while (pTmp) {
            pPrev = pTmp;
            pTmp = pTmp->next;
        }
        pTmp  = (queue_t *)malloc(sizeof(queue_t));
        pTmp->data = elm;

        pTmp->next  = NULL;
        pPrev->next = pTmp;
        (*pHead)->count++;
    }
  
    return 1;
}

int dequeue (queue_head_t **pHead, void *elm)
{
    queue_t *pTmp, *pPrev;

    if (*pHead == NULL) {
        return -1;
    }

    if (!((*pHead)->count)) {
        return 1;
    } else {
      pTmp = (*pHead)->elm;
      if ((*pHead)->elm->data == elm) {
            (*pHead)->elm = pTmp->next;
            (*pHead)->count--;
            free(pTmp);
            return 1;
        } else {
            pPrev = pTmp;
            pTmp = pTmp->next;
            while (pTmp) {
                if (pTmp->data == elm) {
                    pPrev->next = pTmp->next;
                    (*pHead)->count--;
                    free(pTmp);
                    pTmp = NULL;
                    break;
                }
                pPrev = pTmp;
                pTmp = pTmp->next;

            }
        }
    }
    return 1;
}

void *get_first_item (queue_head_t *pHead)
{
    return (pHead->elm->data);
}

void *get_next_item (queue_head_t *pHead, void *element)
{
   queue_t *pTmp;
   pTmp = pHead->elm;
   while (pTmp) {

       if ((pTmp->data == element) && pTmp->next) {
           return pTmp->next->data;
       }
       pTmp = pTmp->next;
   }

   return pTmp;
}

