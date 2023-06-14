typedef struct Node {
    struct Node *left, *right;
    int data;
    int key;
    bool color;
    int depth;
} Node;

typedef struct Tree {
        Node *ks;
} Tree;

typedef struct Table Table;

int D_Timing (Tree *tree);
Node* createNode(int data, bool color, int key);
Node* rotateLeft(Node* myNode);
Node* rotateRight(Node* myNode);
int red(Node *myNode);
void swapColors(Node *node1, Node *node2);
Node* add_element(Node* myNode, int data, int key, int depth);
void del(Node *node);
void destructor(Tree *tree);
char *getstr();
char *fgetstr(FILE* file);
Node *find_el (Tree *tree, int key);
int D_print_tree (Tree *tree);
void trav_print (Node *node, int space_num);
void traverse (Node *node);
int delete_el (Tree *tree, int key);
Node *find_max (Tree *tree, int key);
void makepng (Node *node, FILE *file);
void around (Tree *tree);
int load(Tree* tree, char* fn);
int D_Png(Tree *tree);
int D_Max (Tree *tree);
int D_Load(Tree *tree);
int D_Del(Tree *tree);
int D_Add(Tree *tree, Table *tab);
int D_Show(Tree *tree);
int D_Find(Tree *tree);
Node* fix(Node* h);
Node* delete_min(Node* h);
Node* delete(Node* h, int key);
Node *flipColors(Node *h);
