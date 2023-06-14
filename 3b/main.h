#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct KeySpace {
    unsigned int data;// ненулевой ключ элемента
    int len1; // длина информации
    int offset1; // смещение в файле (по отношение к началу файла)
    int len2;
    int offset2;
}KeySpace;

typedef struct Table{
    KeySpace *ks;
    int msize;// размер области пространства ключей
    int csize;// количество элементов в области пространства ключей
    FILE *fd; // дискриптор файла, чтобы выполнять операции с файлом данных
    char *fname;
}Table;

int D_Add(Table *);
int D_Find(Table *);
int D_Del(Table *);
int D_Show(Table *);
int D_Load(Table *);
int D_Load2(Table *);
int D_New(Table *);
//const char *errmsgs[] = {"Successfully", "Duplicate key", "Table overflow", "There isn't parent key", "Key not found", "Table is empty", "Error opening file", "File format incorrect"};
void destructor(Table* t);
char *getstr();
int create_table(Table* t, char* fn);
int find_el(char *key, Table* t);
int add_el(Table* t, char *key, char *par, unsigned int data);
int new_tab (Table *t, char *par);
int print(Table* t);
char *fgetstr(FILE* file);
int load(Table* t, char* fn);
int load2(Table* t, char* fn);
int save(Table *t);
