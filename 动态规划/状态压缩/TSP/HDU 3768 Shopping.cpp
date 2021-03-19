#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef int ValueType;
const int maxn = 100010;
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


#define maxk 12
int idList[maxk], idCnt;
int idHash[maxn];

ValueType d[maxk][maxn];
ValueType mat[maxk][maxk];


// 
//  dp[i][j]   表示当前点在 i，状态为 j 的最短路径
//             dp[i][j] = min{ dp[k][j^(1<<i)] , dp[k][j] }  + mat[k][i];
ValueType dp[maxk][1 << maxk];

int lowbit(int x) {
    return x & -x;
}

ValueType TSP_dfs(int st, int u, int state) {
    if (u == st && state == (1 << u)) {
        return 0;
    }
    int dstate = state;
    ValueType &x = dp[u][state];
    if (x != -1) {
        return x;
    }
    x = inf;
    int pre = ((1 << u) ^ state);
    for (int k = 0; k < idCnt; ++k) {
        if ((1 << k) & state) {

            int ans = min(TSP_dfs(st, k, state), TSP_dfs(st, k, pre)) + mat[k][u];
            x = min(x, ans);

        }
    }
    return x;
}

int TSP() {
    int ans = inf;
    for (int i = 1; i < idCnt; ++i) {
        memset(dp, -1, sizeof(dp));
        ans = min(ans, (mat[0][i] + TSP_dfs(i, 0, (1 << idCnt) - 1)));
    }
    return ans;
}

int main() {
    vector<int> a;
    int n, m, l;
    int i, j, k;
    int t;
    scanf("%d", &t);
    while (t--) {
        init();
        scanf("%d %d", &n, &m);
        while (m--) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        scanf("%d", &k);
        memset(idHash, -1, sizeof(idHash));
        idCnt = 0;

        idHash[0] = 0;
        idList[idCnt++] = 0;

        for (i = 0; i < k; ++i) {
            int x;
            scanf("%d", &x);
            if (idHash[x] == -1) {
                idHash[x] = idCnt;
                idList[idCnt++] = x;
            }
        }
        for (i = 0; i < idCnt; ++i) {
            DijkstraHeap(n, idList[i], d[i]);
        }

        for (i = 0; i < idCnt; ++i) {
            for (j = 0; j < idCnt; ++j) {
                mat[i][j] = d[i][idList[j]];
            }
        }

        ValueType ans = TSP();
        printf("%d\n", ans);
    }
    return 0;
}

/*
10
4 6
0 1 1
1 2 2
2 3 3
3 0 4
0 2 5
1 3 5
2
2 3

*/