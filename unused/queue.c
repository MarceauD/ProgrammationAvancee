#include <stdio.h>
#include <stdlib.h>
#include "../headers/queue.h"

queue *init_queue(){
    queue *Q;
    Q = malloc(sizeof(*Q));
    Q->first = NULL;

    return Q;
}

void enqueue(queue *Q, fighter nNombre)
{
    Element *new = malloc(sizeof(*new));
    if (Q == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }

    new->F = nNombre;
    new->next = NULL;

    if (Q->first != NULL) /* La file n'est pas vide */
    {
        /* On se positionne a la fin de la file */
        Element *currentElement = Q->first;
        while (currentElement->next != NULL)
        {
            currentElement = currentElement->next;
        }
        currentElement->next = new;
    }
    else /* La file est vide, notre element est le premier */
    {
        Q->first = new;
    }
}


fighter dequeue(queue *Q)
{
    if (Q == NULL)
    {
        exit(EXIT_FAILURE);
    }

    fighter queueNumber = init_fighter(0);

    /* On verifie s'il y a quelque chose a defiler */
    if (Q->first != NULL)
    {
        Element *QueueElement = Q->first;

        queueNumber = QueueElement->F;
        Q->first = QueueElement->next;
        free(QueueElement);
    }

    return queueNumber;
}

void viewQueue(queue *Q)
{
    if (Q == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *element = Q->first;

    while (element != NULL)
    {
        element = element->next;
    }

    printf("\n");
}

fighter Head(queue *Q){
    return Q->first->F;
}
