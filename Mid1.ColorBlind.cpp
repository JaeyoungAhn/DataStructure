#include <stdio.h>
#include <string.h>

using namespace std;

int n, cnt = 0;
char pixel[100][100];
bool isVisited[100][100] = { false };

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

void dfs(int x, int y) {
    isVisited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (!isVisited[nx][ny] && pixel[x][y] == pixel[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", pixel[i]);
    }

    //non color-blind
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!isVisited[i][j]) {
                dfs( i, j);
                cnt++;
            }
        }
    }
    printf("%d ", cnt);

    //color-blind
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (pixel[i][j] == 'G') pixel[i][j] = 'R';
            else pixel[i][j] = pixel[i][j];
        }
    }
    memset(isVisited, false, sizeof(isVisited));

    cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!isVisited[i][j]) {
                dfs(i, j);
                cnt++;
            }
        }
    }
    printf("%d", cnt);

    return 0;
}