#include <iostream>
#include <queue>
using namespace std;

class coordinate {
public:
    int row;
    int col;
    int days;
public:
    coordinate(int ro, int co, int day) {
        row=ro;
        col=co;
        days=day;
    }
};

int main(void) {
    int dx[] = {0,0,1,-1};
    int dy[] = {-1,1,0,0};
    queue<coordinate> q;
    int cols, rows, input, days, x, y, max_days, countdown;
    cin >> cols >> rows;
    countdown = cols*rows;
    int box[rows+1][cols+1];
    for(int i=1; i<=rows; i++) {
        for(int j=1; j<=cols; j++) {
            cin >> input;
            box[i][j]=input;
            if(input == 1) { // 토마토 있는 경우
                q.push(coordinate(i,j,0));
                countdown--;
            }
            else if(input == -1) countdown--;
        }
    }

    while(!q.empty()) {
        coordinate xy = q.front();
        q.pop();
        for(int i=0; i<4; i++) {
            x=xy.col + dx[i];
            y=xy.row + dy[i];
            days=xy.days+1;

            if(x < 1 || x > cols || y < 1 || y > rows) continue;

            if(box[y][x] == 0) {
                q.push(coordinate(y,x,days));
                box[y][x]=1;
                countdown--;
                max_days = max_days < days ? days : max_days ;
            }
        }
    }

    if(countdown==0) cout << max_days << "\n";
    else cout << "-1\n";

}

//
//6 4
//1 -1 0 0 0 0
//0 -1 0 0 0 0
//0 0 0 0 -1 0
//0 0 0 0 -1 1