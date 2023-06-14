#include "main.h"

int main() {
	Table *tab = tab_init();
	int check=-1, choice, f=0;
	while (1){
		printf("0.Quit\n1.Add element\n2.Delete elemet\n3.Find element\n4.Print tab\n5.Import data from file\n6.Find all elements with the same parent key\n");
		scan(&choice, tab);
		switch(choice) {
			case 0: break;
			case 1: 
				dia_add(tab);
				break;
			case 2: 
				dia_delete(tab);
				break;
			case 3:
				dia_search(tab);
				break;
			case 4: 
				dia_print(tab);
				break;
			case 5: 
				dia_import(tab);
				break;
			case 6: 
				dia_new(tab);
				break;
			default: printf("Wrong button\n");
		}
		if (choice == 0) break;
	}
	destructor(tab);
	return 0;
}

void scan (int *value, Table *tab){
        int check = -1;
        while ((check = scanf("%u", value)) != 1 ) {
                if (check == EOF){
                        destructor(tab);
                        exit (1);
                }
                printf("Try again!\n");
                if (check <= 0) scanf("%*s");
        }
}

void dia_new (Table *tab){
	printf("Enter the parent's key:\n");
	char *str = readline(">> ");
	new_tab(tab, str);
	free(str);
}

int new_tab(Table *tab, char *par) {
	Table *new = tab_init();
	//printf("%d\n", new->msize);
	//printf("%s\n", par);
	for (int i=0; i<tab->csize; ++i){
		//printf("%s\n", tab->ks[i].par);
		if (strcmp(tab->ks[i].par, par) == 0){
			//printf("dddddd");
			tab_add(new, tab->ks[i].key, *(tab->ks[i].info), tab->ks[i].par, 0);
		}
	}
	dia_print(new);
	destructor(new);
	return 0;
}

void dia_search(Table *tab){
	printf("Enter the element's key:\n");
	char *str = readline(">> ");
	KeySpace check;
	check = search(tab, str);
	if	(check.key == NULL){
		printf("No such element in the table\n");
	} else {
		printf("This element: %s|%s|%d\n", check.key, check.par, check.info);
	}
	free(str);
}

void dia_add (Table *tab) {
	printf("Enter the element's key:\n");
	int data, len=0, check;
	char *str = readline(">> ");
	printf("Enter the element parent's key:\n");
	char *par = readline(">> ");
	printf("Enter the element's data:\n");
	//scanf("%d", &data);
	scan(&data, tab);
	check = tab_add(tab, str, data, par, 1);
	if (check == 2){
		printf("Not enough space\n");
	} else if (check == 1){
		printf("This key already exists\n");
	} else if (check == 3){
		printf("Key, you wrote as a parent one, doesn't exist in table\n");
	} else {
		printf("Success\n");
	}
	free(str);
	free(par);
}

void dia_delete (Table *tab){
	printf("Enter the element's key:\n");
	char *str = readline(">> ");
	int check;
	check = tab_delete(tab, str);
	if (check == 1){
		printf("Element with this key doesn't exist\n");
	} else {
		printf("Success\n");
	}
	free(str);
}

void dia_print(Table *tab){
	printf("Your tab:\n");
	tab_print(tab);	
}

void dia_import (Table *tab){
	printf("Enter the name of file:\n");
	char *str = readline(">> ");
	int check;
	check = tab_import(tab, str);
	if (check == 1) {
		printf("Error opening file.\n");
	} else if (check == 2) {
		printf("File format incorrect.\n");
	} else if (check == 3) {
		printf("Error reading file.\n");
	} else if (check == 4) {
		printf("Not enough space in tab\n");
	} else {
		printf("Success\n");
	}
	free(str);
}

int tab_import(Table *tab, char *file1) {
  FILE *file;
  int records=0, data;
  char *key = malloc(99*sizeof(char));
  char *par = malloc(99*sizeof(char));
  file = fopen(file1, "r");
  if (file == NULL) {
  	free(key);
  	free(par);
  	fclose(file);
    return 1;
  }
  int read = 0; 
  while (read = fscanf(file, "%[^,],%[^,],%d\n", key, par, &(data)) != EOF) {
    if (read != 1 && !feof(file)) {
		return 2;
    }
    if (ferror(file)) {
    	return 3;
    }
    if (tab_add(tab, key, data, par, 1) != 0) {
        return 4;
    }
  }
  fclose(file);
  free(key);
  free(par);
  return 0;
}

void tab_print(Table *tab){
	for (int i=0; i<tab->csize; ++i){
		printf("%s - %s - %d\n", tab->ks[i].key, tab->ks[i].par, *(tab->ks[i].info));
	}
}

KeySpace search (Table *tab, char *key){
	for (int i=0; i<tab->csize; ++i){
		if (strcmp(tab->ks[i].key, key) == 0){
			return tab->ks[i];
		}
	}
	unsigned int i=1;
	KeySpace g = {NULL, NULL, &i};
	return g;
}

Table *tab_init() {
	Table *tab = malloc(sizeof(Table));
	printf("Print the max size of key space:");
	scan(&(tab->msize), tab);
	tab->ks = (KeySpace*) malloc ((tab->msize)*sizeof(KeySpace));
	for (int i=0; i<tab->msize; ++i){
		tab->ks[i].info = calloc(1, sizeof(unsigned int));
		tab->ks[i].key = calloc(1, sizeof(char));
		tab->ks[i].key[0]='\0';
		tab->ks[i].par = calloc(1, sizeof(char));
		tab->ks[i].par[0]='\0';
	}
	tab->csize=0;
	return tab;
}

int tab_add(Table * tab, char *key, unsigned int info, char *par, int new) {
	if (tab->csize == tab->msize) {
		return 2;
	}
	int flag=0;
	for (int i=0; i<tab->csize; ++i) {
		if (strcmp(tab->ks[i].key, par) == 0) {
			flag = 1;
		}
	}
	if (flag == 0 && strcmp("0", par) != 0 && new != 0){
		return 3;
	}
	//printf("eeeeeeeee\n");
	for (int i=0; i<tab->csize; ++i){
		if (strcmp(tab->ks[i].key, key) == 0) {
			return 1;
		}
	}
	tab->ks[tab->csize].key = realloc(tab->ks[tab->csize].key, (strlen(key)+1)*sizeof(char));
	strcat(tab->ks[tab->csize].key, key);
	tab->ks[tab->csize].par = realloc(tab->ks[tab->csize].par, (strlen(par)+1)*sizeof(char));
	strcat(tab->ks[tab->csize].par, par);
	*(tab->ks[tab->csize].info) = info;	
	(tab->csize)++;
	return 0;
}

int tab_delete(Table *tab, char *key) {
	char *check;
	for (int i=0; i<tab->csize; ++i){
		if (strcmp(tab->ks[i].key, key) == 0) {
			check = malloc ((strlen(tab->ks[i].key)+1)*sizeof(char));
			check[0]='\0';
			strcat(check, tab->ks[i].key);
			if (i==tab->csize-1){
				tab->ks[(tab->csize)-1].key = realloc (tab->ks[(tab->csize)-1].key, sizeof(char));
				tab->ks[(tab->csize)-1].key[0]='\0';
				tab->ks[(tab->csize)-1].par = realloc (tab->ks[(tab->csize)-1].par, sizeof(char));
				tab->ks[(tab->csize)-1].par[0]='\0';
				(tab->csize)--;
			} else {
				free(tab->ks[i].key);
				free(tab->ks[i].par);
				tab->ks[i].par = malloc((strlen(tab->ks[(tab->csize)-1].par)+1)*sizeof(char));
				tab->ks[i].par[0]='\0';
				tab->ks[i].key = malloc((strlen(tab->ks[(tab->csize)-1].key)+1)*sizeof(char));
				tab->ks[i].key[0]='\0';
				strcat(tab->ks[i].key, tab->ks[(tab->csize)-1].key);
				strcat(tab->ks[i].par, tab->ks[(tab->csize)-1].par);
				*(tab->ks[i].info) = *(tab->ks[(tab->csize)-1].info);
				tab->ks[(tab->csize)-1].key = realloc (tab->ks[(tab->csize)-1].key, sizeof(char));
				tab->ks[(tab->csize)-1].par = realloc (tab->ks[(tab->csize)-1].par, sizeof(char));
				tab->ks[(tab->csize)-1].key[0]='\0';
				tab->ks[(tab->csize)-1].par[0]='\0';
				(tab->csize)--;
			}
			for (int j=0; j<tab->csize; ++j){
				if (strcmp(check, tab->ks[j].par) == 0){
					tab->ks[j].par = realloc (tab->ks[j].par, 2*sizeof(char));
					tab->ks[j].par[0] = '\0';
					strcat(tab->ks[j].par, "0");
				}
			}
			free(check);
			return 0;
		}
	}
	return 1;
}

void destructor (Table *tab) {
	for (int i=0; i<tab->msize; ++i){
		free(tab->ks[i].info);
		free(tab->ks[i].key);
		free(tab->ks[i].par);
	}
	free(tab->ks);
	free(tab);
}
