#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N, grey, volume, max;
    cin >> N;
    int volumes[N];
    for(int i=0; i<N; i++){
        cin >> volume;
        volumes[i] = volume;
    }
    cin >> grey;
    for(int i=0; i<grey; i++) {
        sort(volumes, volumes+N);
        volumes[0]+=1;
        volumes[1]+=1;
        volumes[2]+=1;
    }
    sort(volumes, volumes+N);
    max = volumes[N-1];
    if( (max%50) == 0 ) {
        cout << (max/50);
    }
    else {
        cout << (max/50)+1;
    }


    return 0;
}