
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int main(){
	int check;
	Tree *tree = calloc(1, sizeof(Tree));
	tree->ks = NULL;
	while (1){
		printf("0 - Quit\n1 - Add element\n2 - Delete element\n3 - Print tree\n4 - Find element\n5 - Find maximum\n6 - Load elemnts\n7 - Make png\n8 - Print tree as a tree\n9 - Timing\n");
		//printf("0 - Quit\n1 - Find element\n2 - Load elemnts\n3 - Show\n");
		scanf("%d", &check);
		switch(check) {
			case 0: 
				break;
			case 1:
				if (D_Add(tree)==0) check = 0; 
				break;
			case 2:
				if (D_Del(tree)==0) check = 0;
				break;	
			case 3:
				if (D_Show(tree)==0) check = 0;
				break;
			case 4:
				if (D_Find(tree)==0) check = 0;
				break;
			case 5:
				if (D_Max(tree)==0) check = 0;
				break;
			case 6:
				if (D_Load(tree)==0) check = 0;
				break;
			case 7:
				if (D_Png(tree)==0) check = 0;
				break;
			case 8:
				if (D_print_tree(tree)==0) check = 0;
				break;
			case 9:
				if (D_Timing(tree)==0) check = 0;
				break;				
			default:
				printf("Repeat please\n");
				break;
		}
		if (check == 0) break;
	}
	destructor(tree);
	return 0;
}
