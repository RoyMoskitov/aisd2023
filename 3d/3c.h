#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct KeySpace {
	int busy;
    unsigned int data; // ненулевой ключ элемента
    int len; // длина информации
    int offset; // смещение в файле (по отношение к началу файла)
    int version;
}KeySpace;

typedef struct Table{
    KeySpace *ks;
    int msize; // размер области пространства ключей
    int csize; // количество элементов в области пространства ключей
    FILE *fd; // дискриптор файла, чтобы выполнять операции с файлом данных
    char *fname;
}Table;

// int D_Add(Table *);
// int D_Find(Table *);
// int D_Del(Table *);
// int D_Show(Table *);
// int D_Load(Table *);
// int D_New(Table *);
// int D_Find_all (Table *t);
// int D_Load2(Table* t);
int add_el(Table* t, char *key, unsigned int data);
void destructor(Table* t);
char *getstr();
int create_table(Table* t, char* fn);
int hash_func(char *key, Table *t);
int find_key_ver (Table *t, char* key, int version);
int del_el(Table *t, char *key, int version);
int print(Table* t);
char *fgetstr(FILE* file);
int load(Table* t, char* fn);
int load2(Table* t, char* fn); 
int save(Table *t);
KeySpace *find_element(Table *t, char* key, int version);
