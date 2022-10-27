#include <iostream>
using namespace std;

int main(void) {
    int n;
    long result=1;
    cin >> n;
    // 10
    for(int i=1; i<=n; i++) {
        result*=i;
    }
    cout << result;
}