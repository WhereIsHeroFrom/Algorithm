#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1010;
const int flag = -10209321;
#define ll int
int n, m;
ll f[maxn][maxn];
int mat[maxn][maxn];
vector<int> fact[maxn];

void init(int n, int m) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = flag;
        }
    }
}

ll dfs(int x, int y) {
    if (x == 1 && y == 1) {
        return mat[x][y];
    }
    if (x == 0 || y == 0) {
        return INT_MIN;
    }
    int &val = f[x][y];
    if (val != flag) {
        return val;
    }
    val = dfs(x - 1, y);
    val = max(val, dfs(x, y - 1));
    for (int i = 0; i < fact[y].size(); ++i) {
        int v = fact[y][i];
        val = max(val, dfs(x, v));
    }
    val += mat[x][y];
    return val;
}




int main() {
    int t, cas = 0;
    for (int i = 1; i < maxn; ++i) {
        for (int j = 1; j < i; ++j) {
            if (i % j == 0) fact[i].push_back(j);
        }
    }

    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        init(n, m);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &mat[i][j]);
            }
        }
        ll ans = dfs(n, m);
        printf("%d\n", ans);
    }
    return 0;
}