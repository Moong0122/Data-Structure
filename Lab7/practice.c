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
void InsertMin(ElementType X, Heap* H);
void PrintHeap(Heap* H);
ElementType DeleteMin(Heap* H);
void FatalError(char *msg);

int main(int argc, char* argv[]){
	ElementType val;
	Heap *heap;
	heap = CreateHeap(7);
	InsertMin(23,heap);
	InsertMin(24,heap);
	InsertMin(15,heap);
	InsertMin(13,heap);
	InsertMin(27,heap);
	PrintHeap(heap);
	val = DeleteMin(heap);
	PrintHeap(heap);
	printf("val = %d\n", val);
	return 0;
}

Heap* CreateHeap(int heapSize){
	//주소이다
	Heap *h = (Heap*)malloc(sizeof(struct HeapStruct));
	if(h == NULL)
		FatalError("out of space");

	h->Elements = (ElementType*)malloc(sizeof(ElementType) * (heapSize+1));
	if(h->Elements == NULL)
		FatalError("out of space");

	h->Capacity = heapSize;
	h->Size = 0;

	return h;
}
void InsertMin(ElementType X, Heap* H){
	int i;
	for(i = ++H->Size;i/2 > 0 && H->Elements[i/2] > X;i/=2){
		H->Elements[i] = H->Elements[i/2];
	}
	H->Elements[i] = X;
}
void PrintHeap(Heap* H){
	int i;
	for(i = 1;i<=H->Size;i++){
		printf("%d ",H->Elements[i]);
	}
	printf("\n");
}
void FatalError(char *msg){
	printf("%s\n",msg);
	exit(0);
}
ElementType DeleteMin(Heap* H){
	int i, child;
	ElementType MinElement, LastElement;

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for(i = 1;i*2 <= H->Size;i = child){
		child = i*2;
		if(child != H->Size && H->Elements[child+1] < H->Elements[child])
			child++;
		if(LastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
