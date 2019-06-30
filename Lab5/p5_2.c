#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EmptyTOS -1 //스택 포인터 초기값
#define MinStackSize 10
#define MAZE_SIZE 6

typedef struct StackRecord *Stack; //구조체를 가리키는 포인터 이므로 ->사용!

typedef struct{
	int r;
	int c;
}ElementType;

struct StackRecord {
    int Capacity;
    int TopOfStack;
    ElementType *Array; //스택의 배열을 만들어준다
};


char Maze[MAZE_SIZE][MAZE_SIZE] = { 
	{'1', '1', '1', '1', '1', '1'}, 
	{'e', '0', '1', '0', '0', '1'}, 
	{'1', '0', '0', '0', '1', '1'}, 
	{'1', '0', '1', '0', '1', '1'}, 
	{'1', '0', '1', '0', '0', 'x'}, 
	{'1', '1', '1', '1', '1', '1'},
};

void FatalError( char *msg );
void Error( char *msg );
Stack CreateStack( int MaxElements ); 
void MakeEmpty( Stack S );
int IsEmpty( Stack S );
int IsFull( Stack S );
void Push( ElementType X, Stack S ); 
ElementType Pop( Stack S );
void PushLocation(Stack S, int r, int c);
void printStack(Stack S);

ElementType here={1,0}, entry={1,0};

int main()
{
	int r,c; Stack S; 
	S=CreateStack(100);
	here = entry;

	while ( Maze[here.r][here.c]!='x' ){
		r=here.r; 
		c=here.c;
		Maze[r][c] = '.';
		PushLocation(S, r-1,c); 
		PushLocation(S,r+1,c); 
		PushLocation(S,r,c-1); 
		PushLocation(S,r,c+1);

		printStack(S);
    	if( IsEmpty(S) ){
    		printf("실패\n"); 
    		//return; 
    	}
    	else
       		here = Pop(S);
	} 
	printf("성공\n"); 
	return 0;
}

void MakeEmpty( Stack S ){ //스택을 empty 상태로 만들어준다
	S->TopOfStack = EmptyTOS;

}
Stack CreateStack( int MaxElements ){
	Stack S;
	if(MaxElements < MinStackSize) //만들고자 하는 스택의 사이즈가 최소사이즈보다 작다면
		FatalError("Stack size is too small");
	S = malloc(sizeof(struct StackRecord));

	if(S==NULL) //스택이 잘 만들어졌는지 확인해주는 작업!
		FatalError("Out of space!!!");

	S->Array = malloc(sizeof(ElementType)*MaxElements);
	if(S->Array == NULL)
		FatalError("Out of space!!!");
	S->Capacity = MaxElements;
	MakeEmpty(S);

	return S;
}
int IsEmpty( Stack S ){
	return S->TopOfStack == EmptyTOS;
}
int IsFull( Stack S ){
	return S->TopOfStack == (S->Capacity-1);
}
void FatalError( char *msg ) {
 	printf("%s\n", msg);
	exit(0); 
}
void Error( char *msg ) {
   printf("%s\n", msg);
}
void PushLocation(Stack S, int r, int c){ //위치를 스택에 저장

	ElementType tmp;
	if(r < 0 || c< 0)
		return;
	if(Maze[r][c] != '1' && Maze[r][c] != '.'){
		tmp.r = r;
		tmp.c = c;
		Push(tmp,S);
	}
}
void Push( ElementType X, Stack S ){
	if(IsFull(S))
		Error("Full stack");
	else
		S->Array[++S->TopOfStack] = X;
}
ElementType Pop( Stack S ){

	ElementType tmp = {1,0};
	if(IsEmpty(S)){
		Error("Empty stack");
		return tmp;
	}
	else
		return S->Array[S->TopOfStack--];
}

void printStack(Stack S){
	int i;
	for(i = 2+S->TopOfStack;i>S->TopOfStack;i--)
		printf("|     |\n");
	for(i = S->TopOfStack;i>=0;i--)
		printf("|(%01d,%01d)|\n",S->Array[i].r,S->Array[i].c);
	printf("----------\n");
}
