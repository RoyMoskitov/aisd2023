
#include "main.h"
const char *errmsgs[] = {"Successfully", "Duplicate key", "Table overflow", "There isn't parent key", "Key not found", "Table is empty", "Error opening file", "File format incorrect"};

void destructor(Table* t){
	KeySpace* ks=t->ks;
	free(t->fname);
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

int create_table(Table* t, char* fn){
    int n;
    printf("%s\n",fn);
    do{
        printf("Enter the maximum size of the table: --> "); 
        n=scanf("%d",&(t->msize));
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
    t->fd = fopen(fn, "w+b");
    if (t->fd == NULL) {
        t->ks=NULL;
        printf("stok\n");
        fclose(t->fd);
        return 0;
    }
    t->ks=(KeySpace*)calloc((t->msize), sizeof(KeySpace)); 
    fwrite(&t->msize, sizeof(int), 1, t->fd);
    fwrite(&t->csize, sizeof(int), 1, t->fd);
    fwrite(t->ks, sizeof(KeySpace), t->msize, t->fd);
    return 1;
}

int find_el(char *key, Table* t){ 
    KeySpace* ks=t->ks;
    char *str;
    for(int i=0; i<(t->csize); i++){
        fseek(t->fd, ks[i].offset1, SEEK_SET);
        str = malloc((ks[i].len1)*sizeof(char));
        fread(str, sizeof(char), ks[i].len1, t->fd);
        if(strcmp(str, key) == 0) {
        	free(str);
        	return i;
        }
        free(str);
   	}
    return -1;
}

int add_el(Table* t, char *key, char *par, unsigned int data){ 
    KeySpace* k=t->ks;
    int r;
    char zero[2] = "0";
    if(find_el(key,t)>-1) return 1;
    if(find_el(par,t)<=-1 && strcmp(zero, par) != 0) return 3;
    if(t->csize==t->msize) return 2;
    k[t->csize].data = data;
    k[t->csize].len1 = strlen(key)+1;
    r = fseek(t->fd,0,SEEK_END);
    //printf("%d\n", r);
    k[t->csize].offset1 = ftell(t->fd);
    fwrite(key, sizeof(char), k[t->csize].len1, t->fd);
    k[t->csize].len2 = strlen(par)+1;
    k[t->csize].offset2 = ftell(t->fd);
    fwrite(par, sizeof(char), k[t->csize].len2, t->fd);
    (t->csize)++;
    return 0;
}

int new_tab (Table *t, char *par) {
    KeySpace *ks = t->ks;
    int data;
    char *str, *str1;
    Table new = {NULL, 0, 0, NULL};
    printf("Your new tab:\n");
    for (int i=0; i<t->csize; ++i) {
        fseek(t->fd, ks[i].offset2, SEEK_SET);
        str1 = malloc((ks[i].len2) * sizeof(char));
        fread(str1, sizeof(char), ks[i].len2, t->fd);
        if (strcmp(str1,par)!=0) {
        	free(str1);
        	continue;
        }
        fseek(t->fd, ks[i].offset1, SEEK_SET);
        str = malloc((ks[i].len1) * sizeof(char));
        fread(str, sizeof(char), ks[i].len1, t->fd);        
        printf("%s - %s - %u\n", str, str1, ks[i].data);
        free(str);
        free(str1);
    }
    return 0;
}

int del_el(Table *t, char *key){
    int check = find_el(key, t);
    int j=0, qur = t->csize;
    KeySpace *ks = t->ks;
    char *str, *str1;
    char zero[2] = "0";
    if ( check == -1) return 1;
    FILE *new = fopen("new.bin", "w+b");
    FILE *old = t->fd;
    t->fd = new;
    (t->csize) = 0;
    fwrite(&(t->msize), sizeof(int), 1, t->fd);
    fwrite(&(t->msize), sizeof(int), 1, t->fd);
    fwrite(t->ks, sizeof(KeySpace), t->msize, t->fd);
    //printf("%d\n", check);
    for (int i=0; i<qur; ++i) {
        if (check == i) {
            continue;
        }
        fseek(old, ks[i].offset1, SEEK_SET);
        str = malloc((ks[i].len1)*sizeof(char));
        fread(str, sizeof(char), ks[i].len1, old);
        fseek(old, ks[i].offset2, SEEK_SET);
        str1 = malloc((ks[i].len2)*sizeof(char));
        fread(str1, sizeof(char), ks[i].len2, old);
        if (strcmp(str1, key) == 0) {
        	str1 = realloc(str1, 2*sizeof(char));
        	str1[0] = '0';
        	str1[1] = '\0';
        }
        printf("%s - %s - %d\n", str, str1, ks[i].data);
        add_el(t, str, str1, ks[i].data);
        free(str);
        free(str1);    
    }
    rename ("new.bin", t->fname);
    fclose(old);
    return 0;
}

int print(Table* t){
    KeySpace* ks=t->ks;
    char *str, *str1;
    if(t->csize==0)return 5;
    for(int i=0; i<(t->csize); i++){
    	str = malloc(ks[i].len1 * sizeof(char));
    	str1 = malloc(ks[i].len2 * sizeof(char));
    	fseek(t->fd, ks[i].offset1, SEEK_SET);
    	fread(str, sizeof(char), ks[i].len1, t->fd);
    	fseek(t->fd, ks[i].offset2, SEEK_SET);
    	fread(str1, sizeof(char), ks[i].len2, t->fd);
    	printf("%d | %s | %s\n", ks[i].data, str, str1);
    	free(str);
    	free(str1);
    }
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
    char* tinf, *key, *par;
    KeySpace* ks=t->ks;
    FILE *file;
    file = fopen(fn, "r");
    if (file == NULL) return 6;
    int read, count= t->csize;
    do {
	    if(count==t->msize){
	        fclose(file);
	        return 2;
	    }
	    key=fgetstr(file);
	    par=fgetstr(file);
	    read = fscanf(file,"%d\n",&data);
	    if(key==NULL || par==NULL) return 7;
	    read += 2;
	    if (read == 3){
	        rs=add_el(t,key,par,data);
	        free(key);
	        free(par);
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

int load2(Table* t, char* fn){
    t->fd=fopen(fn, "r+b");
    if (t->fd == NULL) return 0;
    fread(&(t->msize), sizeof(int), 1, t->fd);
    printf("%d\n", t->msize);
    t->ks=(KeySpace*)malloc(t->msize*sizeof(KeySpace)); 
    fread(&t->csize, sizeof(int), 1, t->fd);
    fread(t->ks, sizeof(KeySpace), t->csize, t->fd);
    return 1;
}

int save(Table *t){
    fseek(t->fd, sizeof(int), SEEK_SET); 
    fwrite(&t->csize, sizeof(int), 1, t->fd); 
    fwrite(t->ks, sizeof(KeySpace), t->csize, t->fd); 
    fclose(t->fd);
    t->fd = NULL;
    return 1;
}

int D_Add(Table *t){ 
    int rc, n, k, rk;
    char *info, *info2;
    printf("Enter element's data: -->");
    n = scanf("%d",&k);
    if(n <= 0 || k<=0) return 0;
    printf("Enter parent's key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    info2 = getstr();
    if (info2 == NULL) return 0;
    printf("Enter key:\n");
    //scanf("%*[^\n]");
    //scanf("%*c");
    info = getstr();
    if (info == NULL) return 0;
    rc = add_el(t, info, info2, k);
    printf("%s: %s, %s\n", errmsgs[rc], info, info2);
    free(info);
    free(info2);
    return 1;
}

int D_New(Table *t){
    int rc;
    printf("Enter parent key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;  
    printf("Your tab:\n");
    rc = new_tab(t, key);
    printf("%s!\n", errmsgs[rc]);
    free(key);	
	return 1;
}

int D_Del(Table *t){
    int rc, n;
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;  
    rc = del_el(t, key);
    printf("%s: %s\n", errmsgs[rc], key);
    free(key);
    return 1;
}

int D_Find(Table *t){ 
    printf("Enter key: -->");
    scanf("%*[^\n]");
    scanf("%*c");
    char* key = getstr();
    if(key==NULL) return 0;    
    char *str, *str1;
    KeySpace *ks = t->ks;
    int check = find_el(key, t);
    if (check == -1) {
        printf("Item was not found\n");
    } else {
        str = malloc((ks[check].len1) * sizeof(char));
        str1 = malloc((ks[check].len2) * sizeof(char));
    	fseek(t->fd, ks[check].offset1, SEEK_SET);
    	fread(str, sizeof(char), ks[check].len1, t->fd);
    	fread(str1, sizeof(char), ks[check].len2, t->fd);
        printf("%s - %s - %d", str, str1, ks[check].data);
        free(str);
        free(str1);
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

int D_Load2(Table* t){ 
    int msize;
    printf("Enter file name: --> ");
    t->fname = getstr();
    if(t->fname == NULL) return 0;
    if (load2(t, t->fname) == 0){ 
        create_table(t, t->fname); 
    }
    //free(fn);
    return 1;
}
