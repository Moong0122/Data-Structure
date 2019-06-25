#include <stdio.h>
#include <stdlib.h>

void swap(int *n, int *m);

int main(){
	int A,B;
	printf("enter 2 integers\n");
	scanf("%d",&A);
	scanf("%d",&B);

	printf("you entered\n");
	printf("%d, %d\n",A,B);

	swap(&A,&B);

	return 0;
}

void swap(int *n, int *m){
    
	int tmp;
	tmp = *n;
	*n = *m;
	*m = tmp;

	printf("after swapping\n");
	printf("%d, %d\n",*n,*m);
}
