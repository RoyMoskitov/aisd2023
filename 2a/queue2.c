#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

Queue *queue_new() {
	Queue *q = calloc(1, sizeof(Queue));
	q->angle = calloc(SIZE+1, sizeof(int));
	q->members = calloc(SIZE+1, sizeof(int));
	q->res = calloc(SIZE+1, sizeof(double));
	q->min = q->max = 0;
    return q;
}

void queue_delete(Queue *q) {
    free(q->angle);
    free(q->members);
    free(q->res);
    q->min = q->max = 0;
    free(q);
}

int queue_put(Queue *queue, int angle, int members) {
    if (queue->max == SIZE) {
    	//printf("Overflow\n");
    	return 1;
    }
    queue->angle[(queue->max)] = angle;
    queue->members[(queue->max)] = members;
    (queue->max)++;
    return 0;
}

int queue_put_res(Queue *queue, int angle, double res) {
    if (queue->max == SIZE) {
        //printf("Overflow\n");
        return 1;
    }
    queue->angle[(queue->max)] = angle;
    queue->res[(queue->max)] = res;
    (queue->max)++;
    return 0;
}

int queue_get(Queue *queue, int *angle, int *members) {
    if (queue->min == queue->max) {
        return 1;
    }
    *angle = queue->angle[(queue->min)];
    *members =  queue->members[(queue->min)];
    for (int i=0; i<queue->max; ++i){
    	queue->angle[i]=queue->angle[i+1];
    	queue->members[i] = queue->members[i+1];
    }
    (queue->max)--;
    return 0;
}

int queue_get_res(Queue *queue, int *angle, double *res) {
    if (queue->min == queue->max) {
        return 1;
    }
    *angle = queue->angle[(queue->min)];
    *res =  queue->res[(queue->min)];
	for (int i=0; i<queue->max; ++i){
    	queue->angle[i]=queue->angle[i+1];
    	queue->res[i] = queue->res[i+1];
    }
    (queue->max)--;
    return 0;
}

void queue_print(const Queue *queue) {
    for (int i=queue->min; i<queue->max; ++i) printf("%d ", queue->angle[i]);
    printf("\n");
}

void queue_print_res(const Queue *queue) {
    for (int i=queue->min; i<queue->max; ++i) printf("%lf ", queue->res[i]);
    printf("\n");
}

int queue_empty (const Queue *queue){
	if (queue->max == queue->min) return 0;
	return 1;
}
