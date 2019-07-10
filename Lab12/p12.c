#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int* check_visit;
}Graph;

CircularQueue* MakeEmpty(int max); 
int IsEmpty(CircularQueue* Q);
int IsFull(CircularQueue* Q);
void Enqueue(CircularQueue* Q, int X); 
Vertex Dequeue(CircularQueue* Q); 
void PrintQueue(CircularQueue* Q); 
void DeleteQueue(CircularQueue* Q); 
Graph makeGraph(FILE* fi);
void DFS_recursive(Graph g, int visit_node, int end);
void BFS_search(Graph g, int start, int end);
Graph refreshGraph(Graph g);


int main(int argc, char* argv[]){
	FILE *fi = fopen("input.txt","r");
	Graph g = makeGraph(fi);

	int start, end;
	fscanf(fi,"%d-%d",&start,&end);
	printf("start: %d  end: %d\n",start,end );
	printf("DFS : ");
	DFS_recursive(g,start, end);
	printf("\n");
	if(g.check_visit[end-1] == 0)
		printf("cannot find\n");
	
	g = refreshGraph(g);

	printf("BFS : ");
	BFS_search(g,start,end);
	printf("\n");
	
	fclose(fi);

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
Graph makeGraph(FILE* fi){
	int num;
	fscanf(fi,"%d",&num);
	Graph g;
	g.size = num;

	g.weight = (int**)malloc(sizeof(int*)*num);
	g.check_visit = (int*)malloc(sizeof(int)*num);
	memset(g.check_visit,0,sizeof(int)*g.size);

	if(g.check_visit == NULL)
		printf("Error\n");
	int i;
	for(i = 0;i<num;i++){
		g.weight[i] = (int*)malloc(sizeof(int)*num);
		memset(g.weight[i],0,g.size*sizeof(int));
	}
	char temp = 0;
	while(temp != '.'){
		int num1,num2;
		fscanf(fi,"%d-%d",&num1,&num2);
		g.weight[num1-1][num2-1] = 1;
		temp = fgetc(fi);
	}
	return g;
}
void DFS_recursive(Graph g, int visit_node, int end){
	int i;
	g.check_visit[visit_node-1] = 1;
	printf("%d ",visit_node);

	if(visit_node == end)
		return;

	for(i=0;i<g.size;i++){
		if(g.check_visit[end-1] == 1)
			break;
		if(g.weight[visit_node-1][i] == 1 && g.check_visit[i] == 0)
			DFS_recursive(g,i+1,end);
	}
}
Graph refreshGraph(Graph g){
	memset(g.check_visit,0,sizeof(int)*g.size);
	return g;
}
void BFS_search(Graph g, int start, int end){
	int i;
	CircularQueue *q;
	q = MakeEmpty(g.size);
	Enqueue(q,start);
	int tmp = Dequeue(q);

	while(tmp != -1){
		if(g.check_visit[tmp-1] == 1){
			tmp = Dequeue(q);
			continue;
		}
		g.check_visit[tmp-1] = 1;
		printf("%d ", tmp);

		if(tmp == end)
			break;

		for(i=0;i<g.size;i++){
			if(g.weight[tmp-1][i] == 1 && g.check_visit[i] == 0)
				Enqueue(q,i+1);
		}
	}
	if(tmp != end)
		printf("cannot find\n");
}
