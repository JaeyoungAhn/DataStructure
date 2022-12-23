#include <iostream>
using namespace std;

/* 문제에서 요구하는 것을 보면, 직접 특정 pos에 접근하여 값을 변경하는 경우는
 * insert의 경우 한가지 밖에 없으며, 나머지의 경우는 item을 모두 찾아야 하는 작업을 요구하고
 * 만약 이를 Array로 구현한다고 하더라도 결국 item을 찾기위해서는 처음부터 끝의 값을 탐색해야 하고
 * 또한 어떤 값을 insert()하는 경우에도 Array의 insert된 포지션 주변에서 한 칸씩 밀어주는 이동 작업이 발생하므로
 * 시간 소요가 많이 걸릴 것으로 예상됩니다. 따라서 Linked List를 구현하면 비교적 빠른 속도로 연산이 가능할 것이라고 판단하였습니다.
 */

template <typename T>
struct Node { // 리스트의 노드
public:
    T value; // 특정 데이터 타입의 값
    struct Node<T> *next; // 다음을 가리키는 주소이며 초기값은 nullptr
};

template <typename T>
class ListADT {
private:
    Node<T> *head; // 리스트의 왼쪽 시작 지점
    Node<T> *tail; // 리스트이 왼쪽 끝나는 지점
    int length; // 리스트의 길이
public:
    ListADT():head(nullptr),tail(nullptr){
        length = 0; // 초기 길이를 0으로 설정
    } // constructor
    ~ListADT(){} // destructor

    T remove(T item) { // 특정 값을 지우기
        Node<T> *ptr = head; // 탐색을 시작할 head
        Node<T> *tmp = ptr; // 바로 직전 값을 임시 저장 해놓을 포인터
        T returned_val; // 삭제된 것을 리턴(optional)

        while(ptr != nullptr) {
            if(ptr->value == item) // 아이템을 찾은 경우
                break; // while문을 빠져나온다.
            else {
                tmp = ptr; // ptr가 가리키는 것보다 항상 하나 전을 가리키는 변수
                ptr = ptr->next; // 다음 포인터로 이동한다.
            }
        }

//        if(ptr->value != item ) { // 리스트는 반드시 삭제할 값을 가진다고 assume 했으므로 불필요한 코드
//            cout << "찾을 수 없는 노드 입니다" << endl;
//            return;
//        }

        if(ptr == tmp) // head여서 둘다 두 값 모두 같은 경우
            head = tmp->next;
        else if(ptr->next == nullptr)// tail인 경우
            tail = tmp;

        returned_val = ptr->value; // 리턴할 삭제된 값
        tmp->next = ptr->next; // 삭제할 노드를 제외하고 연결
        length--; // 사이즈를 줄임
        delete ptr; // 포인터를 해제한다.
        return returned_val; // 삭제된 값을 리턴한다.
    }

    bool search(T item) { // list에 value가 존재하면 true를 그렇지 않으면 false를 리턴
        Node<T> *ptr = head; // 탐색할 처음을 head로 지정
        while(ptr != nullptr) { // ptr가 nullptr가 아닌 동안
            if(ptr->value == item) return true; // 원하는 값을 찾은 경우
            ptr = ptr->next; // 다음 포인터로 이동
        }
        return false; // while문을 전부 탐색했지만 원하는 값을 찾지 못한 경우
    }

    bool isEmpty() { // List가 비어있는지 확인
        return length == 0; // 사이즈가 0인 경우의 true, false를 리턴
    }

    int size() { // 리스트의 크기를 반환
        return length; // length 변수 값 자체를 리턴
    }

    void append(T item) { // 맨 오른쪽 끝 부분에 노드를 추가
        Node<T> *node = new Node<T>; // 노드를 객체화
        node->value = item; // 파라미터 입력값이 새 객체의 값이 됨
        node->next = nullptr; // 초기 생성시 노드의 다음 주소는 빈 주소
        length++; // 리스트의 길이를 1 증가

        if(head == nullptr) { // 만약 초기 head가 null을 가리키는 경우
            head = node;
            tail = node;
            /* head와 tail을 같도록 설정 */
        }
        else { // head가 nullptr가 아닌 경우
            tail->next = node;
            tail = tail->next;
            /* 기존 tail의 다음이 새 객체를 가리키도록 하고,
             * tail 변수는 새 객체를 가리키도록 한다. */
        }
    }

    void insert(int pos, T item) {
        Node<T> *node = new Node<T>; // 노드를 객체화
        node->value = item; // 파라미터 입력값이 새 객체의 값이 됨
        node->next = nullptr; // 초기 생성시 노드의 다음 주소는 빈 주소

        Node<T> *ptr = head;
        Node<T> *tmp = new Node<T>; // 해당 pos의 Node 보다 한 단계 이전 Node


        /* enough existing items to have position pos라고 assume 되었으므로
         * length를 기준으로 유효한 인덱스가 들어왔는지 검사하는 코드를 생략 */

        for(int i=0; i<pos; i++) {
            tmp = ptr;
            ptr = ptr->next;
        }

        if(pos==0) { // 인덱스가 맨 왼쪽인 경우
            node->next = head;
            head = node;
        }
        else { // 나머지 경우
            node->next = ptr;
            tmp->next = node;
        }
        length++; // 사이즈 증가
    }

    T pop() { // last 값을 삭제

//        if(isEmpty()) { // 리스트가 비어있는지 확인하는 코드이나 list가 최소 하나의 item이 있도록 assume되었으므로 불필요한 코드
//            cout << "리스트가 비어있어 pop 연산을 수행할 수 없습니다.\n";
//            return;
//        }

        Node<T> *ptr = head;
        Node<T> *tmp = new Node<T>;
        T value_to_be_returned;

        /* 마지막 값까지 이동 */
        while(ptr->next != nullptr) { // 양방향 linked list였다면 불필요한 연산
            tmp = ptr;
            ptr = ptr->next;
        }

        value_to_be_returned = ptr->value;
        tail = tmp;
        tail->next = nullptr;
        delete ptr;
        length--;
        return value_to_be_returned;
    }
};

int main() {
    ListADT<int> list;
    cout << "size?: " << list.size() << endl; // 사이즈
    cout << "isEmpty?: " << boolalpha << list.isEmpty() << endl; // 비어있는지 확인
    list.append(1); // 1추가
    list.append(2); // 2추가
    list.append(3); // 3추가
    list.append(4); // 4추가
    list.append(5); // 5추가
    // 1-2-3-4-5
    cout << "search 4?: " << boolalpha << list.search(4) << endl; // 4를 찾을 수 있는가?
    cout << "search 99? " << boolalpha << list.search(99) << endl; // 99를 찾을 수 있는가?
    cout << "isEmpty? " << boolalpha << list.isEmpty() << endl; // 비어있는가?
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    // 1-2-3
    cout << "removed item?: " << list.remove(1) << endl; // removed한 아이템은 무엇인가?
    // 2-3
    cout << "search 1?: " << boolalpha << list.search(1) << endl; // 1을 찾을 수 있는가?
    list.insert(0,30); // 0번 index에 30을 삽입
    // 30-2-3
    list.append(10); // 맨 뒤에 10을 추가
    // 30-2-3-10
    list.insert(2,20); // 2번 index에 20을 삽입
    // 30-2-20-3-10
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    cout << "size? " << list.size() << endl; // size는?
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    cout << "size? " << list.size() << endl; // size는?
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    cout << "size? " << list.size() << endl; // size는?
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    cout << "size? " << list.size() << endl; // size는?
    cout << "popped item?: " << list.pop() << endl; // pop한 아이템은 무엇인가?
    cout << "size? " << list.size() << endl; // size는?
    // empty
    return 0;
}

