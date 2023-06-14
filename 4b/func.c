#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#include <math.h>
#include <limits.h>
#include <time.h>
#include "3g.h"

void itoa(char *str, int val) {
        int pp, len, counter=0;
        len = val;
        for (pp = 1; len>10; len /= 10) pp *= 10;
        while (pp>0) {
        	str[counter] = '0' + val / pp;
			counter++;
			val %= pp;
        }
		str[counter] = '\0';
}


int D_Timing(Tree *tree)  {
FILE *file = fopen("lom.txt", "w");
char t[2] = "\t";
char new[2] = "\n";
Node *root = tree->ks;
char timer[12];
int key[10000], k;
int n = 10, data[10000], cnt = 100000, i, m, d;
double time_spent = 0.0;
clock_t first, last;
srand(time(NULL));
while (n-- > 0){
time_spent = 0.0;
for (i = 0; i < 10000; ++i) {
 data[i] =abs(rand() * rand());
 key[i] = abs(rand() * rand());
 }
 for (i = 0; i < cnt; ++i){
 d = abs(rand() * rand());
 k = abs(rand() * rand());
 tree->ks = add_element(tree->ks, d, k, 0);
 tree->ks->color = false;
 }
 m = 0;
 first = clock();
 for (i = 0; i < 10000; ++i){
 //if (find_el(tree, key[i]) != NULL) {
 add_element(tree->ks, data[i], key[i], 0);
 //}
 tree->ks->color = false;
 }
 last = clock();
 //for (i = 0; i < 1000; ++i) find_el (tree, key[i]);
 time_spent += (double) (last-first)/CLOCKS_PER_SEC; 
 //printf("%d items was found\n", m);
 //find_el(tree, key[i]);
 /*for (i = 0; i < 1000; ++i){
 delete(tree->ks, key[i]);
 tree->ks->color = false;
 }*/
 //printf("test #%d, number of nodes = %d, time = %f\n", 10 - n, (10 -  n)*cnt, difftime(last, first));
 //itoa((90 -  n)*cnt, number);
 itoa(timer, last-first);
 destructor(tree);
 tree->ks = NULL;
 cnt = cnt+100000;
 fwrite(timer, sizeof(char), strlen(timer), file);
 fwrite(new, sizeof(char), strlen(new), file);
 }
 fclose(file);
//destructor(tree);
return 1;
}

Node* rotateLeft(Node* ptr) {
    Node *child = ptr -> right;
    ptr->right = child->left;
    child -> left = ptr;
    child -> color = ptr->color;
    ptr->color = true;
    return child;
}

Node* rotateRight(Node* ptr) {
    Node *child = ptr -> left;
    ptr->left = child->right;
    child -> right = ptr;
    child->color = ptr->color;
    ptr -> color = true;
    return child;
}

int red(Node *ptr) {
    if (ptr == NULL) return 0;
    if (ptr->color) return 1;
    else return 0;
}

Node* add_element(Node* ptr, int data, int key, int depth) {
    if (ptr == NULL) {
    	Node *new = calloc (1, sizeof(Node));
    	new -> left = NULL;
    	new -> right = NULL;
    	new -> data = data;
    	new -> key = key;
    	new -> color = true;    	
    	return new;
    }
    if (key < ptr -> key) ptr -> left = add_element(ptr -> left, data, key, depth+1);
    else if (key > ptr -> key) ptr -> right = add_element(ptr -> right, data, key, depth+1);
    else return ptr;
    if (red(ptr -> right) == 1 && red(ptr -> left) == 0) {
        ptr = rotateLeft(ptr);
    }
    if (red(ptr -> left) == 1 && red(ptr -> left -> left) == 1) {
        ptr = rotateRight(ptr);
    }
    if (red(ptr->left)==1 && red(ptr->right)==1) {
		flipColors(ptr);
		/*myNode->color = !myNode->color;
		myNode->left->color = false;
		myNode->right->color = false;*/
    }
    return ptr;
}

void del(Node *node){
	if (node == NULL) return;
	del(node->left);
	del(node->right);
	free(node); 
	node = NULL;
}

void destructor(Tree *tree) {
	Node *ptr = tree->ks;
	if (tree->ks != NULL) del(tree->ks);
	free(tree);
	tree = NULL;
}

/*char *getstr() { 
    int len = 0;
    char* str = (char*)malloc(1);
    char buf[81];
    int n;
    *str='\0';
    do {
        n = scanf("%80[^\n]", buf);
        if (n<0) {
            free(str);
            str = NULL;
            continue;
        }
        if (n==0) {
            scanf("%*c");
        } else {
            int lenbuf = strlen(buf);
            int strl = len+ lenbuf;
            str = (char*)realloc(str, strl+1);
            str = strcat(str, buf);
        }
    } while (n>0);
    return str;
}

char *fgetstr(FILE* file) {
    int len = 0, i, k;
    char* str = (char*)malloc(1);
    char buf[81];
    int n;
    *str='\0';
    n = fscanf(file, "%s\n", buf);


    if (n<0) {
        free(str);
        return NULL;
    }
    if (n==0) {
        scanf("%*c");
    } else {
        int lenbuf = strlen(buf);
        int strl = len + lenbuf;
        str = (char*)realloc(str, strl+1);
        str = strcat(str, buf);
    }
    return str;
}*/

Node *find_el (Tree *tree, int key){
	Node *ptr = tree->ks;
	while (ptr != NULL){
		if (ptr->key == key) { 
			return ptr;
		}
		if (ptr->key > key){
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}
	return NULL;
}

int D_print_tree (Tree *tree) {
	Node *item = tree->ks;
	if (item == NULL) return 1;
	trav_print(item, 0);
	return 1;
}

void trav_print (Node *node, int space_num) {
	if (node == NULL) return;
	trav_print(node->left, space_num+4);
	for (int i=0; i<space_num; ++i) {
		printf(" ");
	}
	printf("%d\n", node->key);
	trav_print(node->right, space_num+4);
}

void traverse (Node *node) {
	Node *ptr;
	if (node == NULL) return;
	traverse(node->left);    
	traverse(node->right);    
	printf("%d | %d", node->key, node->data);
	if (node->color == true) printf(" | RED\n");
	else printf(" | BLACK\n");
}

Node* fix(Node* qur) {
	if (red(qur->right)) qur = rotateLeft(qur);
	if (red(qur->left) && red(qur->left->left)) qur = rotateRight(qur);
	if (red(qur->left) && red(qur->right)) flipColors(qur);
	return qur;
}

Node* delete_min(Node* h) {
	if (h->left == NULL) {
		free(h);
		return NULL;
	}
	if (red(h->left) == 0 && red(h->left->left) == 0) {
		flipColors(h);
		if (h->right != NULL && red(h->right->left)) {
			h->right = rotateRight(h->right);
			h = rotateLeft(h);
			flipColors(h);
		}
	}
	h->left = delete_min(h->left);
	return fix(h);
}
	
Node* find_min(Node* h) {
	while (h->left != NULL) {
		h = h->left;
	}
	return fix(h);
}

Node *flipColors (Node *qur) {
	if (qur->color == false) qur->color = true;
	else qur->color = false;
	if (qur->left != NULL) {
		if (qur->left->color == false) qur->left->color = true;
		else qur->left->color = false;
	}
	if (qur->right != NULL) {
		if (qur->right->color == false) qur->right->color = true;
		else qur->right->color = false;
	}	
}

Node* delete(Node* h, int key) {
	if (key < h->key) {
		if (red(h->left) == 0 && red(h->left->left) == 0) {
			//h = move_red_left(h);
			flipColors(h);
			if (h->right != NULL && red(h->right->left)) {
				h->right = rotateRight(h->right);
				h = rotateLeft(h);
				flipColors(h);
			}
		}
		h->left = delete(h->left, key);
	} else {
		if (red(h->left)) {
			h = rotateRight(h);
		}
		if (key == h->key && (h->right == NULL)) {
			free(h);
			return NULL;
		}
		if (red(h->right) == 0 && red(h->right->left) == 0) {
			flipColors(h);
			if (h->left != NULL && red(h->left->left)) {
				h = rotateRight(h);
				flipColors(h);
			}
		}
		if (key == h->key) {
			Node* min_node = find_min(h->right);
			h->key = min_node->key;
			h->right = delete_min(h->right);
		} else {
			h->right = delete(h->right, key);
		}
	}
	return fix(h);
}

Node* find_max (Tree *tree, int key) {
    int min = INT_MAX;
    Node *qur = tree->ks;
    Node* res;
    int flag=0;
    while (qur != NULL) {
        int diff = qur->key - key;
        if (diff < 0) diff = diff*(-1);
        if (diff < min && qur->key != key) {
            min = diff;
            res = qur;
            flag=1;
        }
        if (qur->key < key) {
            qur = qur->right;
        } else {
            qur = qur->left;
        }
    }
    if (flag == 1) return res;
    else return NULL;
}

void makepng (Node *node, FILE *file) {
	if (node == NULL) return;
	char it[12];
	if (node->left != NULL) {
		char t[2] = "\t";
		char s[2] = "\"";
		fwrite(t, sizeof(char), strlen(t), file);
		fwrite(s, sizeof(char), strlen(s), file);
		itoa(it, node->key);
		fwrite(it, sizeof(char), strlen(it), file);
		fwrite(s, sizeof(char), strlen(s), file);
		char str[5] = " -> ";
		fwrite(str, sizeof(char), strlen(str), file);
		fwrite(s, sizeof(char), strlen(s), file);
		itoa(it,node->left->key);
		fwrite(it, sizeof(char), strlen(it), file);
		fwrite(s, sizeof(char), strlen(s), file);
		char n[2] = "\n";
		fwrite(n, sizeof(char), strlen(n), file);
	}
        if (node->right != NULL) {
                char t[2] = "\t";
                char s[2] = "\"";
                fwrite(t, sizeof(char), strlen(t), file);
                fwrite(s, sizeof(char), strlen(s), file);
                itoa(it, node->key);
                fwrite(it, sizeof(char), strlen(it), file);
                fwrite(s, sizeof(char), strlen(s), file);
                char str[5] = " -> ";
                fwrite(str, sizeof(char), strlen(str), file);
                fwrite(s, sizeof(char), strlen(s), file);
				itoa(it, node->right->key);
				fwrite(it, sizeof(char), strlen(it), file);
                //fwrite(&(node->right->key), sizeof(int), 1, file);
                fwrite(s, sizeof(char), strlen(s), file);
                char n[2] = "\n";
                fwrite(n, sizeof(char), strlen(n), file);
        }
	makepng(node->left, file);
	makepng(node->right, file);
}

int load(Tree* tree, char* fn){
    int data, rs, key, counter=1;
    char el;
    char* tinf;
    FILE *file;
    file = fopen(fn, "r");
    if (file == NULL) return 6;
    int read=0;
    do {
           read = fscanf(file,"%d",&key);
           fscanf(file, "%c", &el);
           //printf("%d\n", key);
           if (read == 1) {
                tree->ks = add_element(tree->ks, counter, key, 0);
                tree->ks->color = false;
            } else {
                break;
            }
            if (el == '\n') counter++; 
            //if (read != 1 && !feof(file)) return 7;
            /*if (ferror(file)) {
                fclose(file);
            }*/
            //read = 0;
    } while (!feof(file));
    fclose(file);
    return 0;
}

int D_Png(Tree *tree){
    int rc;
    FILE *file;
    file = fopen("love.gv", "w");
    if (file == NULL) {
        printf("Error opening the file\n");
    } else if (tree->ks == NULL) {
        printf("Tree is empty\n");
    } else {
        char str[13] = "digraph G {\n";
        char sk[2] = "\"";
        char t[2] = "\t";
		char it[12];
        fwrite(str, sizeof(char), strlen(str), file);
        if (tree->ks->right == NULL && tree->ks->left == NULL) {
                fwrite(t, sizeof(char), strlen(t), file);
                fwrite(sk, sizeof(char), strlen(sk), file);
                itoa(it, tree->ks->key);
				fwrite(it, sizeof(char), strlen(it), file);
                //fwrite(&(tree->ks->key), sizeof(int), 1, file);
                fwrite(sk, sizeof(char), strlen(sk), file);
                char n[2] = "\n";
                fwrite(n, sizeof(char), strlen(n), file);
        } else {
        	makepng(tree->ks, file);
	}
        char end[2] = "}";
        fwrite(end, sizeof(char), strlen(end), file);
        printf("Succesfully\n");
    }
    fclose(file);
    system("dot -Tpng love.gv -o love.png");
    system("catimg -w 300 love.png");
    return 1;
}


int D_Max (Tree *tree){
	int key, n;
    printf("Enter key: -->");
    n = scanf("%d", &key);
    if(n <= 0 || key<=0) return 0;
    Node *check = find_max(tree, key);
    if (check == NULL) {
        printf("Item was not found\n");
    } else {
        printf("%d | %d\n", check->key, check->data);
    }
    return 1;
}

int D_Find(Tree *tree){ 
    int key, n;
    printf("Enter key: -->");
    n = scanf("%d", &key);
    if(n <= 0 || key<=0) return 0;
    int k;
    Node *check = find_el(tree, key);
    if (check == NULL) {
        printf("Item was not found\n");
    } else {
        printf("Line № %d\n", check->data);
    }
    return 1;
}

int D_Show(Tree *tree){
    traverse (tree->ks);
    return 1;
}


int D_Add(Tree *tree, Table *tab){
    int rc, n, p, k, rk;
    int info;
    printf("Enter element's data: -->");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;
    printf("Enter key:\n");
    p = scanf("%d", &info);
    if(p <= 0 || info<=0) return 0;
    if (find_el(tree, info) != NULL) printf("Key exists\n");
    else {
    	add_el1(tab, info, k);
    	tree->ks = add_element(tree->ks, k, info, 0);
    	tree->ks->color = false;
    	printf("Succesfully\n");
    }
    return 1;
}
 
int D_Del(Tree *tree){
    int rc=0, n, key;
    printf("Enter key: -->");
	n = scanf("%d",&key);
	if(n <= 0 || key<=0) return 0;
	if (find_el(tree, key) == NULL) {
		printf("Element not found\n");
	} else {
		tree->ks = delete(tree->ks, key);
		if (tree->ks) tree->ks->color = false;
		else tree->ks = NULL;
    	printf("Succesfully\n");
	}
    return 1;
}

int D_Load(Tree *tree){
    int rc;
    printf("Enter file name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* fn = getstr();
    if(fn==NULL) return 0;
    rc = load(tree, fn);
    if (rc == 6) printf("Error opening the file\n");
    else if (rc == 7) printf("File format incorrect\n");
    else if (rc == 2) printf("Key already exists\n");
    else printf("Succesfully\n");
    free(fn);
    return 1;
}
