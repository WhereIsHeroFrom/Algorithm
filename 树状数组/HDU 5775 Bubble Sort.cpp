/*
    题意：给定一个 n (n <= 100000 ) 个元素的排列，进行一次冒泡排序以后，问每个元素能够达到的最左和最右距离的绝对值。

    题解：每个数一定有一个起始位置，一个最终位置，以及一个往最终位置挪动的位置。
    在这三个位置中挑选一个最左的，最右的做差值即可。
    往最终位置挪动的位置 可以通过树状数组求右边比它大的数有 x 个，就是它能够到达的最右位置 n-x
*/

#include <iostream>
#include <cstring>
#include <queue>
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

int n;
int a[MAXV], ans[MAXV];
int b[3];

int main() {
    int t, i, cas = 0;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        clear();

        for (i = n; i >= 1; --i) {
            int s = sum(n) - sum(a[i]);
            
            b[0] = i;
            b[1] = a[i];
            b[2] = n - s;
            sort(b, b + 3);
            ans[ a[i] ] = b[2] - b[0];
            add(a[i], n, 1);
        }
        printf("Case #%d:", ++cas);

        for (i = 1; i <= n; ++i) {
            printf(" %d", ans[i]);
        }
        puts("");
    }

    return 0;
}

/*
10

7
7 5 4 6 2 3 1
*/