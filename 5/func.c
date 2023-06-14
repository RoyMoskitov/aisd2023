#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "head.h"
//#include "queue.h"

#define m 1
#define w 0

void makepng (Tree *tree, FILE *file) {
	Node **arr = tree->ks;
	Edge *ptr;
	for(int i=0; i<tree->csize; ++i) {
		ptr = arr[i]->edges;
		if (ptr != NULL) {
			while (ptr != NULL) {
				//printf (" <-> %s", ptr->main->name);
                char t[2] = "\t";
                char s[2] = "\"";
                fwrite(t, sizeof(char), strlen(t), file);
                fwrite(s, sizeof(char), strlen(s), file);
                fwrite(arr[i]->name, sizeof(char), strlen(arr[i]->name), file);
                fwrite(s, sizeof(char), strlen(s), file);
                char str[5] = " -> ";
                fwrite(str, sizeof(char), strlen(str), file);
                fwrite(s, sizeof(char), strlen(s), file);
                fwrite(ptr->main->name, sizeof(char), strlen(ptr->main->name), file);
                fwrite(s, sizeof(char), strlen(s), file);
                char n[2] = "\n";
                fwrite(n, sizeof(char), strlen(n), file);
				ptr = ptr->next;
			}
		} else {
                char t[2] = "\t";
                char s[2] = "\"";
                fwrite(t, sizeof(char), strlen(t), file);
                fwrite(s, sizeof(char), strlen(s), file);
                fwrite(arr[i]->name, sizeof(char), strlen(arr[i]->name), file);
                fwrite(s, sizeof(char), strlen(s), file);
                char n[2] = "\n";
                fwrite(n, sizeof(char), strlen(n), file);			
		}
		//printf("\n");
	}
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
        makepng(tree, file);
        char end[2] = "}";
        fwrite(end, sizeof(char), strlen(end), file);
        printf("Succesfully\n");
    }
    fclose(file);
    system("dot -Tpng love.gv -o love.png");
    system("catimg -w 300 love.png");
    return 0;
}


/*void makepng (Node *node, FILE *file) {
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
}*/



void destructor (Tree *tree) {
	Node **arr = tree->ks;
	Edge *ptr, *prev;
	for (int i=0; i<tree->csize; ++i) {
		ptr = arr[i]->edges;
		if (ptr != NULL) {
			while (ptr->next != NULL) ptr = ptr->next;
			while (ptr != NULL) {
				prev = ptr;
				ptr = ptr->prev;
				if (prev != NULL) free(prev);
			}
		}
		free(arr[i]->name);
		free(arr[i]);
	}
	//free(arr);
	free(tree->ks);
	free(tree);

}

int DFloyd (Tree *tree) {
    int rc, sum;
    char *name;
    printf("Enter person's, whose inheritance should be divided: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    name = getstr();
    if (name == NULL) return 1;
    printf("Enter the amount of inheritance (in $): -->");
    rc = scanf("%d", &sum);
    if (rc <= 0 || sum<=0) return 1;
    rc = floyd (tree, name, sum);
    if (rc == 1) printf("Person doesn't exist\n");
    else printf("Succesfully\n");
    free(name);
    return 0;	
}

int floyd (Tree *tree, char *name, int sum) {
	if (find(tree, name) == 0) return 1;
	int dist[tree->csize][tree->csize], p;
	Node *ptr;
	Node **arr = tree->ks;
	int start;
	for (int i=0; i<tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) start = i;
		for (int j=0; j<tree->csize; ++j) {
			if (i==j) dist[i][j] = 0;
			else dist[i][j] = find_floyd(arr[i], arr[j]->name);
		}
	}
	for (int k=0; k<tree->csize; ++k) {
		for (int i=0; i<tree->csize; ++i) {
			for (int j=0; j<tree->csize; ++j) {
				if ((dist[i][k] != INT_MAX) && (dist[k][j] != INT_MAX) && (dist[i][j] > dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	//for (int i=0; i<tree->csize; ++i) printf("%d ",dist[start][i]);
	float x=1, counter=0;
	for (int i=0; i<tree->csize; ++i) {
		if ((dist[start][i] != 0) && (dist[start][i] != INT_MAX) && (arr[i]->death == 0)) {
			for (int l=dist[start][i]; l>1; l--) x=x/2;
			counter += x;
			x = 1; 
		}
	}
	counter = sum/counter;
	for (int i=0; i<tree->csize; ++i) {
		if ((dist[start][i] != 0) && (dist[start][i] != INT_MAX) && (arr[i]->death == 0)) {
			for (int l=dist[start][i]; l>1; l--) x=x/2;
			x = x*counter;
			printf("%f - for %s\n", x, arr[i]->name);			
			x = 1;
		}
	}	
	return 0;
}

int find_floyd (Node *main, char *check) {
	Edge *ptr = main->edges;
	while (ptr != NULL) {
		if (strcmp(ptr->main->name, check) == 0) return 1;
		ptr = ptr->next;
	}
	return INT_MAX;
}

int DBellmanFord (Tree *tree) {
    int rc;
    char *to, *from;
    printf("Enter 1 person's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    to = getstr();
    if (to == NULL) return 1;
    printf("Enter 2 person's name: -->");
    from = getstr();
    if (from == NULL) return 1;
    rc = bellman_ford(tree, to, from);
    if (rc == 1) printf("Someone doesn't exist\n");
    else printf("Succesfully\n");
    free(to);
    free(from);
    return 0;	
}

int bellman_ford (Tree *tree, char *from, char *to) {
	Node **arr = tree->ks;
	int flag1=0, flag2=0, ind, fin, p, count=0, c=0;
	for (int i=0; i<tree->csize; ++i) {
		if (strcmp(arr[i]->name, from) == 0) {
			flag1 = 1;
			ind = i;
		}
		if (strcmp(arr[i]->name, to) == 0) {
			flag2=1;
			fin = i;
		}
	}
	//printf("%d %d\n", ind, fin);
	if (flag1 == 0 || flag2 == 0) return 1;
	int e[tree->csize];
	int path[tree->csize];
	for (int i=0; i<tree->csize; ++i) {
		e[i] = INT_MAX;
		path[i] = -1;
	}
	e[ind] = 0;
	Edge *ptr;
	for (int j=0; j<(tree->csize)-1; ++j) {
		for (int i=ind; ; i = (i+1)%(tree->csize)) {
			ptr = arr[i]->edges;
			while (ptr != NULL) {
				p = find_ind(tree, ptr->main);
				//printf("%d\n", p);
				if ((p != INT_MAX) && (e[i] != INT_MAX) && (e[p] > e[i]+1)) {
					path[p] = i;
					e[p] = e[i]+1;
				}
				ptr = ptr->next; 
			}
			count++;
			if (count == tree->csize) break;
		}
		count = 0;
	}
	if (e[fin] == INT_MAX) printf("There is no way between them\n");
	else {
		int pr = fin;
		while (1) {
			printf ("%s", arr[fin]->name);
			fin = path[fin];
			if (fin == -1) break;
			printf(" - ");
		}
		printf("\n");
		printf("Number of relatives between them: %d\n", e[pr]-1);
	}
	return 0;
}

int find_ind (Tree *tree, Node *main) {
	Node **arr = tree->ks;
	for (int i=0; i<tree->csize; ++i) {
		if (strcmp(arr[i]->name, main->name) == 0) return i;
	}
	return INT_MAX;
}

int DChangeVertex(Tree *tree){
    int k, n;
    printf("Enter person's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* name = getstr();
    if(name==NULL) return 1;
    if (find(tree, name) == NULL) {
    	printf("Person doesn't exist\n");
    	free(name);
    	return 0;
    }
    printf("What do you want to change?\n1 - birth date\n2 - death date\n3 - name\n4 - sex\n");
    scanf("%d", &k);
    switch (k) {
    	case 1:
    		int birth;
    		n = scanf("%d", &birth);
    		if(n <= 0 || birth<=0) {
    			free(name);
    			return 1;
    		}
    		n = change_birth(tree, name, birth);
    		break;
    	case 2:
    		int death;
    		n = scanf("%d", &death);
    		if(n <= 0 || death<=0) {
    			free(name);
    			return 1;
    		}
    		n = change_death(tree, name, death);
    		break;
    	case 3:
     		scanf("%*[^\n]");
   			scanf("%*c");   		
    		char *new = getstr();
    		if(new==NULL) {
    			free(name);
    			return 1;
    		}
    		n = change_name(tree, name, new);
    		break;
    	case 4:
    		int sex;
    		n = scanf("%d", &sex);
    		if(n <= 0 || (sex != 0 && sex != 1)) {
    			free(name);
    			return 1;
    		}
    		n = change_sex(tree, name, sex);
    		break;
    	default: 
    		free(name);
    		return 0;
    	    		
    } 
	printf("Successfully\n");
    free(name);
    return 0;
}

int change_death (Tree *tree, char *name, int death) {
	Node **arr = tree->ks;
	for (int i=0; i < tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) arr[i]->death = death;
	}
	return 0;
}

int change_birth (Tree *tree, char *name, int birth) {
	Node **arr = tree->ks;
	for (int i=0; i < tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) arr[i]->birth = birth;
	}
	return 0;
}

int change_sex (Tree *tree, char *name, int sex) {
	Node **arr = tree->ks;
	for (int i=0; i < tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) arr[i]->sex = sex;
	}
	return 0;
}

int change_name (Tree *tree, char *name, char *new) {
	Node **arr = tree->ks;
	for (int i=0; i < tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) arr[i]->name = new;
	}
	return 0;
}

int DPrint(Tree *tree){
    print (tree);
    return 0;
}

int DTraverse (Tree *tree) {
	char *name;
	int n;
    printf("Enter person's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    name = getstr();
    if (name == NULL) return 1;
	n = traverse(tree, name);
	if (n == 1) printf("This person doesn't exist\n");
	free(name);
	return 0;
}

int traverse (Tree *tree, char *name) {
	int flag = 0;
	Node *ptr = NULL;
	Node **arr = tree->ks;
	for (int i=0; i<tree->csize; ++i) {
		arr[i]->visited = 0;
		if (strcmp(arr[i]->name, name) == 0) {
			ptr = arr[i];
			flag = 1;
		}
	}
	if (flag == 0) return 1;
	Queue *queue = queue_new();
	queue_put(queue, ptr);
	ptr->visited = 1;
	while (queue->head != NULL) {
		ptr  = queue->head->data;
		queue_get(queue);
		Edge *temp = ptr->edges;
		while (temp != NULL) {
			if (temp->main->visited == 0) {
				temp->main->visited = 1;
				queue_put(queue, temp->main);
			}
			temp=temp->next;
		}
	}	
	queue_delete(queue);
	return 0;
}

int DAddVertex(Tree *tree){
    int n, sex, birth, death, check, rc;
    char *name;
    printf("Enter person's sex: -->");
    n = scanf("%d",&sex);
    if(n <= 0 || (sex != 0 && sex != 1)) return 1;
    printf("Enter person's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    name = getstr();
    if (name == NULL) return 1;
    printf("Enter person's date of birth: -->");
    n = scanf("%d",&birth);
    if(n <= 0 || birth<0) return 1;
    printf("Enter person's date of death: -->");
    n = scanf("%d",&death);
    if(n <= 0 || death<0) return 1;
    if (tree->csize == tree->msize) {
    	tree->msize = 2*(tree->msize);
    	tree->ks = realloc (tree->ks, (tree->msize)*sizeof(Node *));
    }
    rc = add_el(tree, name, sex, birth, death);
    if (rc == 1) printf("Not enough space\n");
    else if (rc == 2) printf("Person already exists\n");
    else printf("Succesfully\n");
    free(name);
    return 0;
}

int DAddEdge(Tree *tree){
    int rc;
    char *to, *from;
    printf("Enter child's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    to = getstr();
    if (to == NULL) return 1;
    printf("Enter parent's name: -->");
    from = getstr();
    if (from == NULL) return 1;
    //printf("%s %s\n", to, from);
    rc = add_edge(tree, to, from);
    if (rc == 1) printf("Someone doesn't exist\n");
    else if (rc == 2) printf("This connection already exists\n");
    else {
    	add_edge(tree, from, to);
    	printf("Succesfully\n");
    }
    free(to);
    free(from);
    return 0;
}

Node *find (Tree *tree, char *name) {
	Node **arr = tree->ks;
	for (int i=0; i < tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) return arr[i];
	}
	return NULL;
}

int add_el (Tree *tree, char *name, int sex, int birth, int death) {
	Node **arr = tree->ks;
	//printf("%d %d\n", tree->csize, tree->msize);
	if (find(tree, name) != NULL) return 2;
	if (tree->csize == tree->msize) return 1;
	arr[tree->csize] = calloc(1, sizeof(Node));
	arr[tree->csize]->sex = sex;
	arr[tree->csize]->death = death;
	arr[tree->csize]->birth = birth;
	arr[tree->csize]->name = strdup(name);
	//arr[tree->csize]->edges = malloc(sizeof(Edge));	
	arr[tree->csize]->edges = NULL;
	(tree->csize)++;
	return 0;
}

int add_edge (Tree *tree, char *to, char *from) {
	Node **arr = tree->ks;
	Node *start = NULL, *finish = NULL;
	for (int i=0; i<tree->csize; ++i){
		if (strcmp(arr[i]->name, from) == 0) {
			start = arr[i];
		}
		if (strcmp(arr[i]->name, to) == 0) {
			finish = arr[i];
		}	
		if (start != NULL && finish != NULL) break;
	}
	if (start == NULL || finish == NULL) return 1;
	if (start->edges == NULL) {
		start->edges = malloc(sizeof(Edge));
		start->edges->main = finish;
		start->edges->next = NULL;
		start->edges->prev = NULL;
		return 0;
	} else {
		Edge *ptr = start->edges;
		while (1) {
			if (strcmp(ptr->main->name, to) == 0) return 2;
			if (ptr->next == NULL) break;
			ptr = ptr->next;
		}
		Edge *prev = ptr;
		ptr=ptr->next;
		ptr = malloc(sizeof(Edge));
		prev->next = ptr;
		ptr->main = finish;
		ptr->next = NULL;
		ptr->prev = prev;
		return 0;
	}
}

int print (Tree *tree) {
	Node **arr = tree->ks;
	Edge *ptr;
	for(int i=0; i<tree->csize; ++i) {
		printf ("%s | %d | %d | %d |", arr[i]->name, arr[i]->sex, arr[i]->birth, arr[i]->death);
		ptr = arr[i]->edges;
		while (ptr != NULL) {
			printf (" <-> %s", ptr->main->name);
			ptr = ptr->next;
		}
		printf("\n");
	}
	return 0;
}

int DDelVertex(Tree *tree){
    int rc, n, k;
    printf("Enter person's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* name = getstr();
    if(name == NULL) return 0;
    n = delete_el(tree, name);
    if (n == 1) printf("Element not found\n");
    else printf("Succesfully\n");
    free(name);
    return 0;
}

int DDelEdge(Tree *tree){
    int rc, n, k;
    printf("Enter 1 person's name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* name1 = getstr();
    if(name1 == NULL) return 0;
    printf("Enter 2 person's name: -->");
    char* name2 = getstr();
    if(name2 == NULL) return 0;
    n = delete_edge(tree, name1, name2);
    if (n == 1) printf("Element not found\n");
    else {
    	delete_edge(tree, name2, name1);
    	printf("Succesfully\n");
    }
    free(name1);
    free(name2);
    return 0;
}

int delete_edge (Tree *tree, char *name1, char *name2) {
	Node **arr = tree->ks;
	for (int i=0; i<tree->csize; ++i) {
		if (strcmp(name1, arr[i]->name) == 0) {
			Edge *ptr = arr[i]->edges;
			while (ptr != NULL) {
				if (strcmp(ptr->main->name, name2) == 0) {
					if (ptr->prev == NULL) {
						//ptr->next->prev = NULL;
						arr[i]->edges = ptr->next;
						free(ptr);
						if (arr[i]->edges) arr[i]->edges->prev = NULL;
						else arr[i]->edges = NULL;
						return 0;
					} else {
						Edge *prev = ptr->prev;
						Edge *n = ptr->next;
						prev->next = n;
						if (n != NULL) n->prev = prev;
						free(ptr);
						return 0;
					}
				}
				ptr = ptr->next;
			}
			return 1;
		}
	}
	return 1;
}

int delete_el (Tree *tree, char *name) {
	Node **arr = tree->ks;
	if (find(tree, name) == NULL) return 1;
	for (int i=0; i<tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) != 0) {
			delete_edge(tree, arr[i]->name, name);
		}
	}
	for (int i=0; i<tree->csize; ++i) {
		if (strcmp(arr[i]->name, name) == 0) {
			Edge *ptr = arr[i]->edges;
			if (ptr != NULL) {
				while (ptr->next != NULL) ptr=ptr->next;
				while (ptr != NULL) {
					Edge *pr = ptr;
					ptr=ptr->prev;
					free(pr);
				}
			}
			free(arr[i]->name);
			free(arr[i]);
			for (int j=i; j<tree->csize-1; ++j) arr[j]=arr[j+1];
			(tree->csize)--;
		}	
	}
	return 0;
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

int queue_put(Queue *queue, Node *data) {
    Item *new = (Item *) malloc(sizeof(Item));
    if (!new) {
        return 1;
    }
    new->data = data;
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

int queue_get(Queue *queue) {
    if (!queue->head) {
        return 1;
    }
    //output = queue->head->data;
    printf("%s\n",queue->head->data->name);
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
        printf("%s ", ptr->data->name);
        ptr = ptr->next;
    }
    printf("\n");
}

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

