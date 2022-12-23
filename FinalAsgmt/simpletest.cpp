#include <iostream>
using namespace std;


int main() {
    int *a = new int(5);
    int *b = new int(3);

    void swap(int *, int *);

    swap(a, b);
    cout << *a << *b << endl;
    return 0;
}

void swap(int *a_address, int *b_address) {
    int a_tmp =*a_address;

    *a_address = *b_address;
    *b_address = a_tmp;

    cout << *a_address << *b_address << endl;
}
