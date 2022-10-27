//
// Created by Ahn on 2022/09/23.
//

#ifndef DS_MYSTACK_H
#define DS_MYSTACK_H

class MyStack {
    public:
        MyStack(int stackCapacity = 10); // constructor
        ~MyStack() {delete [] stack;} // destructor
        bool IsEmpty() const;
        int& Top() const;
        void Push(const int& x);
        void Pop();
    private:
        int *stack; // array for stack elements
        int top; // position of top elements
        int capacity; // capacity of stack array
};


#endif //DS_MYSTACK_H
