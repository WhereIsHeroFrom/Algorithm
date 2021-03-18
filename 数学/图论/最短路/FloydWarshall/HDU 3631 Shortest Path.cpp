#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef int ValueType;
const int maxn = 310;
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


void DijkstraHeap(int n, int st, int *dist) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (st == i) ? 0 : inf;
        visited[i] = false;
    }
    priority_queue <Dist> heap;
    heap.push(Dist(st, 0));

    while (!heap.empty()) {
        Dist s = heap.top();
        heap.pop();
        int u = s.u;
        ValueType dis = s.w;
        if (visited[u]) continue;           // 访问过的不用重复更新
        visited[u] = true;

        // 利用 Dijkstra 更新其它点的最短路信息
        for (int e = head[s.u]; ~e; e = edges[e].next) {
            Edge &nex = edges[e];
            if (dis + nex.w < dist[nex.v]) {
                dist[nex.v] = dis + nex.w;
                heap.push(Dist(nex.v, dist[nex.v]));
            }
        }
    }
}

bool mark[maxn];
ValueType dis[maxn][maxn];


void Floyd(int n, int k) {
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }
}

int main() {
    int i, j;
    int n, m, Q;
    int t = 0;
    while (scanf("%d %d %d", &n, &m, &Q) != EOF && (n || m || Q)) {
        if (t) puts("");
        init();
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                dis[i][j] = (i == j) ? 0 : inf;
            }
        }
        while (m--) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            dis[u][v] = min(dis[u][v], w);
        }
        memset(mark, false, sizeof(mark));
        printf("Case %d:\n", ++t);

        for (i = 0; i < Q; ++i) {
            int p, x, y;
            scanf("%d %d", &p, &x);
            if (p == 0) {
                if (mark[x]) {
                    printf("ERROR! At point %d\n", x);
                }
                else {
                    mark[x] = true;
                    Floyd(n, x);
                }
            }
            else {
                scanf("%d", &y);
                if (mark[x] && mark[y]) {
                    if (dis[x][y] == inf) printf("No such path\n");
                    else printf("%d\n", dis[x][y]);
                }
                else {
                    printf("ERROR! At path %d to %d\n", x, y);
                }

            }
        }
    }
    return 0;
}