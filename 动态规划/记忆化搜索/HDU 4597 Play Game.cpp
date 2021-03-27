#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 25;
const int flag = -10209321;
#define ll int
int n, m;
ll f[2][maxn][maxn][maxn][maxn];
int mat[2][maxn];

void init() {
    memset(f, -1, sizeof(f));
}

ll dfs(int odd, int l1, int r1, int l2, int r2) {
    if (l1 > r1 && l2 > r2) {
        return 0;
    }

    int &val = f[odd][l1][r1][l2][r2];
    if (val != -1) {
        return val;
    }

    if (odd == 0) {
        val = INT_MIN;
        // alice 
        if (l1 <= r1) {
            val = max(val, mat[0][l1] + dfs(1 - odd, l1 + 1, r1, l2, r2));
            val = max(val, mat[0][r1] + dfs(1 - odd, l1, r1 - 1, l2, r2));
        }
        if (l2 <= r2) {
            val = max(val, mat[1][l2] + dfs(1 - odd, l1, r1, l2 + 1, r2));
            val = max(val, mat[1][r2] + dfs(1 - odd, l1, r1, l2, r2 - 1));
        }

    }
    else {
        val = INT_MAX;
        // bob
        if (l1 <= r1) {
            val = min(val, dfs(1 - odd, l1 + 1, r1, l2, r2));
            val = min(val, dfs(1 - odd, l1, r1 - 1, l2, r2));
        }
        if (l2 <= r2) {
            val = min(val, dfs(1 - odd, l1, r1, l2 + 1, r2));
            val = min(val, dfs(1 - odd, l1, r1, l2, r2 - 1));
        }
    }

    return val;
}




int main() {
    int t, cas = 0;


    ll a, b;
    scanf("%d", &t);

    while (t--) {
        init();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &mat[0][i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &mat[1][i]);
        }
        int ans = dfs(0, 1, n, 1, n);

        printf("%d\n", ans);
    }
    return 0;
}