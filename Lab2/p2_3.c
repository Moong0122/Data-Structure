#include <stdio.h>
#include <stdlib.h>

int main(){

	int n;
	printf("input number: ");
	scanf("%d",&n);

	char *person[n];

	printf("enter %d names:\n",n);
	
	for(int i=0;i<n;i++){
		person[i] = (char*)malloc(31);
		scanf("%s", person[i]);
	}

	printf("the names you entered:\n");
	for(int i=0;i<n;i++){
		printf("%s\n", person[i]);
	}

	return 0;
}
