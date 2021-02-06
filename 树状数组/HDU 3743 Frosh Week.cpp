
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 100010
#define ll long long

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
int v[MAXV], vsize;
int w[MAXV];

int getW(int now) {
    int l = 0, r = vsize - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (v[mid] == now) {
            return mid;
        }
        else if (now < v[mid]) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
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


    while ( scanf("%d", &n) != EOF ) {
        clear();
        // 离散化
        vsize = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &w[i]);
            v[vsize++] = w[i];
        }
        // 去重
        sort(v, v + vsize);
        int tmpvsize = 1;
        for (int i = 1; i < vsize; ++i) {
            if (v[i] != v[tmpvsize - 1]) 
                v[tmpvsize++] = v[i];
        }
        vsize = tmpvsize;
        // 二分查找离散后的下标
        for (int i = 1; i <= n; ++i) {
            w[i] = getW(w[i]) + 1;
        }

        ll s = 0;
        for (int i = n; i >= 1; --i) {
            s += sum(w[i]);
            add(w[i], n, 1);
        }
        printf("%lld\n", s);
    }


    return 0;
}
