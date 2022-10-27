#include <iostream>
#include <stack>
#define MAZE_SIZE 6

using namespace std;
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};

class location {
public: int x;
        int y;
        location(int ex, int why) {
            x=ex;
            y=why;
        }

};

char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1'},
        {'e','0','1','0','0','1'},
        {'1','0','0','0','1','1'},
        {'1','0','1','0','1','1'},
        {'1','0','1','0','0','x'},
        {'1','1','1','1','1','1'}
};

void maze_print() {
    for(int i=0; i<MAZE_SIZE; i++) {
        for(int j=0; j<MAZE_SIZE; j++) {
            cout << maze[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main(void) {
    stack<location> s;
    int row = 1;
    int col = 0;
    int new_row = 0;
    int new_col = 0;
    s.push(location(col,row));
    while(1) {
        if(s.empty()) {
            cout << "unreachable\n";
            break;
        }
        location lo = s.top();
        s.pop();
        row = lo.y;
        col = lo.x;
        if(maze[row][col]=='x') {
            cout << "finish";
            break;
        }
        maze[row][col] = '.';
        maze_print();
        for(int i=0; i<4; i++) {
            new_row = row + dy[i];
            new_col = col + dx[i];
            if (new_row < 0 || new_col < 0 || new_row > MAZE_SIZE - 1 || new_col > MAZE_SIZE - 1)
                continue;
            if (maze[new_row][new_col] == '0' || maze[new_row][new_col] == 'x') s.push(location(new_col, new_row));
        }
    }


    return 0;
}