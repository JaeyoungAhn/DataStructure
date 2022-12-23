#include <iostream>
#include <limits.h>

using namespace std;

int N;
int parent[101];
int find(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void uni(int i, int j)
{
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}


void Kruskal(int cost[][101])
{
    int mincost = 0;

    for (int i = 0; i < N; i++)
        parent[i] = i;

    int edge_num = 0;
    while (edge_num < N - 1) {
        int min = INT_MAX, a = -1 , b = -1;
        for (int i = 0; i < N ; i++) {
            for (int j = 0; j < N; j++) {
                if (find(i) != find(j) && cost[i][j] < min) {
                    min = cost[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        uni(a, b);
        edge_num++;
        mincost += min;
    }
    printf("%d", mincost);
}

int main()
{
    int cost[101][101]={false};
    int num;
    scanf("%d", &N);

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            scanf("%d", &num);
            if(N!=0) cost[i][j]=num;
            else cost[i][j]=INT_MAX;
        }
    }

    Kruskal(cost);

    return 0;
}