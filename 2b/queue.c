#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

Queue *queue_new() {
    return (Queue *) calloc(1, sizeof(Queue));
}

void queue_delete(Queue *queue) {
    Item *ptr = queue->head, *ptr_prev;
    while (ptr) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(queue);
}

int queue_put(Queue *queue, int angle, int members) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
        return 1;
    }
    //new->flag = 0;
    new->angle = angle;
    new->members = members;
    new->next = NULL;
    if (!queue->head) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    return 0;
}

int queue_put_res(Queue *queue, int angle, double res) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
        return 1;
    }
    //new->flag = 1;
    new->angle = angle;
    new->res = res;
    new->next = NULL;
    if (!queue->head) {
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    return 0;
}

int queue_get(Queue *queue, int *angle, int *members) {
    if (!queue->head) {
        return 1;
    }
    *angle = queue->head->angle;
    *members = queue->head->members;
    if (queue->head == queue->tail) {
    	queue->tail = NULL;
    }
    Item *head = queue->head;
    queue->head = head->next;
    free(head);
    return 0;
}

int queue_get_res(Queue *queue, int *angle, double *sin) {
    if (!queue->head) {
        return 1;
    }
    *angle = queue->head->angle;
    *sin = queue->head->res;
    if (queue->head == queue->tail) {
    	queue->tail = NULL;
    }
    Item *head = queue->head;
    queue->head = head->next;
    free(head);
    return 0;
}

void queue_print(const Queue *queue) {
    Item *ptr = queue->head;
    while (ptr) {
        printf("%d ", ptr->angle);
        ptr = ptr->next;
    }
    printf("\n");
}

void queue_print_res(const Queue *queue) {
    Item *ptr = queue->head;
    while (ptr) {
        printf("%lf ", ptr->res);
        ptr = ptr->next;
    }
    printf("\n");
}

int queue_empty (const Queue *queue){
	 if (!queue->head) return 0;
	 return 1;
}
