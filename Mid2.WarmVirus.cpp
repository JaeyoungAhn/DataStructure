#include <cstdio>
using namespace std;

int network[101][101];
int visit[101];
int cnt=-1;
void dfs(int n, int now);

int main (void){
    int n;
    int con;
    int a, b;

    scanf("%d", &n);
    scanf("%d", &con);
    for(int i=0; i<con; i++){
        scanf("%d %d", &a, &b);
        network[a][b] =1;
        network[b][a]=1;

    }
    dfs(n, 1);

    printf("%d\n", cnt);
}

void dfs(int n, int now){
    visit[now] = 1;
    cnt++;
    for(int i=1; i<n+1; i++){
        if(visit[i]==1)
            continue;
        if(network[now][i]==0)
            continue;
        dfs(n, i);
    }
}