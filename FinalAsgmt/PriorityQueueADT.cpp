#include <iostream>
using namespace std;

/*
 * 1차원 배열을 처음 일정 개수 생성하고, 계속 삽입이 되어서 길이를 초과하게 되면 2배 길이를 가지는 새로운 배열을 복사하여 배정하고,
 * insert를 하는 경우 unordered 상태로 우선적으로 삽입하고(O(1)), removeMin을 할 때 선형 탐색(O(N))으로 최솟 값을 찾아서 리턴하고
 * 배열이 삭제되면 삭제된 값 뒤의 값들을 한 칸 앞으로 이동 시킵니다.
 */

template <typename T>
class PriorityQueueADT {
public:
    T* list; // 원소들을 담을 리스트
    int currentSize; // 현재 들어온 원소의 개수
    int length; // 리스트 자체의 길이
    PriorityQueueADT(int start_length = 5) { // constructor: 아무 파라미터가 안들어오면 기본 5개의 길이
        list = new T[start_length]; // 5개의 원소를 가질 수 있는 리스트 생성
        length = start_length; // 리스트 길이는 5
        currentSize = 0; // 현재 들어온 원소의 개수는 0개
    }
    ~PriorityQueueADT(){ } // destructor

    void insert(T); // T를 list의 currentSize번째 index에 삽입
    T removeMin(); // 선형탐색하여 최솟값을 리턴하고 값의 위치를 조정
    T min(); // 선형탐색하여 최솟값을 리턴
    int size(); // 현재 들어온 원소의 개수를 리턴
    bool  isEmpty(); // 비어있는지 아닌지에 대한 bool 값을 리턴
    int findMinInd(); // 최솟값을 가지는 index를 리턴


};

template <typename T> int PriorityQueueADT<T>::findMinInd() {
    if(currentSize == 0) { // 비어있는데 최솟값을 찾는 작업이 들어올 경우
        cout << "비어있는 큐에서는 실행할 수 없는 작업입니다." << endl;
        exit(EXIT_FAILURE);
    }
    int minIndex = 0; // 0번째 인덱스를 먼저 대입
    T minValue = list[0]; // 0번째 인덱스의 값을 minValue로 먼저 둠
    for(int i=1; i<currentSize; i++) { // 1번째 index부터 마지막까지
        if(minValue>list[i]) { // 현재 인덱스보다 더 작은 값이 나오는 경우
            minValue = list[i]; // 가장 작은 값을 새로 할당
            minIndex = i; // 가장 작은 값을 가지는 인덱스를 새로 할당
        }
    }

    return minIndex; // 가장 작은 값을 가지는 인덱스를 리턴

}

template <typename T> void PriorityQueueADT<T>::insert(T val) {
    if(currentSize == length) { // 만약 리스트의 원소가 꽉찼는데 또 추가하는 경우
        length*=2; // 리스트 전체 길이를 2배
        T* tmpList = new T[length]; // 임시 리스트를 만들고 길이는 기존의 2배
        for(int i=0; i<currentSize; i++) // 기존 리스트를 더 큰 임시리스트에 옮겨 담음
            tmpList[i] = list[i];
        list = tmpList; // 기존 리스트의 주소가 새로운 리스트의 주소를 가리키도록 할당
    }
    list[currentSize++] = val; // 원소가 꽉차지 않은경우 현재 currentSize을 증가시킨 만큼의 index에 값을 할당
}

template <typename T> T PriorityQueueADT<T>::removeMin() {
    int minIndex = findMinInd(); // 최솟값을 가진 인덱스를 리턴
    T returnVal = list[minIndex]; // 최솟값을 담음
    if(minIndex != currentSize-1) { // 최솟값이 마지막 값이 아닌경우
        for(int i=minIndex; i<currentSize-1; i++) { // 앞으로 한칸씩 옮겨 담음
            list[i] = list[i+1];
        }
    }
    currentSize--; // 사이즈 감소
    return returnVal; // 최솟값을 리턴

}

template <typename T> T PriorityQueueADT<T>::min() {
    return list[findMinInd()]; // 최솟값의 인덱스를 이용해서 최솟값을 리턴
}

template <typename T> int PriorityQueueADT<T>::size() {
    return currentSize; // 현재 사이즈
}

template <typename T> bool PriorityQueueADT<T>::isEmpty() {
    return currentSize == 0; // 현재 사이즈가 0개이면 비어있음
}

int main() {
    PriorityQueueADT<int> pq;
//    pq.removeMin(); // 비어있는 경우에 호출
//    pq.min(); // 비어 있는 경우에 호출
    cout << "큐에 들어있는 원소의 수는?: " << pq.size() << endl; // 사이즈는 0
    cout << "비어있는가?: " << boolalpha << pq.isEmpty() << endl; // 비어있음

    pq.insert(1); // 1을 삽입

    cout << "비어있는가?: " << boolalpha << pq.isEmpty() << endl; // 비어있지 않음
    cout << "큐에 들어있는 원소의 수는?: " << pq.size() << endl; // 사이즈는 1
    cout << "현재 가장 최솟값 조희: " << pq.min() << endl; // 최솟값은 1

    pq.insert(3); // 3 삽입
    pq.insert(5); // 5 삽입
    pq.insert(7); // 7 삽입
    pq.insert(2); // 2 삽입
    pq.insert(4); // 4 삽입
    pq.insert(12); // 12 삽입1
    pq.insert(6); // 6 삽입

    /* 1 - 3 - 5 - 7 - 2 - 4 - 12 - 6 */

    cout << "비어있는가?: " << boolalpha << pq.isEmpty() << endl; // 비어있지 않음
    cout << "큐에 들어있는 원소의 수는?: " << pq.size() << endl; // 사이즈는 8
    cout << "현재 가장 최솟값 조희: " << pq.min() << endl; // 최솟값은 1

    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 1 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 2 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 3 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 4 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 5 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 6 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 7 리턴
    cout << "최솟값 제거 후 반환 값: " << pq.removeMin() << endl; // 12 리턴

    cout << "비어있는가?: " << boolalpha << pq.isEmpty() << endl; // 비어있음
    cout << "큐에 들어있는 원소의 수는?: " << pq.size() << endl; // 사이즈는 0

    return 0;
}

