#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int A[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g,int start, int end) { //시작점과 도착점을 입력받아 최단 거리 구하기
	printf("Shortest Distance: %2d", A[start][end]);
}

void floyd(GraphType* g)
{

	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j];

	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++)
			for (j = 0; j < g->n; j++)
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
	}

	int sorted_vertices[MAX_VERTICES]; //최단 경로 출력
	for (i = 0; i < g->n; i++)
		sorted_vertices[i] = i;

	for (i = 0; i < g->n - 1; i++) {
		for (int j = 0; j < g->n - i - 1; j++) {
			if (A[sorted_vertices[j]][0] > A[sorted_vertices[j + 1]][0]) {
				int temp = sorted_vertices[j];
				sorted_vertices[j] = sorted_vertices[j + 1];
				sorted_vertices[j + 1] = temp;
			}
		}
	}

	printf("Sorted Vertices: ");
	for (i = 0; i < g->n; i++) {
		printf("%d ", sorted_vertices[i] + 1);
	}
	printf("\n");
}
int main(void) {

	GraphType g = { 10,
	{{0 ,3 ,INF,INF,INF,11 ,12 ,INF,INF,INF},
	{3 ,0 ,5 ,4 ,1 ,7 ,8 ,INF,INF,INF},
	{INF,5 ,0 ,2 ,INF,INF,6 ,5 ,INF,INF},
	{INF,4 ,2 ,0 ,13 ,INF,INF,14 ,INF,16 },
	{INF,1 ,INF,13 ,0 ,9 ,INF,INF,18 ,17 },
	{11 ,7 ,INF,INF,9 ,0 ,INF,INF,INF,INF},
	{11 ,8 ,6 ,INF,INF,INF,0 ,13 ,INF,INF},
	{INF,INF,5 ,14 ,INF,INF,13 ,0 ,INF,15 },
	{INF,INF,INF,INF,18 ,INF,INF,INF,0 ,10},
	{INF,INF,INF,16 ,17,INF,INF,15 ,10,0 } }
	};

	printf("Floyd-Warshall Algorithm\n");

	floyd(&g);

	int start;
	int end;

	
	while (1) {
		printf("Start Node: ");
		scanf_s("%d", &start);
		printf("End Node: ");
		scanf_s("%d", &end);
		if ((start < 1 && start > 0) || (end < 11 && end > 0))
			printA(&g, start - 1, end - 1);
		else { //범위를 벗어나면 종료
			printf("범위를 벗어났습니다.\n");
			exit(1);
		}
		printf("\n\n");
	}

}