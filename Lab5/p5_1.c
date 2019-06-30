#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1
#define MinStackSize 1

typedef struct StackRecord *Stack;
typedef char ElementType;

struct StackRecord {
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

Stack CreateStack( int MaxElements ); 
void MakeEmpty( Stack S );
int IsEmpty( Stack S );
int IsFull( Stack S );
void  Push( ElementType X, Stack S );
ElementType  Pop( Stack S );
void DeleteStack(Stack S);
void FatalError( char *msg );
void Error( char *msg );


int main(int argc, char* argv[]){

    FILE* input ;
    Stack S;     
    char input_str[101];
    int max,i=0,a,b,result;

    if (argc==1)
		input =fopen("input.txt","r"); 
	else
        input  =fopen(argv[1],"r");

	fgets(input_str, 101,input); 
	max = strlen(input_str); 

	printf("Pushed numbers :");

	S = CreateStack(max);

	while(input_str[i]!='#'){
 	 // do operation
		switch(input_str[i]){
			case '+':
				a = Pop(S);
				b = Pop(S);
				result = b+a;
				Push(result,S);
				break;
			case '-':
				a = Pop(S);
				b = Pop(S);
				result = b-a;
				Push(result,S);

				break;
			case '*':
				a = Pop(S);
				b = Pop(S);
				result = b*a;
				Push(result,S);
				break;
			case '/':
				a = Pop(S);
				b = Pop(S);
				result = b/a;
				Push(result,S);
				break;
			case '%':
				a = Pop(S);
				b = Pop(S);
				result = b%a;
				Push(result,S);
				break;
			default:
				Push(input_str[i]-'0',S);
				// 이 배열은 char 형이라서 숫자를 받기 위해서 '0'을 뺴준다
				break;	
		}
		i++;
	}
	printf("\nevaluation result : %d\n", result);
	fclose(input);
	DeleteStack(S);
	return 0;

}

void FatalError( char *msg ) {
 	printf("%s\n", msg);
	exit(0); 
}

void Error( char *msg ) {
   printf("%s\n", msg);
}
Stack CreateStack( int MaxElements ){
	Stack S;
	if(MaxElements < MinStackSize)
		FatalError("Stack size is too small");
	S = malloc(sizeof(struct StackRecord));
	if(S==NULL)
		FatalError("Out of space");

	S->Array = malloc(MaxElements*sizeof(ElementType));

	if(S->Array == NULL)
		FatalError("Out of space!!!");
	S->Capacity = MaxElements;
	MakeEmpty(S);
	return S;

}
void MakeEmpty( Stack S ){
	S->TopOfStack = EmptyTOS;

}
int IsEmpty( Stack S ){
	return S->TopOfStack == EmptyTOS;
}
int IsFull( Stack S ){
	return S->TopOfStack == (S->Capacity-1);

}
void  Push( ElementType X, Stack S ){
	if(IsFull(S))
		Error("Full stack");
	else
		S->Array[++S->TopOfStack] = X;
		printf("%d ",X);

}
ElementType Pop( Stack S ){
	if(IsEmpty(S)){
		Error("Empty stack");
		return -1;
	}
	else
		return S->Array[S->TopOfStack--];
}
void DeleteStack(Stack S){
	free(S->Array);
	free(S);
}
