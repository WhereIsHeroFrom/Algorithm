#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef int ValueType;
const int maxn = 100010;
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

void DijkstraHeap(int n, int st, ValueType *dist) { // 1£©
    Heap heap;
    Dijkstra_Init(n, st, heap, dist);               // 2£©
    while (!heap.empty()) {
        int u = Dijkstra_FindMin(heap);             // 3£©
        Dijkstra_Update(u, heap, dist);             // 4£©
    }
}

char bus[maxn][50];

int findName(int& n, char *name) {
    for (int i = 0; i < n; ++i) {
        if (!strcmp(name, bus[i])) {
            return i;
        }
    }
    strcpy(bus[n], name);
    return n++;
}

char st[50], en[50];

int main() {
    int i, j;
    int n, m;
    while (scanf("%d", &m) != EOF && m != -1) {
        init();
        scanf("%s %s", st, en);
        int s, t;
        int n = 0;
        s = findName(n, st);
        t = findName(n, en);

        while (m--) {
            int u, v, w;
            scanf("%s %s %d", st, en, &w);
            u = findName(n, st);
            v = findName(n, en);

            addEdge(u, v, w);

            addEdge(v, u, w);
        }
        DijkstraHeap(n, s, dist);
        if (dist[t] == inf) dist[t] = -1;
        printf("%d\n", dist[t]);
    }
    return 0;
}