#include <stdio.h>
#include <stdlib.h>

typedef struct{
        int size;
        int *data;
} line;
typedef struct{
        line *data;
        int size;
} matrix;

void proc(matrix *m);
void destructor(matrix *m);
void print_m(matrix *m);
