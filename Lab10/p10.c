#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MaxData 10000

typedef int ElementType;

void Msort(ElementType A[], ElementType TmpArray[], int Left, int Right);
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd);
void Quicksort(ElementType A[],int l, int r);
int Partition(ElementType A[],int l, int r);
ElementType select_pivot(ElementType A[], int l, int r);
void printData(ElementType A[], int start, int end);
void FatalError(char *msg);
void swap(int *n, int *m);

int main(){

	int i;
	time_t before, after, ms, qs;
	ElementType *MdataArray, *tmpArray;
	ElementType *QdataArray;

	srand(time(NULL));

	MdataArray = (ElementType*)malloc(sizeof(ElementType) * MaxData);
	if(MdataArray == NULL)
		FatalError("Not enough memory!!");
	
	tmpArray = (ElementType*)malloc(sizeof(ElementType) * MaxData);
	if(tmpArray == NULL)
		FatalError("Not enough memory!!");

	for(i=0; i<MaxData;i++){
		MdataArray[i] = rand()%MaxData; //랜덤한 값을 배열에 넣어준다
	}

	printf("Merge sort:\n");
	before = clock();
	Msort(MdataArray, tmpArray, 0, MaxData-1);
	after = clock();
	ms = after - before;
	printf("Sorted data by Merge sort:\n");
	printData(MdataArray,0,20);
	printf("Merge sort running time : %ld msec.\n", ms);
	free(MdataArray);
	free(tmpArray);

	QdataArray = (ElementType*)malloc(sizeof(ElementType) * MaxData);
	if(QdataArray == NULL)
		FatalError("Not enough memory!!");

	for(i=0;i<MaxData;i++){
		QdataArray[i] = rand() % MaxData;
	} //랜덤한 수를 배열에 넣어준다

	printf("Quick sort:\n");
	before = clock();
	Quicksort(QdataArray,0,MaxData-1);
	after = clock();
	qs = after - before;
	printf("Sorted data by Quick sort:\n");
	printData(QdataArray,0,20);
	printf("Quick sort running time: %ld msec.\n",qs);
	free(QdataArray);

	return 0;
}

void FatalError(char *msg){
	printf("%s\n",msg);
	exit(0);
}
void Msort(ElementType A[], ElementType TmpArray[], int Left, int Right){
	int Center;
	if(Left < Right){
		Center = (Left+Right) / 2;
		//printf("%d ", Center);
	Msort(A, TmpArray, Left, Center);
	Msort(A, TmpArray, Center+1, Right);
	Merge(A, TmpArray, Left, Center+1, Right);
	}
}
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd){
	int i, LeftEnd, NumElements, TmpPos;
	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while(Lpos <= LeftEnd && Rpos <= RightEnd){
		if(A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
	}
	while(Lpos <= LeftEnd){
		TmpArray[TmpPos++] = A[Lpos++];
	}
	while(Rpos <= RightEnd){
		TmpArray[TmpPos++] = A[Rpos++];
	}

	for(i=0; i<NumElements; i++, RightEnd--){
		A[RightEnd] = TmpArray[RightEnd];
	}
}
void Quicksort(ElementType A[],int l, int r){
	int p;
	if(l >= r)
		return;
	p = Partition(A,l,r);
	Quicksort(A,l,p-1);
	Quicksort(A,p+1,r);
}
int Partition(ElementType A[],int l, int r){
	ElementType pivot;
	int i,j;

	pivot = select_pivot(A,l,r);
	i = l-1;
	j = r;
	for(;;){
		while(A[--j] > pivot);
		while(A[++i] < pivot);
		if( i < j)
			swap(&A[i],&A[j]);
		else{
			swap(&A[i],&A[r]);
			return i;
		}
	}
}
void printData(ElementType A[], int start, int end){
	int i;
	for(i = start ; i<= end;i++){
		printf("%d ",A[i]);
	}
	printf("\n");
}
void swap(int *n, int *m){
	int tmp;
	tmp = *n;
	*n = *m;
	*m = tmp;
}
ElementType select_pivot(ElementType A[], int l, int r){
	return A[r];
}