#include <stdio.h>
#include <stdlib.h>

int main(){

	char arr[30];

	printf("enter your name:\n");
	//gets, fgets 사용방법 알아두기
	fgets(arr,sizeof(arr),stdin);
	printf("your name is %s\n",arr);

	return 0;
}
