#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct KeySpace {
	int busy;
    unsigned int data;// ненулевой ключ элемента
	int key;
    int version;
}KeySpace;

typedef struct Table{
    KeySpace *ks;
    int msize;// размер области пространства ключей
    int csize;// количество элементов в области пространства ключей
    FILE *fd; // дискриптор файла, чтобы выполнять операции с файлом данных
    char *fname;
}Table;

int add_el1(Table* t, int key, unsigned int data);
void destructor1(Table* t);
char *getstr();
int create_table(Table* t);
int hash_func(int key, Table *t);
int find_key_ver (Table *t, int key);
int del_el1(Table *t, int key, int version);
int print1(Table* t);
char *fgetstr(FILE* file);
int load1(Table* t, char* fn);
int load2(Table* t, char* fn);
int save(Table *t);
KeySpace *find_element1 (Table *t, int key, int version);
