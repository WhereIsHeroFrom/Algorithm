/*
    题意：给定一个 n(n <= 50000)个元素的数组 A，求四元组 (a, b, c, d) 满足：
    1. 1 ≤ a < b < c < d ≤ n
    2. A[a] < A[b]
    3. A[c] < A[d]

    题解： B[i] 表示 j<i && A[j]<A[i] 的 j 的个数，SumB[i] = sum{ 1<=k<=i| B[i]}
    顺序求一次 B[i]， 逆序求一次 B[i] 并且求后缀和, 相乘累加就是答案。
*/

#include <iostream>
#include <cstring>
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
    while (x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** 一维树状数组 模板 *****************************************

ll A[MAXV];
ll B[2][MAXV];
int n;

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            A[i] = x;
        }
        memset(B, 0, sizeof(B));

        clear();
        for (i = 1; i <= n; ++i) {
            B[0][i] = sum(A[i] - 1);
            add(A[i], n, 1);
        }

        clear();
        for (i = n; i >= 1; --i) {
            B[1][i] = B[1][i + 1] + ( (n-i) - sum(A[i]) );
            add(A[i], n, 1);
        }

        ll s = 0;
        for (i = 1; i < n; ++i) {
            s += B[0][i] * B[1][i + 1];
        }
        printf("%lld\n", s);
    }

    return 0;
}