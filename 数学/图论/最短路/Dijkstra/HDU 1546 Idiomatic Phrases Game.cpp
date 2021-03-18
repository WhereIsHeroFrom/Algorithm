#include <iostream>
#include <cstring>

using namespace std;

typedef int ValueType;
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


struct Idiom {
    int ti;
    char data[110];
    int len;
    void read() {
        scanf("%d %s", &ti, data);
        len = strlen(data);
    }

    bool is_pre_of(const Idiom& I) const {
        return data[len - 4] == I.data[0]
            && data[len - 3] == I.data[1]
            && data[len - 2] == I.data[2]
            && data[len - 1] == I.data[3];
    }

}I[maxn];


int main() {
    int n, m;
    int i, j;
    while (scanf("%d", &n) != EOF && n) {
        init();
        for (i = 0; i < n; ++i) {
            I[i].read();
        }
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                if (i != j) {
                    if (I[i].is_pre_of(I[j])) {
                        addEdge(i, j, I[i].ti);
                    }
                }
            }
        }
        Dijkstra(n, 0, dist);
        ValueType ans = dist[n - 1];
        printf("%d\n", ans == inf ? -1 : ans);
    }

    return 0;
}