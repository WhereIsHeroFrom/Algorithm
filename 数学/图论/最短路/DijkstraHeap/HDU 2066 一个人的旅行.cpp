// HDU 2066
// 图论：最短路
// STL : 队列 queue 的应用
// 贝尔曼 BFS 注意双向边

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef int ValueType;
const int maxn = 10010;
const int maxm = 200010;
const ValueType inf = 1e9;

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
ValueType dist[maxn];
bool visited[maxn];

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

void DijkstraHeap(int n, int st, ValueType *dist) { // 1）
    Heap heap;
    Dijkstra_Init(n, st, heap, dist);               // 2）
    while (!heap.empty()) {
        int u = Dijkstra_FindMin(heap);             // 3）
        Dijkstra_Update(u, heap, dist);             // 4）
    }
}

int tar[maxn];

int main() {
    int i;
    int v;
    int m, n, S, D;

    while (scanf("%d %d %d", &m, &S, &D) != EOF) {
        init();
        n = maxn - 1;
        for (i = 0; i <= n; ++i) {
            tar[i] = 0;
        }
        for (i = 0; i < m; ++i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            addEdge(x, y, z);
            addEdge(y, x, z);
        }
        while (S--) {
            scanf("%d", &v);
            addEdge(0, v, 0);
        }

        while (D--) {
            scanf("%d", &v);
            tar[v] = 1;
        }
        DijkstraHeap(n, 0, dist);

        int ans = inf;
        for (i = 0; i < n; ++i) {
            if (tar[i] && dist[i] != inf) {
                if (dist[i] < ans) ans = dist[i];
            }
        }
        if (ans == inf) ans = 0;
        printf("%d\n", ans);
    }

    return 0;
}