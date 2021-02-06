
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 300010
#define ll int
#define mod 9901

ll c[MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int maxn, ll v) {
    v %= mod;
    while (x <= maxn) {
        c[x] += v;
        if (c[x] >= mod) c[x] %= mod;
        x += lowbit(x);
    }
}

ll sum(int x) {
    ll s = 0;
    while (x >= 1) {
        s += c[x];
        if (s >= mod) s %= mod;
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

int n, k;
int v[MAXV], vsize;
int w[MAXV];

int getW(int now) {
    int l = 0, r = vsize - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (v[mid] == now) {
            return mid + 1;
        }
        else if (now < v[mid]) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
}

int getV(int idx) {
    return v[idx - 1];
}

vector <int> edges[MAXV];
int Id[MAXV], IdCnt;
int nodesCnt[MAXV];

void dfs(int fat, int u) {
    Id[u] = ++IdCnt;
    nodesCnt[u] = 1;

    for (int i = 0, s = edges[i].size(); i < s; ++i) {
        int v = edges[u][i];
        if (v != fat) {
            dfs(u, v);
            nodesCnt[u] += nodesCnt[v];
        }
    }
}

int main() {
    int t;
    int d;

    while ( scanf("%d %d", &n, &d) != EOF ) {
        clear();
        // 离散化
        vsize = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &w[i]);
            v[vsize++] = w[i];
            v[vsize++] = w[i] - d;
            v[vsize++] = w[i] + d;
        }

        // 去重
        sort(v, v + vsize);
        int tmpvsize = 1;
        for (int i = 1; i < vsize; ++i) {
            if (v[i] != v[tmpvsize - 1]) 
                v[tmpvsize++] = v[i];
        }
        vsize = tmpvsize;

        ll s = 0, dp = 0;
        int maxn = n * 3;
        int tot = 0;
        for (int i = 1; i <= n; ++i) {
            int from = getW(w[i] - d);
            int to = getW(w[i] + d);
            int dp = 1 + sum(to) - sum(from - 1);
            add(getW(w[i]), maxn, dp);
            tot += dp;
            tot %= mod;
        }
        tot = ((tot - n) % mod + mod) % mod;
        printf("%d\n", tot);
    }


    return 0;
}

