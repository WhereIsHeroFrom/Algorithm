#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef double ValueType;
const int maxn = 1010;
const int maxm = 2000010;
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
    int u = inf;
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
        int u = Dijkstra_FindMin(n, dist);
        if (u == inf) break;
        Dijkstra_Update(u, dist);
    }
}




int main() {
    int n, m;
    int i, j;
    while (scanf("%d", &n) != EOF && n) {
        init();
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                double w;
                scanf("%lf", &w);
                if (w > 1e-8) {
                    w = -log2(w);
                    addEdge(i, j, w);
                }
            }
        }
        scanf("%d", &m);

        while (m--) {
            int u, v;
            scanf("%d %d", &u, &v);
            --u, --v;
            Dijkstra(n, u, dist);
            ValueType dis = dist[v];
            if (dis > inf - 1) {
                printf("What a pity!\n");
                continue;
            }
            dis = pow(2, -dis);
            if (dis < 0) dis = 0;
            printf("%.3lf\n", dis);
        }
    }

    return 0;
}