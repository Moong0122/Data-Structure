#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct CircularQueue{
  ElementType *key;
  int front;
  int rear;
  int qsize; //큐에 데이터가 증가할때마다 하나씩 올려준다
  int max_queue_size;
}CircularQueue;

CircularQueue* MakeEmpty( int max );
int IsEmpty( CircularQueue* Q );
int IsFull( CircularQueue* Q );
void Enqueue( CircularQueue* Q, ElementType X ); 
ElementType Dequeue( CircularQueue* Q );
void PrintFirst (CircularQueue* Q);
void PrintRear (CircularQueue* Q); 
void DeleteQueue (CircularQueue* Q );
void FatalError( char *msg );
void Error( char *msg );

int main(int argc, char *argv[]){
	char command;
	int key1;

	FILE *input;

	CircularQueue *S = NULL;

	if(argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");

	while(1) {
		command = fgetc(input); 
		if(feof(input)) 
			break; 
		switch(command) {
			case 'n':
				fscanf(input, "%d", &key1);
				S = MakeEmpty(key1);
				break;
			case 'e': // enqueue a new element with the key “x” after the last element.
				fscanf(input, "%d", &key1); 
				Enqueue( S, key1 );
				break;
			case 'd': //dequeue the first element in the queue. 
				Dequeue(S);
				break; 
			case 'f': //print the first element in the queue.
				PrintFirst(S);
				break;
			case 'r': //print the last element in the queue.
				PrintRear(S);
				break; 
			default:
					;
			} 
		}
		//system("PAUSE");
		DeleteQueue(S); 
		fclose(input); 
		return 0;

}

void FatalError( char *msg ) {
 	printf("%s\n", msg);
	exit(0); 
}


void Error( char *msg ) {
   printf("%s\n", msg);
}

CircularQueue* MakeEmpty( int max ){
    
	CircularQueue* newQueue =(CircularQueue*)malloc(sizeof(CircularQueue)); 
	newQueue->key = (ElementType *)malloc(sizeof(ElementType)*max); newQueue->front = 0;
	newQueue->rear = -1;
	newQueue->qsize = 0; 
	newQueue->max_queue_size = max;
	return newQueue; //주소를 넘겨준다
}
int IsEmpty( CircularQueue* Q ){
	if(Q->qsize == 0)
		return 1;
	else
		return 0;
}
int IsFull( CircularQueue* Q ){
	if(Q->qsize == Q->max_queue_size)
		return 1;
	else
		return 0;
}
void Enqueue( CircularQueue* Q, ElementType X ){
	if(!IsFull(Q)){
		if(++Q->rear == Q->max_queue_size)
			Q->rear = 0;
		Q->key[Q->rear] = X;
		Q->qsize++;
	}
	else
		printf("Enqueue Failed : Queue is full!\n");
}
ElementType Dequeue( CircularQueue* Q ){
	ElementType data;
	if(IsEmpty(Q)){
		Error("Dequeue Failed : Queue is empty!");
		return -1;
	}
	data = Q->key[Q->front];
	Q->front = (Q->front+1) % Q->max_queue_size;
	Q->qsize--;

	return data;
}
void PrintFirst (CircularQueue* Q){
	if(IsEmpty(Q)){ //isempty함수는 비어있다면 1을 반환한다
		Error("Print First Failed : Queue is empty");
	}else{
		printf("First element is %d.\n",Q->key[Q->front]);
	}
}
void PrintRear (CircularQueue* Q){
	if(IsEmpty(Q)){ //isempty함수는 비어있다면 1을 반환한다
		printf("Print Rear Failed : Queue is empty\n");
	}else{
		printf("Last element is %d.\n",Q->key[Q->rear]);
	}
}
void DeleteQueue (CircularQueue* Q ){
	free(Q->key);
	free(Q);
}
