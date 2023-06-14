#ifndef QUEUE_H
#define QUEUE_H

#ifdef VECTOR

#define SIZE 2

typedef struct Queue {
    int* angle;
    int* members;
    double* res;
    int min;
    int max;
} Queue;

#else

typedef struct Item {
    int angle;
    int members;
    double res;
    struct Item *next;
    int flag;
} Item;

typedef struct Queue {
    Item *head;
    Item *tail;
} Queue;

#endif

Queue *queue_new();

void queue_delete(Queue *queue);

int queue_put(Queue *queue, int angle, int members);

int queue_put_res(Queue *queue, int angle, double res);

int queue_get(Queue *queue, int *angle, int *members);

int queue_get_res(Queue *queue, int *angle, double *sin);

void queue_print(const Queue *queue);

void queue_print_res(const Queue *queue);

int queue_empty(const Queue *queue);

#endif
