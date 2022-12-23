//
// Created by Ahn on 2022/09/23.
//

#include "0B.MyStack.h"

MyStack::MyStack(int stackCapacity):capacity(stackCapacity) {
    if (capacity < 1)
        throw "MyStack capacity must be > 0";
    stack = new int[capacity];
    top = -1;
}

bool MyStack::IsEmpty() const {
    return top == -1;
}

int &MyStack::Top() const {
    if (IsEmpty())
        throw "MyStack is empty";
    return stack[top];
}

void MyStack::Push(const int &x) { // Add x to the stack.
    if (top == capacity - 1) {
//        ChangeSize1D(stack, capacity, 2*capacity);
//        capacity *= 2;
    }
    // add at stack top
    stack[++top] = x;
}

void MyStack::Pop() {
    if (IsEmpty())
        throw "MyStack is empty. Cannot delete.";
    stack[top--]; // destructor for T
}
