#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 25;
const int flag = -10209321;
#define ll int
int n, m;
ll f[maxn][maxn][maxn];
int mat[2][maxn];

void init() {
    memset(f, -1, sizeof(f));
}

// 为了保证有序，再加入一维
ll dfs(int pre, int m, int n) {
    if (m < 0 || n < 0) {
        return 0;
    }
    if (m == 0 && n == 0) {
        return 1;
    }

    int &val = f[pre][m][n];
    if (val != -1) {
        return val;
    }
    val = 0;
    for (int i = pre; i <= m; ++i) {
        val += dfs(i, m - i, n - 1);
    }
    return val;
}




int main() {
    int t, cas = 0;


    ll a, b;
    scanf("%d", &t);

    while (t--) {
        init();
        scanf("%d %d", &m, &n);
        int ans = dfs(0, m, n);
        printf("%d\n", ans);
    }
    return 0;
}