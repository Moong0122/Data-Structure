#include <stdio.h>
#include <limits.h>

#define TRUE	1
#define FALSE	0
#define MAX_VERTEX	7		/* 정점의 수 */
#define INF	1000	/* 무한대(연결이 없는 경우) */
#define NIL -1

/* 네트워크의 인접행렬 */
int weight[MAX_VERTEX][MAX_VERTEX]={
	{   0,  7,  INF, INF,   3,  10, INF },
	{   7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{   3,  2,  INF,  11,   0, INF,   5 },
	{  10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 }};

int distance[MAX_VERTEX];/* 시작정점으로부터 최단경로 거리 */
int found[MAX_VERTEX];		/* 최소 경로가 정해진 정점 표시 */
int prev_node[MAX_VERTEX];   /* 출발지로부터 경로상의 앞 노드 */

int choose(int distance[], int n, int found[])
{  
	// found 되지 않은 것 중에서 가장 작은 값을 골라준다.
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++){
		if(distance[i] < min && !found[i]){
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}
void shortest_path(int start, int n) 
{
	int i,u,w;
	for(i = 0;i<n;i++){
		distance[i] = INF;
		found[i] = FALSE;
		prev_node[i] = NIL;
	}
	for(i=0;i<n;i++){
		distance[i] = weight[start][i];
	}
	found[start] = TRUE;
	distance[start] = 0;
	prev_node[start] = start;
	for(i=0;i<n;i++){
		if(distance[i]<INF)
			prev_node[i] = start;
	}
	printf("start: %d\n", start);
	for(i=0;i<n-1;i++){
		u = choose(distance,n,found); 
		found[u] = TRUE;
		printf("found: %d\n",u);
		for(w=0;w<n;w++){
			if(!found[w] && distance[u] + weight[u][w] < distance[w]){
				distance[w] = distance[u] + weight[u][w];
				prev_node[w] = u;
			}
		}
	}
}
void printShortestPath(int *prev_node, int last_node, int start_node)
{
	if(last_node != start_node)
		printShortestPath(prev_node, prev_node[last_node], start_node);
	printf("%d ",last_node);
}

void printPreviousNode(int *prev_node)
{
    int i;

    printf("-------------------------------------------\n");
    printf("  node number: ");
	for(i=0; i<MAX_VERTEX; i++)
        printf("%2d ", i);
    printf("\n");
    printf("-------------------------------------------\n");
    printf("previous node: ");
	for(i=0; i<MAX_VERTEX; i++)
        printf("%2d ", prev_node[i]);
    printf("\n");
    printf("-------------------------------------------\n");
}
int main()
{
    int i;
    int start=0;

	shortest_path(start, MAX_VERTEX);

    printPreviousNode(prev_node);

	for(i = 0 ; i < MAX_VERTEX ; i ++)	{
            printf("Shorted Path to %d: ", i);
            printShortestPath(prev_node, i, start);
            printf(" (distance : %d)\n",distance[i]);
	}
}