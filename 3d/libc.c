/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#include "3c.h"
#include "dia_c.h"
//#define HASH 13

const char *errmsgs[] = {"Successfully", "Key not found", "Table overflow", "There isn't parent key", "Key not found", "Table is empty", "Error opening file", "File format incorrect"};

int D_Add(Table *t){ 
    int rc, n, k, rk;
    char *info;
    printf("Enter element's data:");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;
    printf("Enter key:\n");
    scanf("%*[^\n]");
    scanf("%*c");
    info = getstr();
    if (info == NULL) return 0;
    rc = add_el(t, info, k);
    printf("%s\n", errmsgs[rc]);
    free(info);
    return 1;
}

int D_Del(Table *t){
    int rc, n, k;
    printf("Enter key:");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;  
    printf("Enter the element's version:");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;
    rc = del_el(t, key, k);
    printf("%s\n", errmsgs[rc]);
    free(key);
    return 1;
}

int D_Find_all (Table *t){
    printf("Enter key:");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0; 	
	int check, flag = 0;
	char *str;
	KeySpace *ks = t->ks;
	for (int i=0; i<t->msize; ++i){
		if (ks[i].busy == 1){
			str = malloc(ks[i].len * sizeof(char));
			fseek(t->fd, ks[i].offset, SEEK_SET);
			fread(str, sizeof(char), ks[i].len, t->fd);
			if (strcmp(key,str) == 0) {
				flag = 1;
				printf("%s | %d | %d\n", str, ks[i].data, ks[i].version);
			}
			free(str);
		}
	}
	if (flag == 0) printf("Table is empty\n");
	free(key);
	return 1;
}

int D_Find(Table *t){ 
	int k, n;
    printf("Enter key:");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0; 
    printf("Enter the element's version:");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;       
    char *str;
    //KeySpace *ks = t->ks;
    KeySpace *check = find_element(t, key, k);
    if (check == NULL) {
        printf("Item was not found\n");
    } else {
        str = malloc((check->len) * sizeof(char));
    	fseek(t->fd, check->offset, SEEK_SET);
    	fread(str, sizeof(char), check->len, t->fd);
        printf("%s | %d | %d", str, check->data, check->version);
        free(str);
        free(check);
    }
    free(key);
    return 1;
}

int D_Show(Table *t){
    print(t);;
    return 1;
}

int D_Load(Table *t){
    int rc;
    printf("Enter file name:");
    scanf("%*[^\n]");
    scanf("%*c");
    char* fn = getstr();
    if(fn==NULL) return 0;
    rc = load(t, fn);
    free(fn);
    return 1;
}

int D_Load2(Table* t){ 
    int msize;
    printf("Enter file name:");
    t->fname = getstr();
    if(t->fname == NULL) return 0;
    if (load2(t, t->fname) == 0){ 
        create_table(t, t->fname); 
    }
    return 1;
}
