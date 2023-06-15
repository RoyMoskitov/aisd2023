/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#include "3c.h"
//#include "dia_c.h"
#define HASH 13

//const char *errmsgs[] = {"Successfully", "Key not found", "Table overflow", "There isn't parent key", "Key not found", "Table is empty", "Error opening file", "File format incorrect"};

void destructor(Table* t){
	KeySpace* ks=t->ks;
	free(t->fname);
	free(ks);
}

char *getstr() { 
    int len = 0;
    char* str = malloc(sizeof(char));
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
            int strl = len + lenbuf;
            str = realloc(str, strl+1);
            str = strcat(str, buf);
        }
    } while (n>0);
    return str;
}

int create_table(Table* t, char* fn){
    do {
        printf("Enter the maximum size: "); 
        int n=scanf("%d",&(t->msize));
        if(n<0){
        	return 0;
        }if(n==0){
            printf("Try again\n");
        } else if(n== 1 && (t->msize<1)){
            printf("Try again\n");
            n=0;
        }
    }while(n!=1);
    if (t->fd == NULL) return 0;
    t->fd = fopen(fn, "w+b");
    t->csize=0;
    t->ks=(KeySpace*)calloc((t->msize), sizeof(KeySpace)); 
    fwrite(&t->msize, sizeof(int), 1, t->fd);
    fwrite(&t->csize, sizeof(int), 1, t->fd);
    fwrite(t->ks, sizeof(KeySpace), t->msize, t->fd);
    return 1;
}

int hash_func(char *key, Table *t) {
	int hash, sum = 0, p = HASH;
	for (int i=0; i<strlen(key); ++i){
		sum += key[i]*p;
		p = p*p;
	}
	hash = sum % t->msize;
	return hash;
}

int find_key_ver (Table *t, char* key, int version) {
	int hash, i=0;
	char *str;
	KeySpace *ks = t->ks;
	hash = hash_func(key, t);
	while (i<(t->msize)) {
		if (ks[hash].busy != 0) {
			if (ks[hash].busy == 1){
		        fseek(t->fd, ks[hash].offset, SEEK_SET);
		        str = malloc((ks[hash].len)*sizeof(char));
		        fread(str, sizeof(char), ks[hash].len, t->fd);
				if (strcmp(str, key) == 0 && ks[hash].version == version) {
					free(str);
					return hash;
				}
				free(str);
			}
			if (hash == (t->msize)-1) hash=0;
			else hash++;
		}
		++i;
	}
	return -1;
	
}

int add_el(Table* t, char *key, unsigned int data){ 
    KeySpace* k=t->ks;
    if(t->csize==t->msize) return 2;
    int version = 1, hash;
    for (int i=1; 1; ++i){ 
    	if (find_key_ver(t, key, i) == -1) {
    		version = i;
    		break;
    	}
    }
    hash = hash_func(key, t); 
    while (1) {
		if (t->ks[hash].busy != 1) break;
		if (hash == (t->msize)-1) hash=0;
		else hash++;
	}
    k[hash].data = data;
    k[hash].version = version;
    k[hash].busy = 1;
    k[hash].len = strlen(key)+1;
    fseek(t->fd,0,SEEK_END);
    k[hash].offset = ftell(t->fd);
    fwrite(key, sizeof(char), k[hash].len, t->fd);
    (t->csize)++;
    return 0;
}

int del_el(Table *t, char *key, int version){
    int check = find_key_ver(t, key, version);
    int j=0, qur = t->csize;
    KeySpace *ks = t->ks;
    char *str, *str1;
    if ( check == -1) return 1;
    ks[check].busy = 2;
    (t->csize)--;
    return 0;
}

int print(Table* t){
    KeySpace* ks=t->ks;
    char *str;
    int flag=0;
    if(t->csize==0)return 5;
    for(int i=0; i<(t->msize); i++){
    	if (ks[i].busy != 1) continue;
    	flag=1;
    	str = malloc(ks[i].len * sizeof(char));
    	fseek(t->fd, ks[i].offset, SEEK_SET);
    	fread(str, sizeof(char), ks[i].len, t->fd);
    	printf("%d | %s | %d\n", ks[i].data, str, ks[i].version);
    	free(str);
    }
    if (flag == 0) return 5;
    return 0;
}

KeySpace *find_element (Table *t, char* key, int version) {
	int hash, i=0;
	char *str;
	KeySpace *ks = t->ks;
	hash = hash_func(key, t);
	while (i<(t->msize)) {
		if (ks[hash].busy != 0) {
			if (ks[hash].busy == 1){
		        fseek(t->fd, ks[hash].offset, SEEK_SET);
		        str = malloc((ks[hash].len)*sizeof(char));
		        fread(str, sizeof(char), ks[hash].len, t->fd);
				if (strcmp(str, key) == 0 && ks[hash].version == version) {
					free(str);
					KeySpace *copy = calloc (1, sizeof(KeySpace));
					copy->offset = ks[hash].offset;
					copy->version = ks[hash].version;
					copy->len = ks[hash].len;
					copy->busy = ks[hash].busy;
					copy->data = ks[hash].data;
					return copy;
				}
				free(str);
			}
			if (hash == (t->msize)-1) hash=0;
			else hash++;
		}
		++i;
	}
	return NULL;
	
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

int load(Table* t, char* fn){
    int data, rs;
    char* tinf, *key;
    KeySpace* ks=t->ks;
    FILE *file;
    file = fopen(fn, "r");
    if (file == NULL) return 6;
    int read, count = t->csize;
    do {
	    if(count==t->msize){
	        fclose(file);
	        return 2;
	    }
	    key=fgetstr(file);
	    read = fscanf(file,"%d\n",&data);
	    if(key==NULL) return 7;
	    read += 2;
	    if (read == 3){
	        rs=add_el(t,key,data);
	        free(key);
	        if(rs==2) return 2;
	        count++;
	    }
	    if (read != 3 && !feof(file)) return 7;
    } while (!feof(file));
    fclose(file);
    t->csize=count;
    return 0;
}

int load2(Table* t, char* fn){
    t->fd=fopen(fn, "r+b");
    if (t->fd == NULL) return 0; 
    fread(&(t->msize), sizeof(int), 1, t->fd); 
    t->ks=(KeySpace*)malloc(t->msize*sizeof(KeySpace)); 
    fread(&t->csize, sizeof(int), 1, t->fd);
    fread(t->ks, sizeof(KeySpace), t->msize, t->fd);
    return 1;
}

int save(Table *t){
	if (fd == NULL) return 0;
    fseek(t->fd, sizeof(int), SEEK_SET); 
    fwrite(&t->csize, sizeof(int), 1, t->fd); 
    fwrite(t->ks, sizeof(KeySpace), t->msize, t->fd);
    fclose(t->fd);
    return 1;
}

