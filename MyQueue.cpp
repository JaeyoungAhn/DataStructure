//
// Created by Ahn on 2022/09/23.
//

#include "MyQueue.h"
#include <iostream>
MyQueue::MyQueue(int queueCapacity):capacity(queueCapacity) {
    if (capacity < 1)
        std::cout << "MyQueue capacity must be > 0" << std::endl;
    queue = new int[capacity];
    size = 0;
    front = back = -1;
}

bool MyQueue::IsEmpty() const {
    return size == 0;
}


int &MyQueue::Front() const {
    return queue[front+1];
}

int &MyQueue::Rear() const {
    return queue[back];
}

void MyQueue::Push(const int &x) {
    std::cout << capacity << std::endl;
    if (size == capacity) {
        std::cout << "MyQueue is full. Cannot push." << std::endl;
    }
    else {
        if ( back+1 == capacity ) back=-1;
        // add at stack top
        queue[++back] = x;
        size++;
    }

}

void MyQueue::Pop() {
    if (IsEmpty())
        std::cout << "MyQueue is empty. Cannot delete." << std::endl;
    if(front+1 == capacity ) front=-1;
    front++;
    size--;
}
