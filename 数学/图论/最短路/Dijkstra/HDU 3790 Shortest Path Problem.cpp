#include <iostream>
#include <cstring>

using namespace std;

typedef long long ValueType;
const int maxn = 1010;
const int maxm = 200010;
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

ValueType Dijkstra_FindMin(int n, ValueType *dist) {
    ValueType u = inf;
    for (int i = 0; i < n; ++i) {
        if (visited[i])
            continue;
        if (u == inf || dist[i] < dist[u]) {
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
        ValueType u = Dijkstra_FindMin(n, dist);
        if (u == inf) break;
        Dijkstra_Update(u, dist);
    }
}


const int C = 1000000000;

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        init();
        while (m--) {
            int u, v;
            int d, p;
            scanf("%d %d %d %d", &u, &v, &d, &p);
            --u, --v;
            ValueType w = (ValueType)d * C + p;
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        int s, t;
        scanf("%d %d", &s, &t);
        --s, --t;
        Dijkstra(n, s, dist);
        ValueType ans = dist[t];
        printf("%d %d\n", int(ans / C), int(ans % C));
    }

    return 0;
}