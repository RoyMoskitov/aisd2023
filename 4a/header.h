#ifndef FUNC_H
#define FUNC_H

typedef struct Node {
		int depth;
        unsigned int data;
        char *key;
        struct Node *prev;
        struct Node *left;
        struct Node *right;
        struct Node *next;
	struct Node *prev_thr;
} Node;

typedef struct Tree {
        Node *ks;
} Tree;

char *create_str (char *str);
int D_Timing(Tree *tree);
void traverse (Node *node);
void destructor(Tree *tree);
char *getstr();
char *fgetstr(FILE* file);
Node *find_el (Tree *tree, char *key);
int add_el(Tree *tree, char *key, int data);
void sew (Node *qur);
int delete_el (Tree *tree, char *key);
Node *find_max (Tree *tree, char *key);
void around (Tree *tree);
int load(Tree* tree, char* fn);
int D_Max (Tree *tree);
int D_Find(Tree *tree);
int D_Show(Tree *tree);
int D_Add(Tree *tree);
int D_Del(Tree *tree);
int D_Load(Tree *tree);
int D_Png(Tree *tree);
void sshivka (Node *qur, Node *prev);
void del(Node *node);
void makepng (Node *node, FILE *file);
int D_print_tree (Tree *tree);
void trav_print (Node *node, int space_num);


#endif
