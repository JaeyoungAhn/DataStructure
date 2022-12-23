#include <iostream>
using namespace std;

/*
 * Vertex는 Linked List 방식으로 구현하여 어떤 번호의 node가 입력으로 들어와도 동적으로 만들 수 있도록 하였고,
 * Edge는 Vertex안에 Edge의 Linked List를 갖는 방식으로 구현을 하였습니다.
 * (1) - (2)
 *  |
 * (2) - (3) - (1) - (5)
 *  |
 * (3) - (4) - (3)
 *  |
 * (4) - (5)
 *  |
 * (5) - (1) - (2)
 * 위와 같은 구조를 가집니다.
 *
 * addEdge()나 addVertex()시 검사에 통과 한 경우 tail을 이용하여 바로 맨 뒤에 O(1) 시간에 추가합니다.
 */

class Edge { // 간선을 나타내며 시작점은 Vertex가 나타내도록 하여 시작점을 Edge에 나타내지 않음
public:
    Edge *next_edge; // 같은 출발점을 가지는 다음 간선
    int to; // 도착점 정점 번호
    int weight; // 가중치
    Edge(int _to) { // 도착지만 들어온 경우
        to = _to;
        next_edge=nullptr;
    }
    Edge(int _to, int _weight) { // 도착지와 가중치가 같이 들어온 경우
        to = _to;
        weight = _weight;
        next_edge=nullptr;
    }
};

class Vertex { // 정점
public:
    int vertex_number; // 정점 번호이자 Edge의 출발 번호
    Vertex *next_vertex; // 정점을 addVertex()로 추가할때마다 추가될 다른 Vertex를 가리키는 포인터
    Edge *next_edge; // Vertex에 해당하는 도착지 정보가 있는 Edge의 시작점을 담는 포인터
    Edge *next_edge_tail; // Vertex에 해당하는 도착지 정보가 있는 Edge의 마지막 끝점을 담는 포인터

    Vertex(int num) { // 정점 번호
        vertex_number = num;
        next_vertex=nullptr;
        next_edge=nullptr;
        next_edge_tail=nullptr;
    }
};


class GraphADT{ // 그래프 클래스
public:
    int vertex_size; // 몇개의 정점을 담고있는지를 기록할 변수
    Vertex *head_init; // 제일 시작 정점을 가리키는 포인터
    Vertex *tail_init; // 시작 정점부터 이어져 오는 가장 마지막 정점을 가리키는 포인터
    GraphADT(){  // constructor
        head_init=nullptr;
        tail_init=nullptr;
        vertex_size=0;
    }
    ~GraphADT(){  // destructor
    }

    void addVertex(int); // int 값에 해당하는 정점 번호를 동적으로 추가
    void addEdge(int, int); // int에서 int로 이어져있는 Edge를 추가
    void addEdge(int, int, int); // int에서 int로 int만큼 가중치를 가지는 Edge를 추가
    int getVertex(Vertex *); // 특정 Vertex를 가리키는 key가 되는 것이 파라미터로 들어올 경우 선형탐색(O(N)) 없이 O(1)로 즉각적으로 가리킴
    int* getVertices(); // 정점들을 담은 리스트를 리턴
    bool hasVert(int); // int 번호의 정점이 존재하는지 검사
    bool hasEdge(int, int); // int에서 int로 이어져있는 Edge가 존재하는지 검사
};

void GraphADT::addVertex(int num) {
    if(hasVert(num)) { // 이미 추가되어있는 vertex에 또 추가를 하는 경우 에러 발생
        cout << "추가할 vertex가 이미 추가되어있습니다." << endl;
        exit(EXIT_FAILURE);
    }
    Vertex *new_vertex = new Vertex(num); // 새로운 vertex 객체
    vertex_size++; // 관리하는 vertex의 수를 1 증가
    if(head_init == nullptr) { // graph 객체가 가지는 head_init은 관리하는 vertex의 처음 위치를 가리키는데 만약 이가 비어있는 경우
        head_init = new_vertex;
        tail_init = new_vertex;
        /* head_init과 tail_init 모두 최초 만들어진 vertex를 가리키도록함 */
    }
    else { // 이미 한번이라도 vertex가 만들어진 경우
        tail_init->next_vertex = new_vertex; // tail_init의 다음을 새로 들어온 vertex를 가리키도록 함
        tail_init = tail_init->next_vertex; // 기존 tail_init 대신 새로들어온 vertex의 위치를 새로운 tail_init으로 지정
    }
}

void GraphADT::addEdge(int _from, int _to) { // edge를 추가하려는데 weight가 없는 경우
    if(!hasVert(_from)) { // edge를 추가하려는데 _from에 해당하는 vertex가 만들어져 있지 않은 경우 에러 발생
        cout << "추가하려는 edge의 from에 해당하는 vertex가 없습니다." << endl;
        exit(EXIT_FAILURE);
    }
    if(hasEdge(_from, _to)) { // edge를 추가하려는데 이미 _from에서 _to로 가는 edge가 만들어져 있는 경우 에러 발생
        cout << "추가하려는 edge가 이미 존재합니다." << endl;
        exit(EXIT_FAILURE);
    }

    Vertex *vertex_head_init = head_init; // graph가 관리하는 처음 vertex를 가리키는 head_init을 불러옴
    while(vertex_head_init!=nullptr) { // 반복
        if(vertex_head_init->vertex_number == _from) // 추가하려는 edge의 _from에 해당하는 vertex를 찾은 경우
            break; // 포인터 주소를 유지한채로 break
        else vertex_head_init = vertex_head_init->next_vertex;  // _from에 해당하는 것을 찾지 못한경우 다음 vertex로 포인터를 이동
    }

    Vertex *vertex_head = vertex_head_init; // 변수명을 알기 쉽게 하기 위해 동일한 주소를 새로운 명칭으로 받음
    Edge *new_edge = new Edge(_to); // _to를 가지는 새로 추가할 edge
    if(vertex_head->next_edge == nullptr) { // edge가 해당 vertex에 최초로 추가되는 경우
        vertex_head->next_edge = new_edge;
        vertex_head->next_edge_tail = new_edge;
        /* head와 tail을 나타내는 두 개의 변수에 각각 동일한 new_edge 객체를 할당 */
    }
    else { // 한번이라도 추가된 적이 있는 경우
        Edge *tmp = vertex_head->next_edge_tail; // 해당 vertex_head의 tail에 해당하는 edge를 바로 가리킴
        tmp->next_edge = new_edge; // 해당 edge의 tail의 다음 주소에 새 edge 객체의 주소를 할당
        vertex_head->next_edge_tail = tmp->next_edge; // 기존 tail 대신 새 edge 객체의 주소가 새 tail이 되도록 할당
    }
}

void GraphADT::addEdge(int _from, int _to, int _weight) { // edge를 추가하려는데 weight가 있는 경우
    /* 이하 동일 */
    if(!hasVert(_from)) {
        cout << "추가하려는 edge의 from에 해당하는 vertex가 없습니다." << endl;
        exit(EXIT_FAILURE);
    }
    if(hasEdge(_from, _to)) {
        cout << "추가하려는 edge가 이미 존재합니다." << endl;
        exit(EXIT_FAILURE);
    }

    Vertex *vertex_head_init = head_init;
    while(vertex_head_init!=nullptr) {
        if(vertex_head_init->vertex_number == _from)
            break;
        else vertex_head_init = vertex_head_init->next_vertex;
    }

    Vertex *vertex_head = vertex_head_init;
    Edge *new_edge = new Edge(_to, _weight);
    if(vertex_head->next_edge == nullptr) {
        vertex_head->next_edge = new_edge;
        vertex_head->next_edge_tail = new_edge;
    }
    else {
        Edge *tmp = vertex_head->next_edge_tail;
        tmp->next_edge = new_edge;
        vertex_head->next_edge_tail = tmp->next_edge;
    }
}

int GraphADT::getVertex(Vertex* vertKey) { // 특정 vertex를 가리키는 vertKey가 파라미터로 들어옴
    return vertKey->vertex_number; // 해당 vertex의 정점 번호를 리턴
}

int* GraphADT::getVertices() { // 관리중인 모든 vertex들을 배열로 리턴
    int *result_list = new int[vertex_size]; // vertex_size 길이의 리스트를 생성
    int index = 0;
    Vertex *head = head_init;
    while(head!=nullptr) { // head를 next_vertex를 가리켜가며 배열에 해당 head의 정점 번호를 할당하고 index를 증가
        result_list[index++] = head->vertex_number;
        head = head->next_vertex;
    }
    return result_list; // 배열 주소를 리턴
}

bool GraphADT::hasVert(int num) {
    bool result = false;
    if(vertex_size == 0) return false; // vertex의 size가 0이면 어떤 경우든 vertex를 가지지 않으므로 false
    else {
        Vertex *head = head_init;
        while(head!=nullptr) {
            if(head->vertex_number == num) { // head를 돌며 찾고있는 num와 동일한 정점번호를 가지는 head가 나오는 경우
                result = true; // true값을 리턴할 result값에 true를 대입
                break;
            }
            head = head->next_vertex;
        }
    }
    return result; // true 또는 false를 리턴
}

bool GraphADT::hasEdge(int _from, int _to) {
    if(vertex_size == 0) return false; // vertex의 size가 0이면 어떤 경우든 edge를 가지지 않으므로 false
    if(!hasVert(_from)) return false; // _from에 해당하는 vertex를 가지지 않으면 edge도 없으므로 false
    Vertex *head = head_init;
    Vertex *from_vertex;
    while(head!=nullptr) { // 이 위치까지 온경우 _from에 해당하는 번호는 반드시 존재
        if(head->vertex_number == _from) { // head를 돌며 _from과 같은 정점 번호를 가진 head를 발견한 경우
            from_vertex = head; // 해당 주소를 새로운 from_vertex로 받음
            break;
        }
        else
            head = head->next_vertex;
    }
    if(from_vertex == nullptr) return false; // 만일 어떤 정점도 가리키지 않는 경우 false
    Edge *to_edge = from_vertex->next_edge; // 해당 vertex의 맨 앞 edge를 받음
    while(to_edge != nullptr) { // edge를 돌며
        if(to_edge->to == _to) return true; // _to와 동일한 값을 가지는 to_edge의 to 변수가 존재하는 경우 true를 리턴
        else to_edge = to_edge->next_edge;
    }
    return false; // 이 곳에 도달하면 false를 리턴
}



int main() {
    GraphADT graph;
//    graph.addEdge(1, 2); // vertex를 만들기 전에 edge를 추가하는 경우
//    graph.addEdge(2, 3, 30); // vertex를 만들기 전에 edge를 추가하는 경우
//    cout << boolalpha << graph.hasVert(2) << endl; // 아무것도 추가하지 않은 상태에서 조사하므로 false를 리턴
//    cout << boolalpha << graph.hasEdge(1,2) << endl; // 아무것도 추가하지 않은 상태에서 조사하므로 false를 리턴

    graph.addVertex(1); // 1번 정점 추가
//    graph.addVertex(1); // 이미 존재하는 노드를 추가하는 경우
    graph.addVertex(2); // 2번 정점 추가
    graph.addVertex(3); // 3번 정점 추가
    graph.addVertex(4); // 4번 정점 추가
    graph.addVertex(5); // 5번 정점 추가
    graph.addVertex(6); // 6번 정점 추가
    graph.addVertex(7); // 7번 정점 추가
    graph.addVertex(-1); // -1번 정점 추가

    /* 시작 정점, 도착 정점으로 객체화 한 edge */
    graph.addEdge(2,1);
    graph.addEdge(2,3);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(5,1);
    graph.addEdge(7, 7);
    graph.addEdge(7, 6);

    /* 시작 정점, 도착 정점, 가중치로 객체화 한 edge */
    graph.addEdge(1,2, 10);
    graph.addEdge(3,2, 20);
    graph.addEdge(4,3, 30);
    graph.addEdge(5,4, 40);
    graph.addEdge(1,5, 50);
    graph.addEdge(6, 7, 70);
//    graph.addEdge(6,7, 30); // 이미 존재하는 vertex를 동일하게 추가하는 경우

    cout << "해당 정점 가지고 있는가?: " << boolalpha << graph.hasVert(1) << endl; // 1번 정점을 가지고 있는가?

    /* 시작 정점, 도착 정점으로 객체화 한 edge에 대해 조사 */
    cout << "해당 edge를 가지고 있는가?: " << boolalpha << graph.hasEdge(8,8) << endl; // 없는(X) edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(1,11) << endl; // 없는(X) edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(2,1) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(2,3) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(3,4) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(4,5) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(5,1) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(7,7) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(7,6) << endl; // 있는 edge

    /* 시작 정점, 도착 정점, 가중치로 객체화 한 edge에 대해 조사 */
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(1,2) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(3,2) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(4,3) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(5,4) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(1,5) << endl; // 있는 edge
    cout << "해당 edge를 가지고 있는가?: "  << boolalpha << graph.hasEdge(6,7) << endl; // 있는 edge

    int* result_list = graph.getVertices(); // vertex를 담은 리스트를 리턴 받음
    for(int i=0; i<graph.vertex_size; i++) { // vertex 갯수만큼 반복하며 vertex들을 출력함
        if(i==graph.vertex_size-1)
            cout << result_list[i] << endl;
        else cout << result_list[i] << " -> ";
    } // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> -1와 같이 -1가 제일 마지막에 만들어졌기때문에 순서에 그대로 반영

    Vertex* vertKey = graph.head_init; // 1 - 2 - 3 -.. 순의 정점에서 1을 가리킴
    for(int i=0; i<2; i++) { // 2번 증가시켜서 3을 가리킴
        vertKey = vertKey->next_vertex; // 3을 가리키는 것을 key로 설정 함
    }

    cout << graph.getVertex(vertKey) << endl; // 3을 담고있는 vertex의 위치를 키로 주어서 O(1) 시간 안에 vertex를 즉시 가리킴
    return 0;
}

