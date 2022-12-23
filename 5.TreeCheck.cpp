#include <iostream>
#include <map>
using namespace std;

// in-degree가 2 이상인경우 break -> not a tree
// vertex = edge + 1 이어야만 tree
// 들어오는 간선이 없는 단 하나 존재해야함

int main(void) {
    map<int, int> in_degree;
    map<int, int> out_degree;

    int out_degree_count=0;

    int a, b;
    int flag = 1;
    int rootnum = 0;

    do {
        cin >> a;
        cin >> b;
        if(a==0 && b==0) break;

        if(in_degree.count(b) == 0) {
            in_degree.insert(b, 0);
        }
        else in_degree[b]+=1;

        if(out_degree.count(a) == 0) {
            out_degree.insert(a, 0);
        }
        else in_degree[a]+=1;

        if(in_degree[b]>1){
            cout << "not a tree\n";
            return 0;
        }
    }while(1);

    cout << "tree\n";

    return 0;
}