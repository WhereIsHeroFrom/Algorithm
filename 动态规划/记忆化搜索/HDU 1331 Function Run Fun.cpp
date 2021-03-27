#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int inf = 1e9;
const int maxn = 30;
#define ll long long


int n;
ll f[maxn][maxn][maxn];

void init() {
    memset(f, 0x3f, sizeof(f));
}

ll dfs(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }
    if (a > 20 || b > 20 || c > 20) {
        return dfs(20, 20, 20);
    }
    ll &val = f[a][b][c];
    if (val != 0x3f3f3f3f3f3f3f3f) {
        return val;
    }
    if (a < b && b < c) {
        val = dfs(a, b, c - 1) + dfs(a, b - 1, c - 1) - dfs(a, b - 1, c);
    }
    else {
        val = dfs(a - 1, b, c) + dfs(a - 1, b - 1, c) + dfs(a - 1, b, c - 1) - dfs(a - 1, b - 1, c - 1);
    }

    return val;
}

int main() {
    int a, b, c;
    init();

    while (scanf("%d %d %d", &a, &b, &c) != EOF && (a != -1 || b != -1 || c != -1)) {
        ll ans = dfs(a, b, c);
        printf("w(%d, %d, %d) = %lld\n", a, b, c, ans);
    }
    return 0;
}