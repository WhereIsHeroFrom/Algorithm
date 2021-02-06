/*
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

int A, B;
ll Grid[1010][1010];

int main() {
    int t, m;
    int a, b;
    int x, y, cas = 0;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &A, &B);
        for (int x = 1; x <= 1000; ++x) {
            for (int y = 1; y <= 1000; ++y) {
                Grid[x][y] = (x + A) * (y + B);
                Grid[x][y] += Grid[x][y - 1];
            }
        }

        printf("Case #%d:\n", ++cas);
        scanf("%d", &m);

        while (m--) {
            scanf("%d %d %d", &a, &b, &x);
            ll s = 0;

            for (int i = 1; i <= x; ++i) {
                int v = b * i / a;
                if (v > 1000) v = 1000;
                s += Grid[i][v];
            }
            printf("%lld\n", s);
        }

    }


    return 0;
}