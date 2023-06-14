
#include "prog1.h"
#define possibility 25


int main() {
	node *main=malloc(sizeof(node));
	double sum=0, taylor=0, p, res;
	int flag=0, qur_angle, k=0, j=0, i, i1, summa=0,  n=0, f=0, r_members, skip, angle, memb, sl_empty=0;
	srand(time(NULL));
	Queue *q;
	while (1){
		printf("Enter the number of side nodes: ");
		scan(&(main->side_nodes), main);
		printf("Enter the angle range: ");
		scan1(&(main->angle_min), main);
		scan1(&(main->angle_max), main);
		printf("Enter the number of terms in decomposion range: ");
		scan(&(main->mn_min), main);
		scan(&(main->mn_max), main);
		if (main->angle_min > main->angle_max) swap(&(main->angle_max), &(main->angle_min));
		if (main->mn_min > main->mn_max) swap(&(main->mn_max), &(main->mn_min));
		qur_angle=main->angle_min;
		q=queue_new();
		Queue ** slave = malloc((main->side_nodes)*sizeof(Queue*));
		for (int i=0; i<main->side_nodes; ++i){
			slave[i] = queue_new();
		}
		
		for (int i=0; i<(main->angle_max-main->angle_min+1); ++i){
			skip = rand() % 100;
			if (possibility <= skip) printf("Main queue skip\n");
			r_members=(rand()%(-main->mn_min+main->mn_max+1))+(main->mn_min);
			//printf("members %d\n", r_members);
			if ((skip < possibility) && (f == 0)) {
			
				if (queue_put(q, qur_angle, r_members) == 1) {
					printf("Main queue overflow\n");	
				}
			}
			//printf("Check\n");
			for (k=0; k<main->side_nodes; ++k) {
				skip = rand() % 100;
				if (possibility <= skip) printf("Side queue skip\n");
				//printf("skip 2: %d\n", skip);
				if (skip < possibility) {
					if (queue_get(q, &(angle), &(memb)) == 1) {
						//printf("SSSSkip\n");
						break;
					} else {
						taylor = angle;
						taylor *= 0.017453;
						p = taylor;
						sum=0;
						i1=1;
						while(i1<=memb){
							sum += taylor;
							taylor *= -1.0 * p * p / ((2*i1)*(2*i1+1));
							i1 += 1;
						}
						//printf("%lf\n", sum);
						if (queue_put_res(slave[k], angle, sum) == 1) {
							printf("Queue to side node № %d overflow\n", j+1);
						}
					}
				}
			}
			for (int t=0; t<main->side_nodes; ++t) {
				skip = rand() % 100;
				if (possibility <= skip) printf("Main queue skip\n");
				//printf("skip 3: %d\n", skip);
				if (skip < possibility) {
					if (queue_get_res(slave[t], &(angle), &(res)) == 0){
						printf("Node №%d: %d' - %lf\n", t+1, angle, res);
					} 
				}
			}
			f=0;
			sl_empty=0;
			for (int t=0; t<main->side_nodes; ++t){
				if (queue_empty(slave[t]) == 1) {
					sl_empty=1;
					break;
				}
			}
			if (i+1==main->side_nodes && (queue_empty(q) == 1 || sl_empty == 1)){
				i--;
				f=1;
			}
			qur_angle++;
		}
		n=j=f=sl_empty=0;
		for (int i=0; i<main->side_nodes; ++i){
			queue_delete(slave[i]);
		}
		queue_delete(q);
		free(slave);
	}
	free(main);
    return 0;
}

void scan (int *value, node *main){
	int check = -1;
	while ((check = scanf("%d", value)) != 1 || (*value)<=0) {
		if (check == EOF){
			free(main);
			exit(1);
		}
		printf("Try again!\n");
		if (check <= 0) scanf("%*s");
	}
}

void scan1 (int *value, node *main){
	int check = -1;
	while ((check = scanf("%d", value)) != 1 || (*value)<=0 || (*value>90)) {
		if (check == EOF){
			free(main);
			exit(1);
		}
		printf("Try again!\n");
		if (check <= 0) scanf("%*s");
	}
}

void swap (int *first, int *second) {
	int temp;
	temp=(*first);
	*first=(*second);
	*second=temp;
}

void destructor (node *main, side *arr){
	free(main->angles);
	free(main->res);
	free(arr);
}

void mistake (int *j, int *i, node *main, side *arr, Queue *q){
	printf("Program ran out of side nodes(((((((((\n");
	destructor(main, arr);
	free(main);
	exit (1);
}





