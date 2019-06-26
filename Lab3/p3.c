#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position; 
typedef int ElementType;

struct Node{
	ElementType element;
	Position next;
};

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
void Insert( ElementType X, List L, Position P ); 
void PrintList(List L);
void Delete( ElementType X, List L );
Position Find(ElementType X, List);
Position FindPrevious ( ElementType X, List L ); 
void DeleteList ( List L );


int main(int argc, char *argv[]){ 
	char command;

	int key1, key2;

	FILE *input;

	Position header = NULL; 
	Position tmp = NULL;

	if(argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");

	header = MakeEmpty(header);

	while(1) {
		command = fgetc(input); 
		if(feof(input)) 
			break; 
		switch(command) {
			case 'i':
				fscanf(input, "%d %d", &key1, &key2);
				tmp = Find(key1, header);
				if(tmp != NULL) { //값이 이미 들어있다면
					printf("There already is an element with key %d. Insertion failed\n", key1);
					break; 
				}
				tmp = Find(key2, header); 
				Insert(key1, header, tmp);
				break;

			case 'd':
				fscanf(input, "%d", &key1); 
				Delete(key1, header); 
				break;

			case 'f':
				fscanf(input, "%d", &key1);
				tmp = FindPrevious(key1, header); 
				if(IsLast(tmp, header))
						printf("Could not find %d in the list\n", key1);
				else {
					if(tmp->element>0)
						printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
					else
						printf("Key of the previous node of %d is header.\n", key1);
				}
				break; 
			case 'p':
				PrintList(header);
				break; 
			default:
					;
			} 
		}
		system("PAUSE");
		DeleteList(header); 
		fclose(input); 
		return 0;
	}

List MakeEmpty( List L ){ //새로운 리스트를 만들어준다 

	L = (List)malloc(sizeof(struct Node));
	L->element = 0;
	L->next = NULL;
	return L;
}
int IsEmpty( List L ){ // return true if L is empty

	return L->next == NULL; // ==를 넣어서 만약에 가리키는 next가 null이라면 true이고 아니라면 false를 반환한다

}
int IsLast( Position P, List L ){ //return true if P is the last position in list L

	return P->next == NULL;
}

void Insert( ElementType X, List L, Position P ){ // Insert에서 Position P에 다음에 새로운 값을 입력해준다.

	Position TmpCell = NULL; //새로운 리스트를 만들어준다.

	TmpCell = (Position)malloc(sizeof(struct Node)); //메모리 할당
	TmpCell->element = X;

	if (P == NULL){
		printf("Insertion %d is error!\n",X);
		free(TmpCell);
		return;
	}
	TmpCell->next = P->next;
	P->next = TmpCell;
	printf("Insertion Success : %d\n",X);
}

void PrintList(List L){

	Position p = NULL;
	p = L->next;

	while(p != NULL){
		printf("key: %d   ",p->element);
		p = p->next; // 처음 시작이었던 P가 이제 p가 가리키는 다음 리스트로 이동했다는 뜻이다
	}
	printf("\n");
}

Position Find(ElementType X, List L){

	Position p = NULL;
	if(X<0)
		return L;
	p = FindPrevious(X, L);

	return p->next;
}

Position FindPrevious ( ElementType X, List L ){

	Position p = NULL;
	p = L;

	while(p->next != NULL && p->next->element != X){
		p = p->next;
	}
	return p;
}

void Delete( ElementType X, List L ){

	Position p = NULL, TmpCell = NULL;
	p = FindPrevious(X,L);

	if(!IsLast(p,L)){ //만약에 P가 마지막이 아니라면 찾았다는 뜻이므로 삭제를 시작한다
		TmpCell = p->next;
		p->next = TmpCell->next;
		free(TmpCell);
		printf("Deletion Success : %d\n",X);
	}else{
		printf("Deletion failed : element %d is not in the list\n",X);
	}
}

void DeleteList ( List L ){
	
	Position p = NULL, TmpCell = NULL;
	p = L->next;
	L->next = NULL;
	while(p != NULL){
		TmpCell = p->next;
		free(p);
		p = TmpCell;
	}
}

