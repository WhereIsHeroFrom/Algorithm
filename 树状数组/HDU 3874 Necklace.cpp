/*
    题意：给定 n <= 50000 个数，再给出 m <= 200000 次询问，每次询问问的是 [L, R] 这个区间内不重复数的和。

    题解：前缀和 + 相同数前驱 + 离线算法 + 树状数组

    预处理前缀和 S[i]
    预处理前驱 pre[i]，  a[i] == a[j] && i < j  则 pre[j] = i;

    将所有数的 前驱所在的数插入树状数组  add(pre[i], a[i])
    
    对区间进行尾端点排序，然后从前往后枚举区间，把从头到区间尾的数按照上述方法插入树状数组，
    插完后进行查询，查询的是  sum(n) - sum(L[i])  代表比 L[i] 大的所有数的和 X ，然后用当前区间前缀和减去
    X 就是这个区间的答案了。
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 50010
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

ll s[MAXV];
int a[MAXV], pre[MAXV];
int pos[1000010];
ll ans[MAXV];
int n, m;

struct Interval {
    int l, r;
    int idx;

    void read(int i) {
        scanf("%d %d", &l, &r);
        idx = i;
    }

    bool operator < (const Interval& i) const {
        return r < i.r;
    }
}I[200010];


int main() {
    int t, i, j;
    scanf("%d", &t);
    while (t--) {

        scanf("%d", &n);
        memset(pos, 0, sizeof(pos));
        clear();

        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            s[i] = s[i - 1] + a[i];
            pre[i] = pos[a[i]];
            pos[a[i]] = i;
        }
        
        scanf("%d", &m);
        for (i = 0; i < m; ++i) {
            I[i].read(i + 1);
        }
        sort(I, I + m);
        int R = 0;
        for (i = 0; i < m; ++i) {
            for (j = R + 1; j <= I[i].r; ++j) {
                if (pre[j])
                    add(pre[j], n, a[j]);
            }
            R = I[i].r;
            ans[I[i].idx] = s[I[i].r] - s[I[i].l-1] - sum(n) + sum(I[i].l - 1);
        }
        for (i = 1; i <= m; ++i) {
            printf("%lld\n", ans[i]);
        }
    }

    return 0;
}