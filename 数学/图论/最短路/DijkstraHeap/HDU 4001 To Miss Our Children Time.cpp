#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
const int MAXN = 1010;
int n;

struct Block {
    int a, b;
    ll area;
    ll c;
    int d;
    Block() {
    }

    Block(int _a, int _b, int _c, int _d) {
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        area = (ll)a * b;
    }

    void read() {
        int w, h, v, tp;
        scanf("%d %d %d %d", &w, &h, &v, &tp);
        a = w;
        b = h;
        c = v;
        d = tp;
        area = (ll)a * b;
        if (a > b) {
            swap(a, b);
        }
    }

    bool operator < (const Block & o) const {
        if (a == o.a && b == o.b) {
            return d < o.d;
        }
        if (a == o.a) {
            return b < o.b;
        }
        return a < o.a;
    }

    bool operator == (const Block& o) const {
        return a == o.a && b == o.b && d == o.d;
    }

}B[MAXN];

void filter() {
    int i;
    sort(B, B + n);

    int tmpn = 0;
    for (i = 0; i < n; ++i) {
        if (i == 0) {
            B[tmpn++] = B[i];
        }
        else if (B[i].d == 0 && B[i] == B[tmpn - 1]){
            B[tmpn - 1].c += B[i].c;
        }
        else {
            B[tmpn++] = B[i];
        }
    }
    n = tmpn;
    B[n++] = Block(0, 0, 0, 0);
}

struct Edge {
    int u;
    ll val;

    Edge() {
    }

    Edge(int to, ll v) {
        u = to;
        val = v;
    }

    bool operator < (const Edge& e) const {
        return val < e.val;
    }
};

vector <Edge> edges[MAXN];

void addedge() {
    for (int i = 0; i < n; ++i) {
        edges[i].clear();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                bool hasedge = false;
                if (B[i].d == 0) {
                    if (B[i].a >= B[j].a && B[i].b >= B[j].b) {
                        hasedge = true;
                    }
                }
                else if (B[i].d == 1) {
                    if (B[i].a >= B[j].a && B[i].b >= B[j].b) {
                        if (B[i].area > B[j].area)
                            hasedge = true;
                    }
                }
                else if (B[i].d == 2) {
                    if (B[i].a > B[j].a && B[i].b > B[j].b) {
                        hasedge = true;
                    }
                }

                if (hasedge) {
                    edges[j].push_back(Edge(i, B[i].c));
                }
            }
        }
    }

}

ll dist[MAXN];

ll bfs(int start) {
    memset(dist, 0, sizeof(dist));
    priority_queue <Edge> Q;
    Q.push(Edge(start, 0));

    while (!Q.empty()) {
        Edge t = Q.top();
        Q.pop();

        for (int i = 0, s = edges[t.u].size(); i < s; ++i) {
            Edge& e = edges[t.u][i];
            if (dist[t.u] + e.val > dist[e.u]) {
                dist[e.u] = dist[t.u] + e.val;
                Q.push(Edge(e.u, dist[e.u]));
            }
        }
    }

    ll Max = 0;
    for (int i = 0; i < n; ++i) {
        if (dist[i] > Max) Max = dist[i];
    }
    return Max;

}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; ++i) {
            B[i].read();
        }
        filter();
        addedge();
        ll ans = bfs(n - 1);
        printf("%lld\n", ans);
    }

    return 0;
}
