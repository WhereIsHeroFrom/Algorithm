#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 1010
#define MAXM 1000000
#define INF 100000000

struct Edge {
    int u, v, h, dis;
    int next;
    Edge() {

    }
    Edge(int _u, int _v, int _h, int _dis, int _next) {
        u = _u;
        v = _v;
        h = _h;
        dis = _dis;
        next = _next;
    }
}E[MAXM];

struct Pair {
    int v, d;
    Pair() {
    }
    Pair(int _v, int _d) {
        v = _v;
        d = _d;
    }
    friend bool operator < (Pair a, Pair b) {
        return a.d > b.d;
    }
};

int n, m;
int head[MAXN], tot;
int dis[MAXN];

void addEdge(int u, int v, int h, int dis) {
    E[tot] = Edge(u, v, h, dis, head[u]);
    head[u] = tot++;
}

int Dijkstra_Heap(int s, int end, int h) {
    int i;
    for (i = 1; i <= n; i++) {
        dis[i] = (s == i) ? 0 : INF;
    }
    priority_queue <Pair> Q;
    Q.push(Pair(s, 0));

    while (!Q.empty()) {
        Pair pa = Q.top();
        Q.pop();

        int u = pa.v;
        if (u == end) {
            return pa.d;
        }

        for (int e = head[u]; e != -1; e = E[e].next) {
            if (E[e].h < h && E[e].h != -1) {
                continue;
            }
            int v = E[e].v;
            if (dis[u] + E[e].dis < dis[v]) {
                dis[v] = dis[u] + E[e].dis;
                Q.push(Pair(v, dis[v]));
            }
        }
    }
    return INF;
}
int main() {
    int cases = 0;
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        tot = 0;
        memset(head, -1, sizeof(head));

        if (cases++) {
            printf("\n");
        }
        while (m--) {
            int u, v, h, d;
            scanf("%d %d %d %d", &u, &v, &h, &d);
            addEdge(u, v, h, d);
            addEdge(v, u, h, d);
        }
        int s, t, h;
        scanf("%d %d %d", &s, &t, &h);
        int ans = Dijkstra_Heap(s, t, 0);
        printf("Case %d:\n", cases);
        if (ans == INF) {
            printf("cannot reach destination\n");
        }
        else {
            int l = 0, r = h;
            int hlimit = h;
            while (l <= r) {
                int mid = (l + r) >> 1;
                ans = Dijkstra_Heap(s, t, mid);
                if (ans != INF) {
                    hlimit = mid;
                    l = mid + 1;
                }
                else {
                    r = mid - 1;
                }
            }
            printf("maximum height = %d\n", hlimit);
            printf("length of shortest route = %d\n", Dijkstra_Heap(s, t, hlimit));
        }

    }
    return 0;
}

/*
5 6
1 2 7 5
1 3 4 2
2 4 -1 10
2 5 2 4
3 4 10 1
4 5 8 5
1 5 10
5 6
1 2 7 5
1 3 4 2
2 4 -1 10
2 5 2 4
3 4 10 1
4 5 8 5
1 5 4
3 1
1 2 -1 100
1 3 10
*/
