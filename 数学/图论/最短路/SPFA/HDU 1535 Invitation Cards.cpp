#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long ValueType;
const int maxn = 1000010;
const int maxm = 1000010;
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
int visited[maxn], inqueue[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, ValueType w) {
    edges[edgeCount] = Edge(u, v, w, head[u]);
    head[u] = edgeCount++;
}

void SPFA(int n, int st, ValueType *dist) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (st == i) ? 0 : inf;
        visited[i] = 0;
        inqueue[i] = false;
    }
    queue <int> que;
    que.push(st);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inqueue[u] = false;
        // 遇到负环了
        if (visited[u] ++ > n) {
            //break;
        }

        // 利用边来更新其它点的 最短路信息
        for (int e = head[u]; ~e; e = edges[e].next) {
            int v = edges[e].v;
            if (dist[u] + edges[e].w < dist[v]) {
                dist[v] = dist[u] + edges[e].w;
                if (!inqueue[v]) {
                    inqueue[v] = true;
                    que.push(v);
                }
            }
        }
    }
}

ValueType dist[maxn];

struct Triple {
    int x, y;
    int c;

    void read() {
        scanf("%d %d %d", &x, &y, &c);
        --x, --y;
    }
}T[maxm];

int main() {
    int t;
    int n, m;

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; ++i) {
            T[i].read();
        }
        ValueType sum = 0;
        init();
        for (int i = 0; i < m; ++i) {
            addEdge(T[i].x, T[i].y, T[i].c);
        }
        SPFA(n, 0, dist);
        for (int i = 0; i < n; ++i) sum += dist[i];
        init();
        for (int i = 0; i < m; ++i) {
            addEdge(T[i].y, T[i].x, T[i].c);
        }
        SPFA(n, 0, dist);
        for (int i = 0; i < n; ++i) sum += dist[i];
        printf("%lld\n", sum);

    }
    return 0;
}