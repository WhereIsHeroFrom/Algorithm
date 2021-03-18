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

int head[maxn], edgeCount;
int visited[maxn];

void init() {
    edgeCount = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, ValueType w) {
    edges[edgeCount] = Edge(u, v, w, head[u]);
    head[u] = edgeCount++;
}

void SPFA(int n, int st, ValueType *dist, int *cnt) {
    for (int i = 0; i < n; ++i) {
        dist[i] = (st == i) ? 0 : inf;
        cnt[i] = (st == i) ? 1 : 0;
        visited[i] = 0;
    }
    queue <int> que;
    que.push(st);

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        // 遇到负环了
        if (visited[u] ++ > n) {
            //break;
        }

        // 利用 Dijkstra 更新其它点的最短路信息
        for (int e = head[u]; ~e; e = edges[e].next) {
            int v = edges[e].v;
            if (dist[u] + edges[e].w < dist[v]) {
                dist[v] = dist[u] + edges[e].w;
                cnt[v] = cnt[u] + 1;
                que.push(v);
            }
            else if (dist[u] + edges[e].w == dist[v]) {
                if (cnt[u] + 1 > cnt[v]) {
                    cnt[v] = cnt[u] + 1;
                    que.push(v);
                }
            }
        }
    }
}

ValueType dist[maxn][maxn];
int cnt[maxn][maxm];

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
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        --a, --b, --c, --d;
        for (int i = 0; i < n; ++i) {
            SPFA(n, i, dist[i], cnt[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] == inf) continue;
                if (dist[a][i] == inf || dist[j][b] == inf) continue;
                if (dist[c][i] == inf || dist[j][d] == inf) continue;

                if (dist[a][i] + dist[i][j] + dist[j][b] != dist[a][b]) continue;
                if (dist[c][i] + dist[i][j] + dist[j][d] != dist[c][d]) continue;

                ans = max(ans, cnt[i][j]);
            }
        }
        printf("%d\n", ans);

    }
    return 0;
}