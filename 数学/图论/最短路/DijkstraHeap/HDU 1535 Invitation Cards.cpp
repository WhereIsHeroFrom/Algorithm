#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long ValueType;
const int maxn = 1000010;
const int maxm = 1000010;
const ValueType inf = (ValueType)1e9 * 1e9;

struct Edge {
    int u, v, next;
    ValueType w;
    Edge(){}
    Edge(int _u, int _v, ValueType _w, int _next) :
        u(_u), v(_v), w(_w), next(_next)
    {
    }
}edges[maxm];

struct Dist {
    int u;
    ValueType w;
    Dist(){}
    Dist(int _u, ValueType _w) : u(_u), w(_w)
    {
    }
    bool operator < (const Dist& d) const {
        return w > d.w;
    }
};
typedef priority_queue <Dist> Heap;
int head[maxn], edgeCount;
int visited[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, ValueType w) {
    edges[edgeCount] = Edge(u, v, w, head[u]);
    head[u] = edgeCount++;
}

void Dijkstra_Init(int n, int st, Heap& heap, ValueType *dist) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (st == i) ? 0 : inf;
        visited[i] = false;
    }
    heap.push(Dist(st, 0));
}

void Dijkstra_Update(int u, Heap& heap, ValueType *dist) {
    if (visited[u]) {
        return;
    }
    visited[u] = true;
    for (int e = head[u]; ~e; e = edges[e].next) {
        int v = edges[e].v;
        int w = edges[e].w;
        dist[v] = min(dist[v], (dist[u] + w));
        if (dist[u] + w == dist[v])
            heap.push(Dist(v, dist[v]));
    }
}

int Dijkstra_FindMin(Heap& heap) {
    Dist s = heap.top();
    heap.pop();
    return s.u;
}

void DijkstraHeap(int n, int st, ValueType *dist) { // 1£©
    Heap heap;
    Dijkstra_Init(n, st, heap, dist);               // 2£©
    while (!heap.empty()) {
        int u = Dijkstra_FindMin(heap);             // 3£©
        Dijkstra_Update(u, heap, dist);             // 4£©
    }
}




ValueType dist[maxn];

struct Triple {
    int x, y;
    int c;

    void read() {
        scanf("%d %d %d", &x, &y, &c);
        --x, --y;
    }
}T[maxm];

int main() {
    int t;
    int n, m;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; ++i) {
            T[i].read();
        }
        ValueType sum = 0;
        init();
        for (int i = 0; i < m; ++i) {
            addEdge(T[i].x, T[i].y, T[i].c);
        }
        DijkstraHeap(n, 0, dist);
        for (int i = 0; i < n; ++i) sum += dist[i];
        init();
        for (int i = 0; i < m; ++i) {
            addEdge(T[i].y, T[i].x, T[i].c);
        }
        DijkstraHeap(n, 0, dist);
        for (int i = 0; i < n; ++i) sum += dist[i];
        printf("%lld\n", sum);

    }
    return 0;
}
