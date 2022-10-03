#include <iostream>
#include <stack>
using namespace std;

int main(void) {
    stack<int> s;
    int num, current, idx;
    idx=1;
    cin >> num;
    for(int i=0; i<num; i++) {
        cin >> current;
        while(true) {
            if(idx<=num) s.push(idx);
            if(idx<num) idx++;
            if( (idx == num && s.top() != current) || ) break;
            if(s.top() == current) s.pop();
        }
    }
    if(s.empty()) cout << "YES";
    else cout << "NO";

    return 0;
}