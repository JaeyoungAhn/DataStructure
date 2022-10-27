//
// Created by Ahn on 2022/09/23.
//

#ifndef DS_MYQUEUE_H
#define DS_MYQUEUE_H
class MyQueue {
public:
    MyQueue(int queueCapacity = 5);
    ~MyQueue() {delete [] queue;}
    bool IsEmpty() const;
    int& Front() const;
    int& Rear() const;
    void Push(const int& x);
    void Pop();
private:
    int *queue; // array for stack elements
    int size ; // size of current element
    int capacity; // capacity of queue array
    int front;
    int back;
};



#endif //DS_MYQUEUE_H
