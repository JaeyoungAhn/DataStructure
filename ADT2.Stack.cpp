#include <iostream>
using namespace std;

/* 구현의 편의상 스택의 capacity를 지정하는 방식으로 구현 하였습니다. */

template <typename T>
class StackADT {
private:
    int *stack_array; // 스택 배열을 담을 포인터
    int top; // 스택의 제일 끝의 index를 나타냄
    int capacity; // 스택이 최대로 담을 수 있는 용량을 나타냄
public:
    StackADT(int size = 5){ // constructor이고 size가 파라미터로 들어오지 않을 시 기본 5
        stack_array = new T[size]; // 스택을 저장할 배열을 생성
        capacity = size; // 용량
        top = -1; // 초기는 0개의 값을 가리킨다.
    }
    ~StackADT(){  // destructor
        delete[] stack_array; // 배열 전체를 해제해준다.
    }

    void push(T); // 스택에 item을 삽입
    T pop(); // 스택의 끝에 있는 값을 제거하면서 리턴
    T peek(); // 스택의 끝에 있는 값을 확인
    bool isEmpty(); // 스택이 비어있는지 확인
    int size(); // 스택의 현재 들어와 있는 item의 개수를 확인
};

template <typename T> void StackADT<T>::push(T item) {
    if(size() == capacity) {
        cout << "스택이 꽉차 push를 할 수 없습니다." << endl;
        exit(EXIT_FAILURE);
    }

    stack_array[++top] = item;
};

template <typename T> T StackADT<T>::pop() {
    if(isEmpty()) {
        cout << "stack이 비어있어서 pop할 수 없습니다." << endl;
        exit(EXIT_FAILURE);
    }

    return stack_array[top--];
}

template <typename T> T StackADT<T>::peek() {
    if (!isEmpty()) return stack_array[top]; // empty가 아닌 경우 peek 가능
    else {
        cout << "비어있는 stack을 peek 할 수 없습니다." << endl;
        exit(EXIT_FAILURE); // empty인 경우 에러 발생
    }
}

template <typename T> bool StackADT<T>::isEmpty() {
    return top == -1; // top이 초기 -1인 경우 비어있는 경우
}

template <typename T> int StackADT<T>::size() {
    return top+1;
}

int main() {
    StackADT<int> st(5);
    cout << "isEmpty? : " << boolalpha <<  st.isEmpty() << endl; // 스택이 비어있는가?
    cout << "size? : " << st.size() << endl; // 현재 들어온 아이템들의 크기는?
//    cout << "peek?: " << st.peek() << endl; // 비어있는 것을 peek 할 시 에러 발생
//    cout << "pop? : " << st.pop() << endl; // 비어있는 것을 pop 할 시 에러 발생
    st.push(10); // 10을 스택에 삽입
    cout << "isEmpty? : " << boolalpha << st.isEmpty() << endl;
    cout << "size? : " << st.size() << endl;
    st.push(20); // 20을 스택에 삽입
    st.push(30); // 30을 스택에 삽입
    st.push(40); // 40을 스택에 삽입
    st.push(50); // 50을 스택에 삽입
//    st.push(60); // 스택 사이즈 5로 꽉 찬 경우 삽입하여 에러 발생
    // 10 < 20 < 30 < 40 < 50
    cout << "isEmpty? : " << boolalpha << st.isEmpty() << endl; // 스택이 비어있는가?
    cout << "size? : " << st.size() << endl; // 현재 들어온 아이템들의 크기는?
    cout << "peek? : " << st.peek() << endl; // top에 있는 아이템은?
    cout << "pop? " << st.pop() << endl; // pop을 수행하고 나온 아이템은?
    cout << "peek? : " << st.peek() << endl; // top에 있는 아이템은?
    cout << "pop? " << st.pop() << endl; // pop을 수행하고 나온 아이템은?
    cout << "peek? : " << st.peek() << endl; // top에 있는 아이템은?
    cout << "pop? " << st.pop() << endl; // pop을 수행하고 나온 아이템은?
    cout << "peek? : " << st.peek() << endl; // top에 있는 아이템은?
    cout << "pop? " << st.pop() << endl; // pop을 수행하고 나온 아이템은?
    cout << "isEmpty? : " << boolalpha << st.isEmpty() << endl;
    cout << "size? : " << st.size() << endl; // 현재 들어온 아이템들의 크기는?
    cout << "peek? : " << st.peek() << endl; // top에 있는 아이템은?
    cout << "pop? " << st.pop() << endl; // pop을 수행하고 나온 아이템은?
    cout << "isEmpty? : " << boolalpha << st.isEmpty() << endl;
    cout << "size? : " << st.size() << endl; // 현재 들어온 아이템들의 크기는?
    // empty
    return 0;
}

