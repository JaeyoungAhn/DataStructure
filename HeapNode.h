//
// Created by Ahn on 2022/11/18.
//
#include <cstdio>
class HeapNode {
    int key; // key 값
public:
    HeapNode( int k = 0 ) : key(k) { }
    void setKey(int k) { key = k; }
    int getKey() { return key; }
    void display() { printf("%4d", key); }
};

]