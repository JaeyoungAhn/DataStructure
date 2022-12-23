#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

class Graph {
public:
    int n;
    // 인접 정점
    // first: 정점, second: 가중치
    vector<pii>* adj;

    Graph(int n) {
        this->n = n;
        adj = new vector<pii>[n+1];
    }

    // 간선 추가
    void insertEdge(int u, int v, int w) {
        this->adj[u].push_back(make_pair(v, w));
    }
};

class Compare {
public:
    // 우선순위 큐를 위한 비교 함수
    bool operator() (pii a, pii b) {
        return a.second > b.second;
    }
};

vector<int> dijkstra(Graph* g, int start) {
    // 최단 거리가 발견되면 true
    vector<bool> found(g->n+1, false);

    // 해당 정점까지의 거리 (default : 무한)
    vector<int> distance(g->n+1, INT_MAX);

    // 최단거리가 업데이트 될때 바로 이전에 방문하게 되는 정점
    vector<int> from(g->n+1, -1);

    // 가장 가까운 정점을 찾기 위한 우선순위 큐
    // first: 정점 번호, second: 정점까지의 거리
    priority_queue<pii, vector<pii>, Compare> pq;

    // 출발지의 최단거리 발견
    found[start] = true;
    // 출발지까지 거리 0
    distance[start] = 0;

    // 우선순위 큐에 넣는다.
    pq.push(make_pair(start, 0));

    //for (int i = 0; i < g->n; i++) {
    while(!pq.empty()) {
        // 가장 가까운 정점을 우선순위 큐에서 꺼낸다.
        int u = pq.top().first;
        pq.pop();

        // 최단거리 발견
        found[u] = true;
        for (int j = 0; j < g->adj[u].size(); j++) {
            // 정점 u의 인접정점의 최단거리 업데이트
            pii v = g->adj[u][j];

            if (!found[v.first]) {
                if (distance[u] + v.second < distance[v.first]) {
                    distance[v.first] = distance[u] + v.second;
                    from[v.first] = u;

                    // 우선순위 큐에 추가
                    pq.push(make_pair(v.first, distance[v.first]));
                }
            }
        }
    }

    return distance;
}

// from[n]에서 목적지까지의 정점을 재귀적으로 출력한다.
void trace_path(int s, int e, vector<int> from) {
    // 기저 조건 : 시작점과 목적지가 같은 경우
    if (from[e] == s) {
        cout << s << " ";
        return;
    }

    // 재귀호출을 통해 정점 e전의 정점에 대한 경로를 출력한다..
    trace_path(s, from[e], from);

    // 최단경로에서 정점 e 바로 이전의 정점를 화면에 출력한다.
    cout << from[e] << " ";
}

// 마지막 목적지를 간편하게 화면의 출력하기 위해 함수 분리
void print_path(int s, int e, vector<int> from) {
    // 위의 trace_path를 호출하여 최단 경로를 출력한후,
    if ( s!=e && from[e] == -1 ) {
        cout << "-1";
        return;
    }

    if(s!=e) {
        trace_path(s, e, from);
    }
    // 목적지의 정점 번호도 출력한다.
    cout << e;
}


int main(void) {
    int n, s, e;
    int value;
    cin >> n >> s >> e;
    Graph* g = new Graph(n);
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> value;
            g->insertEdge(i,j,value);
        }
    }

    // 최단 경로를 구한다.
    auto distance = dijkstra(g, s);

    // s부터 각 정점까지의 경로 출력
    if(distance[e] == 1000) cout << "-1";
    else cout << distance[e];

    return 0;
}
//
//5 1 4
//0 7 4 6 1
//1000 0 1000 1000 1000
//1000 2 0 5 1000
//1000 3 1000 0 1000
//1000 1000 1000 1 0