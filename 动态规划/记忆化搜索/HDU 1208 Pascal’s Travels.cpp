#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 110;
#define ll long long
int n, k;
char mat[maxn][maxn];
ll f[maxn][maxn];

void init() {
    memset(f, -1, sizeof(f));
}

ll dfs(int x, int y) {
    if (x < 0 || y < 0) {
        return 0;
    }
    if (x == 0 && y == 0) {
        f[0][0] = 1;
        return f[0][0];
    }
    ll &ans = f[x][y];
    if (ans != -1) {
        return ans;
    }
    ans = 0;

    for (int i = 1; i < n; ++i) {
        int prex = x - i;
        int prey = y - i;

        if (mat[prex][y] - '0' == i) {
            ans += dfs(prex, y);
        }
        if (mat[x][prey] - '0' == i) {
            ans += dfs(x, prey);
        }
    }
    return ans;

}

int main() {
    int i, j;
    while (scanf("%d", &n) != EOF && n != -1) {
        int maxT = 0;
        init();
        for (i = 0; i < n; ++i) {
            scanf("%s", mat[i]);
        }
        ll ans = dfs(n - 1, n - 1);
        printf("%lld\n", ans);
    }

    return 0;
}