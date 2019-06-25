#include <stdio.h>
#include <stdlib.h>

int select();
int add();
int sub();
int mul();
int divide();

int main(){

	int n = -1; //초기에 아무 숫자가 설정되지 않도록 하기 위해서 -1 대입
	int a,b;
	int (*fp)(int, int);

	while(1){

		n = select();
		if(n==4)
			break;

		printf("Input 2 operand : ");
		scanf("%d%d",&a, &b); //%d %d로 하면 spacebar를 두번 눌러야 한다

		switch(n){
			case 0:
				fp = add;
				break;
			case 1:
				fp = sub;
				break;
			case 2:
				fp = mul;
				break;
			case 3:
				fp = divide;
				break;				
			default:
				break;
		}

		printf("Result = ");
		printf("%d\n",fp(a,b));

	}

}

int add(int a, int b){
	return a+b;
}

int sub(int a, int b){
	return a-b;
}

int mul(int a, int b){
	return a*b;
}

int divide(int a, int b){
	return a/b;
}

int select(){		

	int t;

	printf("--------------------\n");
	printf("0. add\n");
	printf("1. sub\n");
	printf("2. mul\n");
	printf("3. div\n");
	printf("4. exit\n");
	printf("--------------------\n");

	while(1){
		printf("Select Operation : ");

		scanf("%d",&t);
		if(t<0 || t>4){
			printf("you choose wrong number!\n");
			continue;
		}
		else
			break;
	}

	return t;

}
