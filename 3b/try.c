
#include "main.h"

int dialog(const char *choice[], int N){ //робит
    char *errchoice = "";
    int rc;
    int i, n;
    do{
        puts(errchoice);
        errchoice = "You are wrong. Repeate, please!";
        for(i = 0; i < N; ++i) puts(choice[i]);
        printf("Make your choice: --> ");
        n = scanf("%d",&rc);
        if(n <= 0) rc = 0;
    } while(rc < 0 || rc >= N);
    return rc;
}

int main(){
    const char* choice[]={"0- Exit", "1- Add element", "2- Find element",
                          "3- Delete element", "4- Show table", 
                          "5- Add elements from a text file", "6- New table"};
    const int N=sizeof(choice)/sizeof(choice[0]);
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Del, D_Show, D_Load, D_New};
    Table t = {NULL, 0, 0, NULL};
    int rc;
    if (D_Load2(&t) == 0)return 1;
    while(rc = dialog(choice, N))if(!fptr[rc](&t))break;
	save(&t); // Выгружаем таблицу, закрываем файл данных
    printf("That's all. Bye!\n");
    destructor(&t); 
    return 0;
}
