//
// Created by Ahn on 2022/11/18.
//
#include "HeapNode.h"
#define MAX_ELEMENT 200
class MaxHeap {
    HeapNode node[MAX_ELEMENT]; // 요소의 배열
    int size; // 힙의 현재 요소의 개수
public:
    MaxHeap( ) : size(0) { }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size == MAX_ELEMENT-1; }

    HeapNode& getParent(int i){ return node[i/2]; } // 부모 노드
    HeapNode& getLeft(int i){ return node[i*2]; } // 왼쪽 자식 노드
    HeapNode& getRight(int i){ return node[i*2+1]; } // 오른쪽 자식 노드

    void insert(int key) {
        if(isFull()) return; // 힙이 가득 찬 경우
        int i = ++size; // 증가된 힙 크기 위치에서 시작

        // 트리를 거슬러 올라가면서 부모 노듸와 비교하는 과정
        while(i!=1//루트가 아니고
          && key>getParent(i).getKey()){ // 부모 노드보다 키 값이 크면
            node[i] = getParent(i); // 부모를 자신 노드로 끌어내림
            i /= 2; // 한 레벨 위로 상승
        }
        node[i].setKey(key);
    } // 삽입 함수
    HeapNode remove() {
        if( isEmpty() ) return NULL;
        HeapNode item = node[1]; // 루트노드(꺼낼 요소)
        HeapNode last = node[size--]; // 힙의 마지막노드
        int parent = 1;             // 마지막 노드의 위치를 루트로 생각함
        int child = 2;              // 루트의 왼쪽 자식 위치
        while( child <= size ){     // 힙 트리를 벗어나지 않는 동안
            // 현재 노드의 자식 노드 중 더 큰 자식노드를 찾음
            if( child < size
            && getLeft(parent).getKey() < getRight(parent).getKey())
                child++;            // child: 더 큰 자식의 노드의 인덱스
            // 마지막 노드가 더 큰 자식보다 크면 ==> 이동 완료
            if( last.getKey() >= node[chlid].getKey() ) break;

            // 아니면 ==> 한 단계 아래로 이동
            node[parent] = node[child];
            parent = child;
            child *= 2;
        }
        node[parent] = last; // 마지막 노드를 최종 위치에 저장
        return item; // 루트 노드 반환
    } //  삭제 함수

    HeapNode find() { return node[1]; }


};
