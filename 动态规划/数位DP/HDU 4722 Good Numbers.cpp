#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 2010;
#define ll long long
int n;
ll f[20][10];        // f[i][j] 表示长度为 i 的数，每一位加和为 j 的数的个数
ll p[20];

void init() {
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 1; i <= 18; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) { // 最高位为 k
                int pre = (j - k + 10) % 10;
                f[i][j] += f[i - 1][pre];
            }
        }
    }
    p[0] = 1;
    for (int i = 1; i < 20; ++i) {
        p[i] = p[i - 1] * 10;
    }
}

ll dfs(int depth, ll val, int mod) {
    int d = (val / p[depth]) % 10;
    if (depth == 0) {
        return mod <= d ? 1 : 0;
    }
    ll ans = d * f[depth][0];
    ans += dfs(depth - 1, val, (mod - d + 10) % 10);
    return ans;
}

ll ans(ll val) {
    if (val < 0) {
        return 0;
    }
    if (val == 0) {
        return 1;
    }
    ll v = val;
    int cnt = 0;
    while (v) {
        v /= 10;
        ++cnt;
    }

    ll ret = dfs(cnt - 1, val, 0);
    return ret;
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld %lld", &a, &b);
        printf("Case #%d: %lld\n", ++cas, ans(b) - ans(a - 1));
    }
    return 0;
}