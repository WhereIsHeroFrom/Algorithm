#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef int ValueType;
const int maxn = 1010;
const int maxm = 2000010;
const int INVALID_INDEX = -1;
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

void Dijkstra_Init(int n, int st, ValueType *dist) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (st == i) ? 0 : inf;
        visited[i] = false;
    }
}

int Dijkstra_FindMin(int n, ValueType *dist) {
    int u = INVALID_INDEX;
    for (int i = 0; i < n; ++i) {
        if (visited[i])
            continue;
        if (u == INVALID_INDEX || dist[i] < dist[u]) {
            u = i;
        }
    }
    return u;
}

void Dijkstra_Update(int u, ValueType *dist) {
    visited[u] = true;
    for (int e = head[u]; ~e; e = edges[e].next) {
        Edge& to = edges[e];
        if (dist[u] + to.w < dist[to.v]) {
            dist[to.v] = dist[u] + to.w;
        }
    }
}

void Dijkstra(int n, int st, ValueType *dist) {
    Dijkstra_Init(n, st, dist);
    while (true) {
        int u = Dijkstra_FindMin(n, dist);
        if (u == INVALID_INDEX) break;
        Dijkstra_Update(u, dist);
    }
}




int main() {
    int n, m;
    int i, j;
    while (scanf("%d", &n) != EOF && n) {
        init();
        int s, t;
        scanf("%d %d", &s, &t);
        --s, --t;
        for (i = 0; i < n; ++i) {
            int ki;
            scanf("%d", &ki);
            int l = i - ki;
            int r = i + ki;
            if (l >= 0)
                addEdge(i, l, 1);
            if (r < n)
                addEdge(i, r, 1);
        }
        Dijkstra(n, s, dist);
        ValueType x = dist[t];
        if (x == inf) x = -1;
        printf("%d\n", x);
    }

    return 0;
}