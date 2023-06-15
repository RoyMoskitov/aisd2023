#include "3g.h"
#include "dia_c.h"
#define HASH 13

//const char *errmsgs[] = {"Successfully", "Key not found", "Table overflow", "There isn't parent key", "Key not found", "Table is empty", "Error opening file", "File format incorrect"};

void destructor(Table* t){
	KeySpace* ks=t->ks;
	for (int i=0; i<(t->msize); ++i){
		if (ks[i].busy == 1) free(ks[i].key);
	}
	free(ks);
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

int create_table(Table* t){
	int create_table(Table* t, char* fn){
    do{
        printf("Enter the maximum size of the table:");
        int n=scanf("%d",&(t->msize));
        if(n<0) return 0;
        else if(n==0) printf("Try again\n");
        else if (n== 1 && (t->msize<1)){
            printf("Try again\n");
            n=0;
        }
    }while(n!=1);
    t->csize=0;
	t->ks=(KeySpace*)calloc((t->msize), sizeof(KeySpace));
    return 1;
}

int hash_func(char *key, Table *t) {
	int hash, sum = 0, p = HASH;
	for (int i=0; i<strlen(key); ++i){
		sum += key[i]*p;
		p = p * p;
	}
	hash = sum % t->msize;
	return hash;
}

KeySpace *find_element (Table *t, char* key, int version){
	int hash, i=0;
	char *str;
	KeySpace *ks = t->ks;
	hash = hash_func(key, t);
	while (i<(t->msize)) {
		if (ks[hash].busy != 0) {	
			if ((ks[hash].busy == 1) && (strcmp(ks[hash].key, key) == 0) && (ks[hash].version == version)) {
				KeySpace *copy = calloc (1, sizeof(KeySpace));
				copy->data = ks[hash].data;
				copy->busy = ks[hash].busy;
				copy->version = ks[hash].version;
				copy->key = strdup(key);
				return copy;
			}
			if (hash == (t->msize)-1) hash=0;
			else hash++;
		}
		++i;
	}
	return NULL;
}

int find_key_ver (Table *t, char* key, int version) {
	int hash, i=0;
	char *str;
	KeySpace *ks = t->ks;
	hash = hash_func(key, t);
	while (i<(t->msize)) {
		if (ks[hash].busy != 0) {	
			if ((ks[hash].busy == 1) && (strcmp(ks[hash].key, key) == 0) && (ks[hash].version == version)) {
				return hash;
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
    k[hash].key = strdup(key);
    (t->csize)++;
    return 0;
}

int del_el(Table *t, char *key, int version){
    int check = find_key_ver(t, key, version);
    int j=0, qur = t->csize;
    KeySpace *ks = t->ks;
    if ( check == -1) return 4;
    ks[check].busy = 2;
    free(ks[check].key);
    return 0;
}

int print(Table* t){
    KeySpace* ks=t->ks;
    int flag=0;
    if(t->csize==0)return 5;
    for(int i=0; i<(t->msize); i++){
    	if (ks[i].busy != 1) continue;
    	flag=1;
    	printf("%d | %s | %d\n", ks[i].data, ks[i].key, ks[i].version);
    }
    if (flag == 0) return 5;
    return 0;
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


