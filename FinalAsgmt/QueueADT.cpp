#include <iostream>
using namespace std;

/* Array로 구현할 시 enqueue와 dequeue가 반복될 때 마다 Array 전체의 위치를 변경해주어야 하는 번거로움이 있는데
 * 이를 해결하기 위해 Linked List로 구현하는 방법이 있고 원형 Queue를 구현하는 방법이 있는데 원형 큐로 구현하였습니다. */

template <typename T>
class QueueADT {
private:
    int length;
    int front; // 큐의 앞에서 리턴 되는 지점의 index
    int rear; // 큐의 뒤에서 삽입 되는 지점의 index
    T* circular_array; // 자료를 저장할 리스트
    int current_size; // 현재 몇개의 item이 들어있는지 확인하기 위한 변수

public:
    QueueADT(int input_size = 5){ // 리스트의 사이즈를 지정할 파라미터로 지정해주지 않을시 기본 값은 5
        length = input_size+1; // 한 칸은 empty와 full을 구분하기 위한 공간이기에 구분을 위해서는 하나의 크기가 더 필요하다.
        circular_array = new T[length]; // 리스트의 크기를 지정
        front = 0; // 초기에는 index 0을 가리킴
        rear = 0; // 초기에는 index 0을 가리킴
        current_size = 0; // 초기에 들어있는 item의 개수는 0
    }
    ~QueueADT(){ // deqructor
        delete[] circular_array; // array의 포인터를 해제
    }

    void enqueue(T); // 큐의 맨 뒤에 값을 삽입
    T dequeue(); // 큐의 맨 앞에 있는 값을 제거하고 리턴
    bool isEmpty(); // 큐가 비어있는지 확인
    int size(); // 큐에 존재하는 아이템의 사이즈를 확인
};

template <typename T> void QueueADT<T>::enqueue(T item) {
    if((rear + 1) % length==front) { // full인 경우
        cout << "큐가 꽉 찬 상태입니다." << endl;
        exit(EXIT_FAILURE);
    }
    else { // 큐가 꽉 차지 않은 경우
        circular_array[rear] = item; // rear가 가리키는 곳에 item을 할당
        rear = (rear + 1) % length; // read는 +1해주어 한 칸 이동하지만 length+1가 length와 같아질경우 length만큼 나눈 것의 나머지를 할당
        current_size++; // item이 들어있는 개수를 1 증가
    }
};

template <typename T> T QueueADT<T>::dequeue() {
    T item_to_be_returned; // 리턴될 아이템
    if(isEmpty()) { // 큐가 비어있는데 dequeue를 사용한 경우
        cout << "비어있는 큐에 dequeue를 할 수 없습니다." << endl;
        exit(EXIT_FAILURE); // 에러 발생
    }
    else { // 정상적인 경우
        item_to_be_returned = circular_array[front]; // 리턴될 아이템을 현재 front가 가리키는 것으로 할당
        front = (front + 1) % length; // front는 한칸 증가시키나 front+1가 length와 같아지는 경우 length로 나눈 것의 나머지를 할당
        current_size--; // 현재 사이즈를 1 감소
    }
    return item_to_be_returned;
}

template <typename T> bool QueueADT<T>::isEmpty() {
    if(rear == front) return true; // rear와 front가 같으면 empty
    else return false; // 그렇지 않은경우 false를 리턴
}

template <typename T> int QueueADT<T>::size() {
    return current_size; // current_size를 리턴
}

int main() {
    QueueADT<int> q(5); // 5개의 값을 담을 수 있도록 지정
    cout << "isEmpty? : " << boolalpha <<  q.isEmpty() << endl; // 비어있는가?
    cout << "size? : " << q.size() << endl; // 사이즈는?
//    cout << "dequeue? : " << q.dequeue() << endl; // 비어있는 큐에 dequeue를 할 수 없어서 에러 발생.
    q.enqueue(10); // 10을 삽입
    cout << "isEmpty? : " << boolalpha << q.isEmpty() << endl; // 비어있는가?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    q.enqueue(20); // 20을 삽입
    q.enqueue(30); // 30을 삽입
    q.enqueue(40); // 40을 삽입
    q.enqueue(50); // 50을 삽입
    cout << "isEmpty? : " << boolalpha << q.isEmpty() << endl; // 비어있는가?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    // 10 - 20 - 30 - 40 - 50
//    q.enqueue(60); // 5개로 꽉찬 상태에서 enqueue를 할 수 없어서 에러 발생
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    q.enqueue(70); // 70을 삽입
    // 20 - 30 - 40 - 50 - 70
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    // 40 - 50 - 70 - empty - empty
    q.enqueue(80); // 80을 삽입
    q.enqueue(90); // 90을 삽입
    // 40 - 50 - 70 - 80 - 90
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    cout << "dequeue? : " << q.dequeue() << endl; // dequeue를 수행하고 리턴된 값은?
    cout << "size? : " << q.size() << endl; // 사이즈는?
    cout << "isEmpty? : " << boolalpha << q.isEmpty() << endl; // 비어있는가?
    // empty
    return 0;
}

