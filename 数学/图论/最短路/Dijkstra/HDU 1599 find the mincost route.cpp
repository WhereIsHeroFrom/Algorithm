#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef int ValueType;
const int maxn = 110;
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
ValueType d[maxn];
bool visited[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, ValueType w) {
    edges[edgeCount] = Edge(u, v, w, head[u]);
    head[u] = edgeCount++;
}

// 顶点 0 ~ n-1
// 起点 start
// 终点 end
ValueType Dijkstra(int n, int start, int end) {
    for (int i = 0; i < n; ++i) {
        d[i] = inf;
        visited[i] = false;
    }
    d[start] = 0;
    while (1) {
        ValueType Min = inf;
        int u;
        for (int i = 0; i < n; ++i) {
            if (visited[i]) {
                continue;
            }
            if (d[i] < Min) {
                Min = d[i];
                u = i;
            }
        }
        if (Min == inf) {
            break;
        }
        visited[u] = true;

        if (u == end) {
            return d[end];
        }

        for (int e = head[u]; e != -1; e = edges[e].next) {
            Edge& to = edges[e];

            if (to.u == start && to.v == end
                || to.u == end && to.v == start
                ) {
                continue;
            }

            if (d[u] + to.w < d[to.v]) {
                d[to.v] = d[u] + to.w;
            }
        }
    }
    return d[end];
}

Edge E[maxn][maxn];
int ECnt[maxn];
int mat[maxn][maxn];

int main() {
    int n, m;
    int i, j;
    while (scanf("%d %d", &n, &m) != EOF) {
        init();
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                mat[i][j] = (i == j) ? 0 : inf;
            }
            ECnt[i] = 0;
        }

        for (i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            --u, --v;
            if (w < mat[u][v]) {
                mat[u][v] = mat[v][u] = w;
            }
        }

        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                if (mat[i][j] && mat[i][j] != inf) {
                    addEdge(i, j, mat[i][j]);
                    E[i][ECnt[i]++] = Edge(i, j, mat[i][j], -1);
                }
            }
        }

        int Min = inf;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < ECnt[i]; ++j) {
                int ans = E[i][j].w + Dijkstra(n, i, E[i][j].v);
                Min = min(Min, ans);
            }
        }
        if (Min == inf) {
            printf("It's impossible.\n");
        }
        else
            printf("%d\n", Min);

    }
    return 0;
}