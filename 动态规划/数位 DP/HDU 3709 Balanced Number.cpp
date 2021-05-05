#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#pragma warning(disable : 4996)
const int maxl = 20;
const int base = 1540;
const int maxd = base*2;
#define ll long long

int n;
int d[maxl];
ll f[maxl][maxd][2][2];

ll dfs(int n, int state, bool hasnonzero, bool inrange, int pos, int d[]) {
    int x = 0;
    if (hasnonzero == 0) {
        if (pos - 1 > n) {
            return 0;
        }
    }
    if (n == 0) {
        return state == 0 ? 1 : 0;
    }

    ll& sum = f[n][state + base][hasnonzero][inrange];
    if (sum != -1) {
        return sum;
    }
    sum = 0;
    int maxdigit = inrange ? 9 : d[n];
    for (; x <= maxdigit; ++x) {
        int isinrange = (x < maxdigit) || inrange;
        int ishasnonzero = (x > 0) || hasnonzero;
        sum += dfs(n - 1, state + ((n>pos)? (x*(n-pos)) : -x*(pos-n)) , ishasnonzero, isinrange, pos, d);
        //printf("%d -> %d %d %d\n", n, state, x, sum);
    }
    return sum;
}

ll ans(ll val) {
    if (val < 0) {
        return 0;
    }
    if (val == 0) {
        return 1;
    }

    int stk[maxl];
    int n = 0;
    while (val) {
        stk[++n] = val % 10;
        val /= 10;
    }
    ll ret = 0;
    for (int i = 1; i <= n; ++i) {
        memset(f, -1, sizeof(f));
        ll asv = dfs(n, 0, 0, 0, i, stk);
        ret += asv;
    }
    return ret;
}

int main() {
    int t, cas = 0;
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", ans(b) - ans(a-1));
    }
    return 0;
}
