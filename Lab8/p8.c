#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode *Position; 
typedef struct AVLNode *AVLTree; 
typedef int ElementType;

struct AVLNode{
	ElementType Element;
	AVLTree Left; 
	AVLTree Right; 
	int Height;
};

Position SingleRotateWithLeft(Position node); 
Position SingleRotateWithRight(Position node); 
Position DoubleRotateWithLeft(Position node); 
Position DoubleRotateWithRight(Position node); 
AVLTree Insert(ElementType X, AVLTree T);
void PrintInorder(AVLTree T);
void FatalError(char *msg);
int Height(Position node);
int Max(int H1, int H2);

int main(int argc, char* argv[]){

	FILE *fp = fopen(argv[1], "r"); 
	AVLTree myTree = NULL; 
	ElementType num;

	while (fscanf(fp, "%d", &num) != EOF){ 
		myTree = Insert(num, myTree);
		PrintInorder(myTree);
		printf("\n"); 
	}
	fclose(fp); 
	return 0;
}

AVLTree Insert(ElementType X, AVLTree T){
	//Insert a new node to the AVL Tree. 
	//If the key already exists in the tree, print an error message.
	if(T == NULL){
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		if(T == NULL)
			FatalError("Out of space!!!");
		else{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}else if(X<T->Element){
		T->Left = Insert(X,T->Left);
		if(Height(T->Left) - Height(T->Right) == 2){
			if(X<T->Left->Element)
				T= SingleRotateWithLeft(T);
			else
				T= DoubleRotateWithLeft(T);
		}
	}else if(X > T->Element){
		T->Right = Insert(X,T->Right);
		if(Height(T->Right) - Height(T->Left) == 2){
			if(X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
}
	T->Height = Max(Height(T->Left),Height(T->Right)) + 1;
	return T;
}

Position SingleRotateWithLeft(Position node){
	Position K1;

	K1 = node->Left;
	node->Left = K1->Right;
	K1->Right = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) +1;
	K1->Height = Max(Height(K1->Left),node->Height) +1;

	return K1;
}
Position SingleRotateWithRight(Position node){
	Position K1;
	K1 = node->Right;
	node->Right = K1->Left;
	K1->Left = node;

	node->Height = Max(Height(node->Left), Height(node->Right)) +1;
	K1->Height = Max(Height(K1->Right),node->Height) +1;

	return K1;
}
Position DoubleRotateWithLeft(Position node){
	node ->Left = SingleRotateWithRight(node->Left);

	return SingleRotateWithLeft(node);
}
Position DoubleRotateWithRight(Position node){
	node->Right = SingleRotateWithLeft(node->Right);

	return SingleRotateWithRight(node);
}
void PrintInorder(AVLTree T){
	if(T == NULL)
		return;
	PrintInorder(T->Left);
	printf("%d(%d) ",T->Element,T->Height);
	PrintInorder(T->Right);
}
void FatalError(char *msg){
	printf("%s\n",msg);
	exit(0);
}
int Height(Position node){
	if(node == NULL)
		return -1;
	else
		return node->Height;
}
int Max(int H1, int H2){
	if(H1>H2)
		return H1;
	else
		return H2;
}