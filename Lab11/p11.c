#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Qsize 20

typedef struct CircularQueue{ 
	int *key;
	int front;
	int rear;
	int qsize;
	int max_queue_size;
}CircularQueue;

typedef int Vertex;

typedef struct Graph{
	int size;
	int** weight;
	int* Indegree;
}Graph;

CircularQueue* MakeEmpty(int max); 
int IsEmpty(CircularQueue* Q);
int IsFull(CircularQueue* Q);
void Enqueue(CircularQueue* Q, int X); 
Vertex Dequeue(CircularQueue* Q); 
void PrintQueue(CircularQueue* Q); 
void DeleteQueue(CircularQueue* Q);
int *checkIndegree(Graph g); 
Graph makeGraph(FILE* fi);


int main(int argc, char* argv[]){
	FILE *fi;
	Graph g;
	int i;
	Vertex V,w;
	CircularQueue *Q;
	fi = fopen("input.txt","r");
	g = makeGraph(fi);
	Q = MakeEmpty(Qsize);
	g.Indegree = checkIndegree(g); 
	//topsort 구현하기
	for(int i = 0;i<g.size;i++){
		if(g.Indegree[i] == 0)
			Enqueue(Q,i);
	}
	while(!IsEmpty(Q)){
		V = Dequeue(Q);
		printf("%d ",V+1);
		for(w = 0; w < g.size; w++){ 
			if(g.weight[V][w] == 1){
				if( --g.Indegree[w] == 0)
					Enqueue(Q,w);
				}
			}
		}
	printf("\n");
	fclose(fi);
	DeleteQueue(Q);

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
	newQueue->key = (Vertex *)malloc(sizeof(Vertex)*max); 
	newQueue->front = 0;
	newQueue->rear = -1;
	newQueue->qsize = 0; 
	newQueue->max_queue_size = max;
	return newQueue;
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
void Enqueue( CircularQueue* Q, Vertex X ){
	if(!IsFull(Q)){
		if(++Q->rear == Q->max_queue_size)
			Q->rear = 0;
		Q->key[Q->rear] = X;
		Q->qsize++;
	}
	else
		printf("Enqueue Failed : Queue is full!\n");
}
Vertex Dequeue( CircularQueue* Q ){
	Vertex data;
	if(IsEmpty(Q)){
		Error("Dequeue Failed : Queue is empty!");
		return -1;
	}
	data = Q->key[Q->front];
	Q->front = (Q->front+1) % Q->max_queue_size;
	Q->qsize--;

	return data;
}
void DeleteQueue (CircularQueue* Q ){
	free(Q->key);
	free(Q);
}
void PrintQueue(CircularQueue* Q){
	int start, size;
	start = Q->front;
	size = Q->qsize;

	for(int i=0;i<size;i++){
		printf("%d ",Q->key[start]);
		start = (start+1) % Q->max_queue_size;
	}
}
int *checkIndegree(Graph g){
	int i,j;
	int *tmp;
	tmp = (int*)malloc(sizeof(int)*g.size);

	if(!tmp){
		FatalError("malloc error!!");
	}
	else
		memset(tmp,0,sizeof(int)*g.size);

	for(i=0;i<g.size;i++){
		for(j=0;j<g.size;j++){
			if(g.weight[i][j] == 1)
				tmp[j]++;
		}
	}
	return tmp;
} 
Graph makeGraph(FILE* fi){
	int num;
	fscanf(fi,"%d",&num);
	Graph g;
	g.size = num;
	g.weight = (int**)malloc(sizeof(int*)*num);
	int i;
	for(i = 0;i<num;i++){
		g.weight[i] = (int*)malloc(sizeof(int)*num);
		memset(g.weight[i],0,g.size*sizeof(int));
	}
	char temp = 0;
	while(temp != '\n'){
		int num1,num2;
		fscanf(fi,"%d-%d",&num1,&num2);
		g.weight[num1-1][num2-1] = 1;
		temp = fgetc(fi);
	}
	return g;
}
