#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

//#include "queue.h"

#define m 1
#define w 0

typedef struct Edge Edge;
typedef struct Node Node;

struct Edge {
	Edge *next;
	Node *main;
	Edge *prev;
};

struct Node {
	int sex;
	char *name;
	int birth;
	int death;
	Edge *edges;
	int visited;
};

typedef struct Tree {
	Node **ks;
	int msize;
	int csize;
} Tree;

typedef struct Item {
    Node *data;
    struct Item *next;
} Item;

typedef struct Queue {
    Item *head;
    Item *tail;
} Queue;

void makepng (Tree *tree, FILE *file);
int D_Png(Tree *tree);
int DPrint(Tree *tree);
int DAddVertex(Tree *tree);
int DAddEdge(Tree *tree);
Node *find (Tree *tree, char *name);
int add_el (Tree *tree, char *name, int sex, int birth, int death);
int add_edge (Tree *tree, char *to, char *from);
int print (Tree *tree);
char *getstr();
char *fgetstr(FILE* file);
int DAddEdge(Tree *tree);
int DChangeVertex(Tree *tree);
int change_death (Tree *tree, char *name, int death);
int change_birth (Tree *tree, char *name, int birth);
int change_sex (Tree *tree, char *name, int sex);
int change_name (Tree *tree, char *name, char *new);
int DDelVertex(Tree *tree);
int DDelEdge(Tree *tree);
int delete_edge (Tree *tree, char *name1, char *name2);
int delete_el (Tree *tree, char *name);
int DTraverse (Tree *tree);
int traverse (Tree *tree, char *name);
int DBellmanFord (Tree *tree);
int bellman_ford (Tree *tree, char *to, char *from);
int find_ind (Tree *tree, Node *main);
int DFloyd (Tree *tree);
int floyd (Tree *tree, char *name, int sum);
int find_floyd (Node *main, char *check);
void destructor (Tree *tree);

Queue *queue_new();
void queue_delete(Queue *queue);
int queue_put(Queue *queue, Node *data);
int queue_get(Queue *queue);
void queue_print(const Queue *queue);
