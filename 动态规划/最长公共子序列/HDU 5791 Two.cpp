#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** 二维树状数组 模板 *****************************************
#define maxn 1001
#define ll int
#define mod 1000000007

ll c[maxn][maxn];

int lowbit(int x) {
    return x & (-x);
}

void clear() {
    memset(c, 0, sizeof(c));
}

void add(int x, int y, int v, int xmax, int ymax) {
    while (x <= xmax) {
        int ty = y;
        while (ty <= ymax) {
            c[x][ty] += v;
            if (c[x][ty] >= mod)
                c[x][ty] %= mod;
            ty += lowbit(ty);
        }
        x += lowbit(x);
    }
}

int sum(int x, int y) {
    ll s = 0;
    while (x >= 1) {
        int ty = y;
        while (ty >= 1) {
            s += c[x][ty];
            if (s >= mod)
                s %= mod;
            ty -= lowbit(ty);
        }
        x -= lowbit(x);
    }
    return s;
}
//***************************************** 二维树状数组 模板 *****************************************

ll an[maxn], am[maxn];

int main() {
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF) {
        clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &an[i]);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &am[i]);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (an[i] == am[j]) {
                    ll tot = sum(i - 1, j - 1) + 1;
                    add(i, j, tot, n, m);
                }
            }
        }
        ll ans = sum(n, m);
        printf("%d\n", ans);
    }

    return 0;
}