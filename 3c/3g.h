#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct KeySpace {
	int busy;
    unsigned int data;
	char *key;
    int version;
}KeySpace;

typedef struct Table{
    KeySpace *ks;
    int msize;
    int csize;
    FILE *fd;
    char *fname;
}Table;

int add_el(Table* t, char *key, unsigned int data);
void destructor(Table* t);
char *getstr();
int create_table(Table* t);
int hash_func(char *key, Table *t);
int find_key_ver (Table *t, char* key, int version);
int del_el(Table *t, char *key, int version);
int print(Table* t);
char *fgetstr(FILE* file);
int load(Table* t, char* fn);
int load2(Table* t, char* fn);
int save(Table *t);
KeySpace *find_element (Table *t, char* key, int version);
