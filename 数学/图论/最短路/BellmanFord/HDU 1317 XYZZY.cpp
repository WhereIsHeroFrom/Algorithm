#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef int ValueType;
const int maxn = 110;
const int maxm = 2000010;
const ValueType inf = -1e9;

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

bool BellmanFordUpdate() {
    bool flag = false;
    for (int i = 0; i < edgeCount; ++i) {
        Edge &edge = edges[i];

        if (dist[edge.u] <= 0) continue;

        if (dist[edge.u] + edge.w > dist[edge.v]) {
            flag = true;
            dist[edge.v] = dist[edge.u] + edge.w;
        }
    }
    return flag;
}

bool mat[maxn][maxn];

bool BellmanFord(int n) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (i == 0) ? 100 : inf;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (!BellmanFordUpdate()) {
            return dist[n - 1] >= 0;
        }
    }
    for (int i = 0; i < edgeCount; ++i) {
        Edge &edge = edges[i];

        if (dist[edge.u] <= 0) continue;

        if (dist[edge.u] + edge.w > dist[edge.v]) {
            if (mat[edge.u][n - 1]) {
                return true;
            }
        }
    }
    return dist[n - 1] >= 0;
}

int d[maxn], to[maxn][maxn];


void floyed(int n) {
    int i, j, k;
    for (k = 0; k < n; ++k) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                mat[i][j] = mat[i][j] || (mat[i][k] && mat[k][j]);
            }
        }
    }
}

int main() {
    int n, m, l;
    int i, j, k;
    int t;
    while (scanf("%d", &n) != EOF && n != -1) {
        init();
        for (i = 0; i < n; ++i) {
            scanf("%d %d", &d[i], &to[i][0]);
            for (j = 0; j < n; ++j) {
                mat[i][j] = i == j;
            }
            for (j = 1; j <= to[i][0]; ++j) {
                scanf("%d", &to[i][j]);
                int t = --to[i][j];
                mat[i][t] = 1;
            }

        }
        floyed(n);

        for (i = 0; i < n; ++i) {
            for (j = 1; j <= to[i][0]; ++j) {
                int u = i, v = to[i][j], w = d[to[i][j]];
                addEdge(u, v, w);
            }
        }
        bool circle = BellmanFord(n);
        if (circle) {
            printf("winnable\n");
        }
        else {
            printf("hopeless\n");
        }


    }
    return 0;
}