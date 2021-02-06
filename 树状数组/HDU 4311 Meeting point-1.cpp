/*
    题意：二维空间上 n (n <= 100000) 个点，范围在 [-10^9, 10^9]，要求选择一个点，
    使得它到其他所有点的曼哈顿距离之和最小。

    题解：由于是计算曼哈顿距离，所以 x 和 y 轴是完全不相关的两个维度，是可以分开计算的。
    对于x轴，将所有点按照 x 轴排序，计算相邻两个点之间的差值，用树状数组来维护前缀和。
    y轴同样处理。
*/

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//***************************************** 一维树状数组 模板 *****************************************

#define MAXV 200100
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

struct Point {
    int x, y;
    int idx;
    void read(int i) {
        scanf("%d %d", &x, &y);
        idx = i;
    }

    static bool cmpx1(const Point& a, const Point& b) {
        return a.x < b.x;
    }

    static bool cmpx2(const Point& a, const Point& b) {
        return a.x > b.x;
    }

    static bool cmpy1(const Point& a, const Point& b) {
        return a.y < b.y;
    }
    
    static bool cmpy2(const Point& a, const Point& b) {
        return a.y > b.y;
    }

}P[MAXV];

int n;
ll ans[MAXV];

ll ABS(ll x) {
    return x > 0 ? x : -x;
}

void check(int tp) {
    int i;
    ll sns = sum(n - 1);
    for (i = 0; i < n; ++i) {
        ll sn = sns - sum(i);
        ll sb = (ll)(tp==0?P[i].x:P[i].y) * (n-i-1);
        ans[P[i].idx] += ABS(sn - sb);
    }
}

int main() {
    int t;
    int i;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            P[i].read(i);
        }
        memset(ans, 0, sizeof(ans));

        // 处理x递增的情况
        sort(P, P + n, Point::cmpx1);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].x );
        }
        check(0);

        // 处理x递减的情况
        sort(P, P + n, Point::cmpx2);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].x);
        }
        check(0);

        // 处理y递增的情况
        sort(P, P + n, Point::cmpy1);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].y);
        }
        check(1);

        // 处理y递减的情况
        sort(P, P + n, Point::cmpy2);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].y);
        }
        check(1);

        int Min = 0;
        for (i = 0; i < n; ++i) {
            if (ans[i] < ans[Min]) {
                Min = i;
            }
        }
        printf("%lld\n", ans[Min]);

    }

    return 0;
}

/*
4
6
-4 -1
-1 -2
2 -4
0 2
0 3
5 -2
6
0 0
2 0
-5 -2
2 -2
-1 2
4 0
5
-5 1
-1 3
3 1
3 -1
1 -1
10
-1 -1
-3 2
-4 4
5 2
5 -4
3 -1
4 3
-1 -2
3 4
-2 2
*/