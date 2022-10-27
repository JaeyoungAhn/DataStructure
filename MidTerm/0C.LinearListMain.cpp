#include <iostream>
#include "0C.LinearList.h"
#include "0B.MyStack.h"
#include "0E.MyQueue.h"
#include <list>
using namespace std;
int main() {
//    LinearList list();
//    LinearList list;

//    LinearList * list = new LinearList();
//
//    cout << list->isEmpty() << endl;
//    cout << list->length() << endl;
//    list->Insert(0,1);
//    list->Insert(0,2);
//    list->Insert(0,3);
//    list->Insert(0,4);
//    list->Insert(3,5);
//    for(int i=0; i<5; i++)
//        cout << list->Retrieve(i) << " ";
//    cout << endl;
//    cout << list->Delete(2) << endl;
//    for(int i=0; i<4; i++)
//        cout << list->Retrieve(i) << " ";x
//    delete list;
//    return 0;

//
//
//    cout << "=====Stack!!!=====\n";
//    MyStack st(10);
//    st.Push(123); st.Push(456);  st.Push(789);
//
//    cout << st.Top() << endl; st.Pop();
//    cout << st.Top() << endl; st.Pop();
//    cout << st.Top() << endl; st.Pop();
//
//    cout << "======Queue!!!=====" << endl;
//    MyQueue q(5);
//    q.Push(123); q.Push(456);  q.Push(789);  q.Push(1011); q.Push(1213); q.Push(1415);
//
//    cout << q.Front() << endl; cout << q.Rear() << endl; q.Pop();
//    cout << q.Front() << endl; cout << q.Rear() << endl; q.Pop();
//    cout << q.Front() << endl; cout << q.Rear() << endl;
//
//    q.Push(9999);
//    cout << q.Front() << endl; cout << q.Rear() << endl; q.Pop();
//
//    if(!q.IsEmpty()) cout << q.Front() << " ";
//
//    return 0;
    list<int> mylist(10);
    mylist.push_back(10);
    mylist.push_back(20);
    mylist.push_back(30);
    mylist.push_back(40);


    list<int>::iterator it;
    for(it=mylist.begin();it!=mylist.end();it++)
    {
        cout << *it << endl;
    }

}


