#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_SIZE 26

using namespace std;

int location[MAX_SIZE][MAX_SIZE];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
int n, c;
vector<int> DanjiNum;

void DFS(int a, int b);

int main()
{
    scanf("%d", &n);
    string ephe;

    for(int i = 1; i <= n; i++) {
        cin >> ephe;
        for(int j = 1; j <= n; j++) {
            location[i][j] = (ephe[j - 1] - '0');
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(location[i][j] == 1) {
                c = 0;
                DFS(i, j);
                DanjiNum.push_back(c);
            }
        }
    }

    sort(DanjiNum.begin(), DanjiNum.end());

    printf("%lu\n",DanjiNum.size());

    for(int i = 0; i < DanjiNum.size(); i++) {
        printf("%d\n", DanjiNum[i]);
    }

    return 0;
}

void DFS(int a, int b)
{
    location[a][b] = 0;
    c++;

    for(int i = 0; i < 4; i++) {
        if(a + dy[i] < 1 || a + dy[i] > n || b + dx[i] < 1 || b + dx[i] > n) continue;
        if(location[a + dy[i]][b + dx[i]] == 1)
            DFS(a + dy[i], b + dx[i]);
    }
}