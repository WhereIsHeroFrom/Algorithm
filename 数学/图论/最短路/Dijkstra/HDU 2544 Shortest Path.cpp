#include <iostream>
#include <cstring>

using namespace std;

typedef int ValueType;
const int maxn = 1100;
const int maxm = 200010;
const int inf = 1e9;
const int INVALID_INDEX = -1;

struct Edge {
    int u, v, w, next;
    Edge(){}
    Edge(int _u, int _v, int _w, int _next) :
        u(_u), v(_v), w(_w), next(_next)
    {
    }
}edges[maxm];

int head[maxn], edgeCount;
int dist[maxn];
bool visited[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int w) {
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
        int v = edges[e].v;
        int w = edges[e].w;
        dist[v] = min(dist[v], (dist[u] + w));
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
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        init();
        while (m--) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u, --v;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        Dijkstra(n, 0, dist);
        printf("%d\n", dist[n - 1]);
    }

    return 0;
}