#include <iostream>
#include <deque>

using namespace std;

class balloon {
    public:balloon(int balNum, int balChg) {
        this->balNum = balNum;
        this->balChg = balChg;
    }
    public:int balNum;
    public:int balChg;
};

int main() {
    int num;
    int chg;
    int flag=0;
    deque<balloon> q; // 3 2 1 -3 -1
    cin >> num;
    for(int i=1; i<=num; i++) {
        cin >> chg;
        q.push_back(balloon(i, chg));
    }

//    while(!q.empty()) {
//        balloon b = q.front();
//        cout << b.balNum << " and " << b.balChg << "\n";
//        q.pop_front();
//    }

    while(!q.empty()) {
        int popchg;
        int popnum;
        if(flag==1) {
            balloon b = q.back();
            q.pop_back();
            popchg = b.balChg;
            popnum = b.balNum;
            flag=0;
        }
        else {
            balloon b = q.front();
            q.pop_front();
            popchg = b.balChg;
            popnum = b.balNum;
        }

        chg = popchg;
        cout << popnum << " ";
        if(chg < 0) {
            chg += 1;
            chg *= -1;
            flag=1;
        }
        else if (chg > 0) {
            chg -= 1;
        }
        else {
            cout << "0 is not allowed\n";
        }

        for(int i = 0; i < chg; i++) {
            if(flag==1){
                balloon b = q.back();
                q.pop_back();
                q.push_front(b);
            }
            else {
                balloon b = q.front();
                q.pop_front();
                q.push_back(b);
            }
        }
    }

    return 0;
}