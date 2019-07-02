#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

typedef struct HeapStruct {
	int Capacity; // max heap capacity
	int Size; // current heap size
	ElementType *Elements; 
}Heap;

Heap* CreateHeap(int heapSize);
void InsertMax(ElementType X, Heap* H);
int DeleteMax(Heap* H);
void PrintHeap(Heap* H);
void FatalError( char *msg );
void Error( char *msg );
int IsFull(Heap* H);
int IsEmpty(Heap* H);

int main(int argc, char* argv[]){
	
	FILE *fi = fopen(argv[1], "r");
	char cv;
    Heap* maxHeap;
    int heapSize, key;

	while(!feof(fi)){
 	 // do operation
		fscanf(fi,"%c",&cv);
		switch(cv){
			case 'n':
				fscanf(fi,"%d",&heapSize);
				maxHeap = CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fi,"%d",&key);
				InsertMax(key, maxHeap);
				break;
			case 'd':
				DeleteMax(maxHeap);
				break;
			case 'p':
				PrintHeap(maxHeap);
				break;
		}
	}
	return 0;
}

void FatalError( char *msg ) {
    printf("%s\n", msg);
    exit(0);
}
void Error( char *msg ) {
    printf("%s\n", msg);
}

Heap* CreateHeap(int heapSize){
	Heap* h = (Heap*)malloc(sizeof(struct HeapStruct));
	if(h == NULL)
		FatalError("out of space");
	//우리는 배열의 1번부터 사용하기 때문에 만약 사이즈가 7이라면 8크기 배열을 만들어줘야 한다.
	h->Elements = (ElementType*)malloc((heapSize+1) * sizeof(ElementType));

	if(h->Elements == NULL)
		FatalError("out of space");

	h->Capacity = heapSize;
	h->Size = 0;

	return h;
}
int IsFull(Heap* H){ 
	return H->Size == H->Capacity;
}
int IsEmpty(Heap* H){
	return H->Size == 0;
}
void InsertMax(ElementType X, Heap* H){
	int i;
	if(IsFull(H)){
		printf("Insertion Error : Max Heap is full\n");
		return;
	}
	for(i = ++H->Size;i/2 > 0 && H->Elements[i/2] < X; i /= 2)
			H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = X;
}
int DeleteMax(Heap* H){
	int i, child;
	ElementType MaxElement, LastElement;

	if(IsEmpty(H)){
		printf("Deletion Error : Max Heap is empty\n");
		return 0;
	}
	MaxElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for(i = 1; i*2 <= H->Size; i = child){

		child = i*2;
		if(child != H->Size && H->Elements[child+1] > H->Elements[child])
			child++;
		if(LastElement < H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MaxElement;
}
void PrintHeap(Heap* H){

	int i,hsize;
	hsize = H->Size;

	if(IsEmpty(H)){
		Error("Print Error : Max heap is empty");
		return;
	}
	for(i=1;i<=hsize;i++){
		printf("%d ",H->Elements[i]);
	}
	printf("\n");
}