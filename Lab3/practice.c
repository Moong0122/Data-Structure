#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

List MakeEmpty(List H);
int IsEmpty(List L);
void Insert( ElementType X, List L, Position P );
void PrintList(List L);

struct Node
{
    ElementType Element;
    Position Next;
};

int main(int argc, char *argv[]){
	Position header = NULL;
	header = MakeEmpty(header);

	if(IsEmpty(header))
		printf("빈 리스트입니다.\n");

	Insert(12,header,header);
	Insert(10,header,header);


	printf("\n");

	printf("%d\n",header->Next->Next->Element); // 12출력
	printf("%d\n",header->Next->Element); // 10출력 *중요한점! 헤더는 지지대 역할이다 헤더를 계산에 포함시키지는 않는다*

	PrintList(header);

	return 0;
}

List MakeEmpty(List H){
	H = (List)malloc(sizeof(struct Node));

	H->Next = NULL;
	H->Element = 0;

	return H;

}

int IsEmpty(List L){
	return L->Next == NULL;
}

void Insert( ElementType X, List L, Position P ){ // Insert에서 Position P에 다음에 새로운 값을 입력해준다.

	Position TmpCell; //새로운 리스트를 만들어준다.

	TmpCell = malloc(sizeof(struct Node)); //메모리 할당
	if (TmpCell == NULL)
		printf("Insert is error!\n");
	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;

}

void PrintList(List L){

	Position p;
	p = L->Next;

	if( p== NULL){
		printf("list is empty!\n");
		return;
	}

	while(p!= NULL){
		printf("key: %d   ",p->Element);
		p = p->Next; // 처음 시작이었던 P가 이제 p가 가리키는 다음 리스트로 이동했다는 뜻이다
	}
	printf("\n");
}

// 이거 함수 하나씩 써보면서 이해하는 방법 이용해야 한다