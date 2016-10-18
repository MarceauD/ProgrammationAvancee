#ifndef H_FILE
#define H_FILE
#include "graphics.h"

typedef struct Element Element;
struct Element
{
    fighter F;
    Element *next;
};

typedef struct queue queue;
struct queue
{
    Element *first;
};

queue *init_queue();
void enqueue(queue *Q, fighter F);
fighter Head(queue *Q);
fighter dequeue(queue *Q);
void viewqueue(queue *Q);

#endif
