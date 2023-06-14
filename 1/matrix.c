#include "matrix.h"

void proc(matrix *m){
	int *b = malloc((m->size)*sizeof(int));
	int count=0, i=0;
	line *item=m->data;
	while (count<(m->size)){
		b[count]=0;
		while (i<(item[count].size)){
			if (item[count].data[i] % 2 == 0){
				b[count] += item[count].data[i];
			} else {
				b[count] -= item[count].data[i];
			}
			i++;
		}
		i=0;
		count++;
	}
	printf("Your new vector: ");
	for (int j=0; j<(m->size); ++j) printf("%d ", b[j]);
	printf("\n");
	free(b);
}

void destructor(matrix *m){
	line * item=m->data;
	int i=0;
	while (i<(m->size)){
		free(item[i].data);
		++i;
	}
	free(item);
	free(m);
}

void print_m(matrix *m) {
line *item=m->data;
        int p=0, n=0;
        printf("Your matrix:\n");
        while(p < m->size){
                while (n<item[p].size){
                        printf("%10d ", item[p].data[n]);
                        ++n;
                }
                n=0;
                printf("\n");
                ++p;
        }
}

int main(){
	//char check;
	int width, k=0, hight=3, i=0, j=0 , qur=-1, values=-1, count=0, check;
	printf("Enter matrix hight: ");
	while(check = scanf("%d", &hight)!= 1 || hight<=0){
		printf("Try again!\n");
		if (check != 1) scanf("%*s");
	}
	line *l = malloc(hight*sizeof(line));
	matrix *m = malloc(sizeof(matrix));
	m->data=l;
	m->size=hight;
	while(k<hight){
		printf("Type the number of elements in line %d: ", k+1);
		while(check = scanf("%d", &qur)!= 1 || qur<=0){
				printf("Try again!\n");
				if (check == 1 && qur <= qur) scanf("%*s");
		}
		l[k].data=malloc(sizeof(int));
		l[k].size=qur;
		printf("Type them: ");
		while (qur>0){
			while(check = scanf("%d", &values)!= 1){
					printf("Try again!\n");
					if (check != 1) scanf("%*s");
			}
			l[k].data = realloc(l[k].data, (count+1)*sizeof(int));
			l[k].data[count]=values;
			count++;
			qur--;
		}
		k++;
		qur=-1;
		count=0;
	}
	print_m(m);
	proc(m);
	destructor(m);
}
