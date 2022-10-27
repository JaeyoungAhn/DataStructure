#include <iostream>
#include <deque>
using namespace std;

int main(void) {
    int NumOfPeople;
    int Kth;
    deque<int> deq;
    int move;
    int temp;
    // 1 2 3 4 5 6 7 (7,3)
    // 3 6 2 7 5 1 4
    // 7 1 4 5
    cin >> NumOfPeople >> Kth;
    move = Kth-1;
    for(int i=1; i<=NumOfPeople; i++) deq.push_back(i);
    while(!deq.empty()) {
        for(int i=0; i<move; i++){
            temp = deq.front();
            deq.pop_front();
            deq.push_back(temp);
        }
        cout << deq.front() << ", ";
        deq.pop_front();
    }
    cout

}