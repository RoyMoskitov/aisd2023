#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*typedef struct side{
        int angle;
        int members;
        double res;
        int size;
} side;*/

typedef struct Queue Queue;

typedef struct side{
	Queue *q;
}side;

typedef struct node{
        int side_nodes;
        int angle_max;
        int angle_min;
        int mn_max;
        int mn_min;
        double *res;
        int *angles;
} node;


Queue *queue_new();

void queue_delete(Queue *queue);

int queue_put(Queue *queue, int angle, int members);

int queue_put_res(Queue *queue, int angle, double res);

int queue_get(Queue *queue, int *angle, int *members);

int queue_get_res(Queue *queue, int *angle, double *sin);

void queue_print(const Queue *queue);

void queue_print_res(const Queue *queue);

int queue_empty (const Queue *queue);

void scan (int *value, node *main);

void scan1 (int *value, node *main);

void swap (int *first, int *second);

void destructor (node *main, side *arr);

void mistake (int *j, int *i, node *main, side *arr, Queue *q);
