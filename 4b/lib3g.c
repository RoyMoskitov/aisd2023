
#include "3g.h"
#include "dia_c.h"
#define HASH 13
#define BUF 5

//const char *errmsgs[] = {"Successfully", "Key not found", "Table overflow", "There isn't parent key", "Key not found", "Table is empty", "Error opening file", "File format incorrect"};

void destructor1(Table* t){
	KeySpace* ks=t->ks;
	/*for (int i=0; i<(t->msize); ++i){
		if (ks[i].busy == 1) free(ks[i].key);
	}*/
	free(ks);
}

char *getstr() { // робит
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
    int n;
    do{
        //printf("Enter the maximum size of the table: --> ");
        //n=scanf("%d",&(t->msize));
        t->msize = BUF;
        n=1;
        if(n<0){
                return 0;
                break;
        }if(n==0){
            printf("Incorrect value.True again!\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
        if(n== 1 && (t->msize<1)){
            printf("Incorrect value.True again!\n");
            n=0;
        }
    }while(n!=1);
    t->csize=0;
    t->ks=(KeySpace*)calloc((t->msize), sizeof(KeySpace)); // выделяем память под таблицу
    return 1;
}

int hash_func(int key, Table *t) {
	int hash, sum = 0, p = HASH;
	/*for (int i=0; i<strlen(key); ++i){
		sum += key[i]*p;
		p = p * p;
	}*/
	hash = key % t->msize;
	return hash;
}

/*KeySpace *find_element1 (Table *t, int key, int version){
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
				copy->key = key;
				return copy;
			}
			if (hash == (t->msize)-1) hash=0;
			else hash++;
		}
		++i;
	}
	return NULL;
}*/

int find_key_ver (Table *t, int key) {
	int hash, i=0;
	char *str;
	KeySpace *ks = t->ks;
	hash = hash_func(key, t);
	while (i<(t->msize)) {
		if (ks[hash].busy != 0) {	
			if ((ks[hash].busy == 1) && ks[hash].key == key) {
				return hash;
			}
			if (hash == (t->msize)-1) hash=0;
			else hash++;
		}
		++i;
	}
	return -1;
	
}

int add_el1(Table* t, int key, unsigned int data){ //не робит
    KeySpace* k=t->ks;
    int min=100000, min_key;
    if(t->csize==t->msize) {
    	for (int i=0; i<t->csize; ++i) {
    		if (k[i].version < min) {
    			min = k[i].version;
    			min_key = k[i].key;
    		}
    	}
    	del_el1(t, min_key, min);
    	(t->csize)--;
    }
    int version = 1, hash;
    /*for (int i=1; 1; ++i){ 
    	if (find_key_ver(t, key, i) == -1) {
    		version = i;
    		break;
    	}
    }*/
    version = t->csize;
    hash = hash_func(key, t); 
    while (1) {
		if (t->ks[hash].busy != 1) break;
		if (hash == (t->msize)-1) hash=0;
		else hash++;
	}
    k[hash].data = data;
    k[hash].version = version;
    k[hash].busy = 1;
    k[hash].key = key;
    (t->csize)++;
    return 0;
}

int del_el1(Table *t, int key, int version){
    int check = find_key_ver(t, key);
    int j=0, qur = t->csize;
    KeySpace *ks = t->ks;
    if ( check == -1) return 4;
    ks[check].busy = 2;
    //free(ks[check].key);
    return 0;
}

int print1(Table* t){
    KeySpace* ks=t->ks;
    int flag=0;
    if(t->csize==0)return 5;
    for(int i=0; i<(t->msize); i++){
    	if (ks[i].busy != 1) continue;
    	flag=1;
    	printf("%d | %d\n", ks[i].data, ks[i].key);
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

/*int load(Table* t, char* fn){
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
	        if(rs==1) count--;
	        if(rs==2) return 2;
	        count++;
	    }
	    if (read != 3 && !feof(file)) return 7;
	    if (ferror(file)) {
	        fclose(file);
	        return 7;
	    }
    } while (!feof(file));
    fclose(file);
    t->csize=count;
    return 0;
}

int load2(Table* t, char* fn){// робит 
    t->fd=fopen(fn, "r+b");// открывается существующий файл на чтение и запись
    if (t->fd == NULL) return 0; // если файл не открылся
    fread(&(t->msize), sizeof(int), 1, t->fd); // считываем размер вектора
    printf("%d\n", t->msize);
    t->ks=(KeySpace*)malloc(t->msize*sizeof(KeySpace)); //выделяем память под таблицу
    fread(&t->csize, sizeof(int), 1, t->fd);// считываем размер таблицы
    fread(t->ks, sizeof(KeySpace), t->msize, t->fd);
    return 1;
}

int save(Table *t){
    fseek(t->fd, sizeof(int), SEEK_SET); // пропуск поля, где задаётся длина вектора
    fwrite(&t->csize, sizeof(int), 1, t->fd); // записываем в файл размер таблицы
    fwrite(t->ks, sizeof(KeySpace), t->msize, t->fd); // записываем в файл всю таблицу
    fclose(t->fd);
    t->fd = NULL;
    return 1;
}*/

/*int D_Add(Table *t){ //не робит(((
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
    rc = add_el(t, info, k);
    printf("%s: %s\n", errmsgs[rc], info);
    free(info);
    return 1;
}

int D_Del(Table *t){
    int rc, n, k;
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;  
    printf("Enter the element's version: -->");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;
    rc = del_el(t, key, k);
    printf("%s: %s\n", errmsgs[rc], key);
    free(key);
    return 1;
}

int D_Find_all (Table *t){
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0; 	
	int check, count=0, flag=0;
	char *str;
	KeySpace *ks = t->ks;
	for (int i=0; i<t->msize; ++i){
		if (ks[i].busy == 1 && strcmp(ks[i].key, key) == 0){
			flag = 1;
			printf("%s | %d | %d\n", ks[i].key, ks[i].data, ks[i].version);
		}
	}
	if (flag == 0) printf("Table is empty\n");
	free(key);
	return 1;
}

int D_Find(Table *t){ // робит
	int k, n;
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0; 
    printf("Enter the element's version: -->");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;       
    char *str;
    KeySpace *ks = t->ks;
    KeySpace *check = find_element(t, key, k);
    //printf("check %d\n", check);
    if (check == NULL) {
        printf("Item was not found\n");
    } else {
        //printf("%s | %d | %d", ks[check].key, ks[check].data, ks[check].version);
        printf("%s | %d | %d", check->key, check->data, check->version);
    }
    free(key);
    return 1;
}

int D_Show(Table *t){
    int rc;
    rc = print(t);
    printf("%s!\n", errmsgs[rc]);
    return 1;
}

int D_Load(Table *t){
    int rc;
    printf("Enter file name: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* fn = getstr();
    if(fn==NULL) return 0;
    rc = load(t, fn);
    printf("%s\n", errmsgs[rc]);
    free(fn);
    return 1;
}
*/
