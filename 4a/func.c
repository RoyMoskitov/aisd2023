#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <time.h>

int D_print_tree (Tree *tree);
void trav_print (Node *node, int space_num);


int scan_file () {
	printf("Enter file name:\n");
    scanf("%*[^\n]");
    scanf("%*c");
    char *fn = getstr();
    if (fn == NULL) return 0;
    Tree *tree;
    tree = calloc (1, sizeof(Tree));
    tree->ks = NULL;
	FILE *file = fopen(fn, "r");
	while (file) {
		
	}
}


int D_Timing(Tree *tree)  {
FILE *file = fopen("lom.txt", "w");
char t[2] = "\t";
char new[2] = "\n";
Node *root = tree->ks;
char *key[10000], *k, timer[12], number[12];
int n = 10, data[10000], cnt = 100000, i, m, d; 
clock_t first, last; 
srand(time(NULL)); 
//for (int u=0; u < 100; ++u) key[u] = calloc (6, sizeof(char));
//k = calloc(6, sizeof(char));
while (n-- > 0){ 
 //double time_spent = 0.0;
 for (i = 0; i < 10000; ++i) { 
 data[i] = rand() * rand();
 key[i] = create_str(key[i]);
 } 
 for (i = 0; i < cnt; ){ 
 d = rand() * rand();
 k = create_str(k); 
 if (add_el(tree, k, d)) ++i; 
 free(k);
 }  
 m = 0;  
 first = clock(); 
 for (i = 0; i < 10000; ++i)
 find_max(tree, key[i]);
 //find_el(tree, key[i]);
 //for (i = 0; i < 1000; ++i)
 //delete_el(tree, key[i]);
 last = clock(); 
 //printf("%d items was found\n", m); 
 //printf("test #%d, number of nodes = %d, time = %d\n", 90 - n, (90 -  n)*cnt, last-first); 
 /*itoa((90 -  n)*cnt, number);
 itoa(last-first, timer);
 //fwrite(number, sizeof(char), strlen(number), file);
 //fwrite(t, sizeof(char), strlen(t), file);
 fwrite(timer, sizeof(char), strlen(timer), file);
 fwrite(new, sizeof(char), strlen(new), file);*/
 destructor(tree);
 tree->ks = NULL;
 cnt = cnt+100000;
 for (int u=0; u < 10000; ++u) free(key[u]);
 }  
 fclose(file);
//destructor(tree);
return 0; 
}  

char *create_str (char *str) {
	int p = (rand() % 6) + 1;
	str = malloc((p+1)*sizeof(char));
	str[p] = '\0';
	for (int i=0; i<p; ++i) {
		str[i] = (rand()%26) + 'a';
	}
	//printf("%s\n", str);
	return str;
}

void del(Node *node){
	if (node == NULL) return;
	del(node->left);
	del(node->right);
	free(node->key);
	free(node); 
	node = NULL;
}

void destructor(Tree *tree) {
	Node *ptr = tree->ks;
	if (tree->ks != NULL) del(tree->ks);
	free(tree);
	tree = NULL;
}

char *getstr() { 
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
}

Node *find_el (Tree *tree, char *key){
	Node *ptr = tree->ks;
	while (ptr != NULL){
		if (strcmp(ptr->key, key)==0) { 
			return ptr;
		}
		if (strcmp(ptr->key, key)>0){
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
	trav_print(node->left, (node->depth)+strlen(node->key)+space_num);
	for (int i=0; i<space_num; ++i) {
		printf(" ");
	}
	printf("%s\n", node->key);
	trav_print(node->right, (node->depth)+strlen(node->key)+space_num);
}

int mystrcmp (char *str1, char *str2) {
	int min = strlen(str1);
	if (strlen(str1) != strlen(str2)) return -1;
	for (int i=0; i < min; ++i) {
		if (str1[i] != str2[i] && str1[i]+32 != str2[i] && str1[i]-32 != str2[i]) return -1;
	}
	return 0;
}

int add_el(Tree *tree, char *key, int data){
	Node *prev;
	Node *ptr = tree->ks;
	Node *new = calloc (1, sizeof(Node));
	if (!new) return 1;
	new->depth = 0;
	new->left = NULL;
	new->right = NULL;
	new->prev = NULL;
	new->next = NULL;
	new->data = data;
	new->key = strdup(key);
	new->prev_thr;
	if (ptr == NULL){
		tree->ks = new;
	} else {
		while (ptr != NULL) {
			if (mystrcmp(ptr->key, key) == 0) {
				free(new->key);
				free(new);
				(ptr->data)++;
				return 0;
			}
			prev = ptr;
			(new->depth)++;
			if (strcmp(ptr->key, key)>0) {
				ptr = ptr->left;
			} else {
				ptr = ptr->right;
			}
		}
		ptr = new;
		ptr->prev = prev;
		if (strcmp(prev->key, key)<0) prev->right = ptr;
		else prev->left = ptr;
		sew(ptr);
	}
	return 0;
}

void sew_del (Node *qur) {
	Node *prev = qur->prev_thr;
	Node *next = qur->next;
	if (prev != NULL) prev->next = next;
	if (next != NULL) next->prev_thr = prev;
}

void sew (Node *qur) {
	if (qur->prev == NULL) return;
	if (qur->prev->right == qur && qur->prev->left == NULL) {
		Node *prev = qur->prev->prev_thr;
		if (prev != NULL) prev->next = qur;
		qur->next = qur->prev;
		qur->prev_thr = prev;
		qur->prev->prev_thr = qur;
	} else if (qur->prev->right == qur) {
		Node *prev = qur->prev->left;
		if (prev != NULL) prev->next = qur;
		qur->prev_thr = prev;
		qur->next = qur->prev;
		qur->prev->prev_thr = qur;
	} else if (qur->prev->left == qur && qur->prev->right == NULL) {
		Node *prev = qur->prev->prev_thr;
		if (prev != NULL) prev->next=qur;
		qur->prev_thr = prev;
		qur->next = qur->prev;
		qur->prev->prev_thr = qur;
	} else {
		Node *prev = qur->prev->right;
		//Node *prev = qur->prev->right->prev_thr;
		//if (prev != NULL) prev->next = qur;
		while (prev->left != NULL || prev->right != NULL) {
			if (prev->left != NULL) prev = prev->left;
			else if (prev->right != NULL) prev = prev->right;
		}
		qur->prev_thr = prev->prev_thr;
		if (prev->prev_thr != NULL) prev->prev_thr->next = qur;
		qur->next = prev;
		prev->prev_thr = qur;
		//qur->prev->right->prev_thr = qur;
	}
}

void traverse (Node *node) {
	Node *ptr;
	if (node == NULL) return;
	traverse(node->left);    
	traverse(node->right);    
	printf("%s | %d\n", node->key, node->data);
}

int delete_el (Tree *tree, char *key){
	Node *ptr = find_el(tree, key);
	Node *prev;
	if (ptr == NULL) return 1;
	if (ptr->left == NULL && ptr->right == NULL) {
		//printf("case 1\n");
		if (ptr->prev != NULL) {
			prev = ptr->prev;       
			if (prev->right == ptr) prev->right = NULL;
			else prev->left = NULL;
			sew_del(ptr);
		} else {
			tree->ks = NULL;
		}
		free(ptr->key);
		free(ptr);                   
		ptr = NULL;             
		return 0;
	}
	if (ptr->left == NULL && ptr->right != NULL){
		if (ptr == tree->ks){
			//printf("case 2\n");
			tree->ks = ptr->right;
			tree->ks->prev = NULL;
			tree->ks->next = NULL;
			free(ptr->key);
			free(ptr);
			return 0;
		}
		prev = ptr->prev;
		if (prev->left == ptr) {
			prev->left = ptr->right;
		} else {
			prev->right = ptr->right;
		}
		ptr->right->prev = prev;
		ptr->right->next = ptr->next;
		ptr->next->prev_thr = ptr->right;
		free(ptr->key);
		free(ptr);
		return 0;
	}
	if (ptr->left != NULL && ptr->right == NULL){
		//printf("case 3\n");
		if (ptr == tree->ks){
			tree->ks = ptr->left;
			tree->ks->prev = NULL;
			tree->ks->next = NULL;
			free(ptr->key);
			free(ptr);
			return 0;
		}
		prev = ptr->prev;
		if (prev->left == ptr) {
			prev->left = ptr->left;
		} else {
			prev->right = ptr->left;
		}
		ptr->left->prev = prev;
		ptr->left->next = ptr->next;
		ptr->next->prev_thr = ptr->left;
		free(ptr->key);
		free(ptr);
		return 0;
	}
		//printf("case 4\n");
		Node *istok = ptr;
		ptr = ptr->right;
		while (ptr->left != NULL) ptr=ptr->left;
		free(istok->key);
		istok->key = strdup(ptr->key);
		istok->data = ptr->data;
		prev = ptr->prev;
		if (prev->right == ptr) prev->right = ptr->right;
		else prev->left = ptr->right;
		if (ptr->right != NULL) ptr->right->prev = ptr->prev;
		if (ptr->right == NULL) sew_del(ptr);
		else {
			ptr->right->next = ptr->next;
			ptr->next->prev_thr = ptr->right;
		}
		free(ptr->key);
		free(ptr);
		return 0;
}

Node *find_max (Tree *tree, char *key){
	Node *ptr = tree->ks;
	if (ptr == NULL) return NULL;
	while (1) {
		if (strcmp(ptr->key, key) == 0){
			return ptr;
		}
		if ((ptr->left != NULL) && (strcmp(ptr->key, key) > 0)) ptr = ptr->left;
		else if ((ptr->right != NULL) && (strcmp(ptr->key, key) < 0) && (strcmp(ptr->right->key, key) <= 0)) ptr = ptr->right;
		else if (strcmp(ptr->key, key)>0) return NULL;
		else return ptr;
	}
}

void makepng (Node *node, FILE *file) {
	if (node == NULL) return;
	makepng(node->left, file);    
	makepng(node->right, file); 
	if (node->prev != NULL) {   
		char t[2] = "\t";
		char s[2] = "\"";
		fwrite(t, sizeof(char), strlen(t), file);
		fwrite(s, sizeof(char), strlen(s), file);
		fwrite(node->prev->key, sizeof(char), strlen(node->prev->key), file);
		fwrite(s, sizeof(char), strlen(s), file);
		char str[5] = " -> ";
		fwrite(str, sizeof(char), strlen(str), file);
		fwrite(s, sizeof(char), strlen(s), file);
		fwrite(node->key, sizeof(char), strlen(node->key), file);
		fwrite(s, sizeof(char), strlen(s), file);
		char n[2] = "\n";
		fwrite(n, sizeof(char), strlen(n), file);
	}
}

void around (Tree *tree) {
	Node *ptr = tree->ks;
	if (tree->ks == NULL) {
		printf("Tree is empty\n");
		return;
	}
	while (ptr->left != NULL || ptr->right != NULL) {
		if (ptr->left != NULL) ptr = ptr->left;
		else if (ptr->right != NULL) ptr = ptr->right;
	}
	while (ptr != NULL) {
		printf("%s - %d\n", ptr->key, ptr->data);
		ptr = ptr->next;
	}
}

int load(Tree* tree, char* fn){//загружает информацию с файла в структурный массив
    int data, rs;
    char* tinf, *key;
    //Node* ks=t->ks;
    FILE *file;
    file = fopen(fn, "r");
    if (file == NULL) return 6;
    int read;
    do {
            key=fgetstr(file);
            if(key==NULL) return 7;
            read += 2;
            if (read == 3){
                rs=add_el(tree, key, data);
                free(key);
                if(rs==1) return 2;
                //count++;
            }
            if (read != 3 && !feof(file)) return 7;
            if (ferror(file)) {
                fclose(file);
                return 7;
            }
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
    	fwrite(str, sizeof(char), strlen(str), file);
    	if (tree->ks->right == NULL && tree->ks->left == NULL) {
    		fwrite(t, sizeof(char), strlen(t), file);
    		fwrite(sk, sizeof(char), strlen(sk), file);
    		fwrite(&(tree->ks->key), sizeof(char), strlen(tree->ks->key), file);
    		//fwrite(&(tree->ks->data), sizeof(tree->ks->data), 1, file);
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
	int k, n;
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;
    Node *check = find_max(tree, key);
    if (check == NULL) {
        printf("Item was not found\n");
    } else {
        printf("%s | %d\n", check->key, check->data);
    }
    free(key);
    return 1;
}

int D_Find(Tree *tree){ 
    int k, n;
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;
    //KeySpace *ks = t->ks;
    Node *check = find_el(tree, key);
    if (check == NULL) {
        printf("Item was not found\n");
    } else {
        printf("%s | %d\n", check->key, check->data);
    }
    free(key);
    return 1;
}

int D_Show(Tree *tree){
    around (tree);
    return 1;
}


int D_Add(Tree *tree){ 
    int rc, n, k, rk;
    char *info;
    printf("Enter element's data: -->");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;
    printf("Enter key:\n");
    scanf("%*[^\n]");
    scanf("%*c");
    info = getstr();
    if (info == NULL) return 0;
    rc = add_el(tree, info, k);
    if (rc == 1) printf("Memory not allocated\n");
    else if (rc == 2) printf("Key already exists\n");
    else printf("Succesfully\n");
    free(info);
    return 1;
}

int D_Del(Tree *tree){
    int rc, n, k;
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;
    rc = delete_el(tree, key);
    if (rc == 1) printf("Element not found\n");
    else printf("Succesfully\n");
    free(key);
    return 1;
}

int fg(Tree *tree, char *fn) {  
   FILE *mf;
   char sym;
   char *str = malloc(2*sizeof(char));
   str[0] = '\0';
   mf = fopen (fn,"r");
   int len=0;
   if (mf == NULL) {
   		//printf ("Error\n"); 
   		return 6;
   }
   while (1) {
      sym = fgetc (mf);
      if (sym == EOF) {
         if ( feof (mf) != 0) {  
            break;
         } else {
         	return 7;
         }
      }
      if (sym == '.' || sym == ',' || sym == ':' || sym == '-' || sym == ' ' || sym == '\t' || sym == '\n') {
        if (str[0] != '\0') add_el(tree, str, 1);
      	free(str);
      	str = malloc(2*sizeof(char));
      	str[0] = '\0';
      	len = 0;
      } else {
      	len++;
      	str = realloc(str, (len+1)*sizeof(char));
      	str[len-1] = sym;
      	str[len] = '\0';
      }
      
   }
   free(str);
   fclose(mf);
   return 0;
} 


int D_Load(Tree *tree){
    int rc;
    printf("Enter file name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* fn = getstr();
    if(fn==NULL) return 0;
    rc = fg(tree, fn);
    if (rc == 6) printf("Error opening the file\n");
    else if (rc == 7) printf("File format incorrect\n");
    //else if (rc == 2) printf("Key already exists\n");
    else printf("Succesfully\n");
    free(fn);
    return 1;
}
