#include <iostream>
using namespace std;

void hanoi_tower(int n, char from, char tmp, char to) {
    if (n==1) cout << "원판 1을 " << from << "에서 " << to <<"로 옮긴다.\n";
    else {
        hanoi_tower(n-1, from, to, tmp);
        cout <<"원판 "<<n<<"을 "<<from<<"에서 "<<to<<"로 옮긴다.";
        hanoi_tower(n-1, tmp, from, to);
    }
};

int main(void) {
    hanoi_tower(10, 'A', 'B', 'C');
    return 0;
}