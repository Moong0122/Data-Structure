#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TreeNode* SearchTree;
typedef struct TreeNode* Node;
typedef struct TreeNode Tree;
typedef int ElementType; 

struct TreeNode{

	ElementType Element; 
	SearchTree Left; 
	SearchTree Right;
};

Node Find(ElementType X, SearchTree T);
Node FindMax(SearchTree T);
Node FindMin(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
void printInorder(Tree* root);
void printPreorder(Tree* root);
void printPostorder(Tree* root);
void FatalError( char *msg );
void Error( char *msg );

int main(int argc, char* argv[]){
	
	FILE *fi = fopen(argv[1], "r");
	char cv;
    int key;

    Tree* root = NULL;

	while(!feof(fi)){
 	 // do operation
		fscanf(fi,"%c",&cv);
		switch(cv){
			case 'i':
				fscanf(fi,"%d",&key);
				root = Insert(key,root);
				break;
			case 'd':
				fscanf(fi,"%d",&key);
				Delete(key,root);
				break;
			case 'f':
				fscanf(fi,"%d",&key);
				Find(key,root);
				break;
			case 'p':
				fscanf(fi,"%c",&cv);
				if(cv == 'i')
					printInorder(root);
				else if(cv == 'r')
					printPreorder(root);
				else if(cv == 'o')
					printPostorder(root);
				printf("\n");
				break;
		}
	}
	return 0;
}

Node Find(ElementType X, SearchTree T){ 
//find the given key to check whether the key exists in the tree .
	if(T == NULL){
		printf("%d is not in the tree\n", X);
		return NULL;
	}
	if(X < T->Element)
		return Find(X,T->Left);
	else if(X > T->Element)
		return Find(X,T->Right);
	else {// X == T->Element
		printf("%d is in the tree\n", X);
		return T;
	}
}
Node FindMax(SearchTree T){
	if(T==NULL)
		return NULL;
	else{
		while(T->Right!=NULL){
			T= T->Right;
		}
		return T;
	}
}
Node FindMin(SearchTree T){
	if(T == NULL)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}
SearchTree Insert(ElementType X, SearchTree T){
	if(T == NULL){
		T = malloc(sizeof(struct TreeNode));
		if(T == NULL)
			FatalError("Out of space!!!");
		else{
			printf("Insert %d\n",X);
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}else if(X < T->Element){
		T->Left = Insert(X,T->Left);
	}else if(X > T->Element){
		T->Right = Insert(X,T->Right);
	}
	return T;
}
SearchTree Delete(ElementType X, SearchTree T){
	SearchTree tmp;
	if(T == NULL)
		printf("Deletion error : %d in not in the tree\n",X);
	else if(X < T->Element)
		T->Left = Delete(X, T->Left);
	else if(X > T->Element)
		T->Right = Delete(X, T->Right);
	else if(T->Element == X){ //x를 찾았다! 하지만 케이스 별로 구분해야 한다
		printf("Delete %d\n",X);
		if(T->Left == NULL && T->Right == NULL){
			tmp = T;
			free(tmp);
			T = NULL;
		}else if(T->Left == NULL){
			tmp = T;
			T = T->Right;
			free(tmp);
		}else if(T->Right == NULL){
			tmp = T;
			T = T->Left;
			free(tmp);
		}else{
			tmp = FindMin(T->Right);
			T->Element = tmp->Element;
			T->Right = Delete(T->Element, T->Right);
		}
	}

	return T;
}
void printInorder(Tree* root){
	if(root){
		printInorder(root->Left);
		printf("%d " , root->Element);
		printInorder(root->Right);
	}
}
void printPreorder(Tree* root){
	if(root){
		printf("%d ", root->Element);
		printPreorder(root->Left);
		printPreorder(root->Right);
	}
}
void printPostorder(Tree* root){
	if(root){
		printPostorder(root->Left);
		printPostorder(root->Right);
		printf("%d ", root->Element);
	}
}

void FatalError( char *msg ) {
    printf("%s\n", msg);
    exit(0);
}
void Error( char *msg ) {
    printf("%s\n", msg);
}