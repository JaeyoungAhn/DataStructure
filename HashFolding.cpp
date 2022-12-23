#include <iostream>
using namespace std;
// 12$34567$890
int main() {
    string input;
    int n1=0;
    int n2=0;
    int n3=0;
    cin >> input;
    int index=0;
    int digit=1;
    while(input[index]!='$') {
        n1 = n1 + (digit * (input[index++]-'0') );
        digit*=10;
    }
    index++;
    while(input[index]!='$')
        index++;
    index--;
    digit=1;
    while(input[index]!='$') {
        n2 = n2 + (digit * (input[index--]-'0') );
        digit*=10;
    }
    index++;
    while(input[index]!='$')
        index++;
    index++;
    digit=1;
    while(input[index]!='\0') {
        n3 = n3 + (digit * (input[index++]-'0') );
        digit*=10;
    }

    cout << n1+n2+n3;

    return 0;
}