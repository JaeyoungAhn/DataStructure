#include "MaxHeap.h

void main() {
    MaxHeap heap;
    // 삽입 테스트
    heap.insert(10); heap.insert(5);
    heap.insert(30); heap.insert(8);
    heap.insert(9); heap.insert(3);
    heap.insert(7);
    heap.display(); // 상태 출력
    // 삭제 테스트
    heap.remove(); heap.display();
    heap.remove(); heap.display();
    printf("\n");


}