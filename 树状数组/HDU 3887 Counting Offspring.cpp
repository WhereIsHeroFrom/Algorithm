
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 100010
#define ll int

ll c[MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int maxn, ll v) {
    while (x <= maxn) {
        c[x] += v;
        x += lowbit(x);
    }
}

ll sum(int x) {
    ll s = 0;
    while (x >= 1) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

int n, k;

vector <int> edges[MAXV];
int Id[MAXV], IdCnt, IdHas[MAXV];
int nodesCnt[MAXV];
int f[MAXV];

struct Interval {
    int l, r;
    int v;
    Interval() {}
    Interval(int il, int ir, int iv) : l(il), r(ir), v(iv) {}

    bool operator < (const Interval& I) const {
        return r < I.r;
    }
}I[MAXV];
int iTop;

void dfs(int fat, int u) {
    Id[u] = ++IdCnt;
    IdHas[Id[u]] = u;
    nodesCnt[u] = 1;
    for (int i = 0, s = edges[u].size(); i < s; ++i) {
        int v = edges[u][i];
        if (v != fat) {
            dfs(u, v);
            nodesCnt[u] += nodesCnt[v];
        }
    }
    I[iTop++] = Interval(Id[u], Id[u] + nodesCnt[u] - 1, u);
}

int main() {
    int t;
    int d;

    while (scanf("%d %d", &n, &d) != EOF && (n || d)) {
        clear();
        iTop = 0;
        IdCnt = 0;
        for (int i = 1; i <= n; ++i) {
            edges[i].clear();
        }

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        dfs(0, d);
        sort(I, I + iTop);
        memset(f, 0, sizeof(f));
        int R = 0;
        for (int i = 0; i < iTop; ++i) {
            for (int j = R + 1; j <= I[i].r; ++j) {
                add(IdHas[j], n, 1);
            }
            R = I[i].r;
            f[I[i].v] = sum(I[i].v - 1);
        }
        clear();
        for (int i = 1; i <= n; ++i) {
            f[IdHas[i]] -= sum(IdHas[i]);
            add(IdHas[i], n, 1);
        }


        for (int i = 1; i <= n; ++i) {
            if (i > 1) printf(" ");
            printf("%d", f[i]);
        }
        puts("");
    }
    return 0;
}

/*
10
12 3
1 2 1 3 1 2 1 2 2 2 2 1
1 2
1 5
2 3
2 4
5 6
5 7
7 8
7 9
9 10
9 11
7 12
*/
