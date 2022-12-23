#include <iostream>
#include <stack>
using namespace std;

int main(void) {
    stack<int> s;
    int order, num, current, idx;
    idx=0;
    order=1;
    cin >> num;

    int *list = new int[num];

    for(int i=0; i<num; i++) cin >> list[i];

    for(int i=0; i<num; i++) {
        s.push(order++);
        while (!s.empty() && (list[idx] == s.top()) ) {
            idx++;
            s.pop();
        }
    }

    if(s.empty()) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}

