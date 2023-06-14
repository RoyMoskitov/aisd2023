#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct KeySpace {
        char *key;
        char *par;
        unsigned int *info;
} KeySpace;

typedef struct Table{
        KeySpace *ks;
        int msize;
        int csize;
} Table;

Table *tab_init ();
void dia_add (Table *tab);
int tab_add (Table * tab, char *key, unsigned int info, char *par, int new);
int tab_delete(Table *tab, char *key);
void destructor (Table *tab);
KeySpace search (Table *tab, char *key);
void tab_print(Table *tab);
int tab_import(Table *tab, char *file1);
char *getstr();
void scan(int *value, Table *tab);
void dia_delete (Table *tab);
void dia_print(Table *tab);
void dia_search(Table *tab);
void dia_import (Table *tab);
void dia_new (Table *tab);
int new_tab(Table *tab, char *par);
