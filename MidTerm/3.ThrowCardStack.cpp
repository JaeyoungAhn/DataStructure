#include <iostream>
#include <deque>
using namespace std;

int main(void) {
    int num; // 1 2 3 4 5 6
    int temp;
    deque<int> s;
    cin >> num;
    for(int i=num; i>=1; i--) s.push_back(i);
    while(s.size() != 1) {
        s.pop_back();
        temp = s.at(s.size()-1);
        s.pop_back();
        s.push_front(temp);
    }
    cout << s.at(0);
    return 0;
}