
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
#pragma warning(disable : 4996)

const int maxl = 20;
const int invalidstate = -123456789;
const int leadingzerostate = 12;
const int maxstate = leadingzerostate + 1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isEndStateValid(stType state) {
    return true;
}

stType nextState(stType st, int digit) {
    if (st == leadingzerostate) {
        return digit == 0 ? leadingzerostate : digit;
    }
    if (digit == 0) {
        return invalidstate;
    }
    return digit;
}

void init() {
    memset(f, inf, sizeof(f));
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if (n == 0)
        return isEndStateValid(state) ? 1 : 0;
    ll sum = f[n][state];
    if (lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for (int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if (invalidstate != st)
            sum += dfs(n - 1, st, nextlim, d);
    }
    if (lim) f[n][state] = sum;
    return sum;
}

ll g(ll x) {
    if (x < 0) return 0;
    if (x == 0) return 0;
    int d[maxl];
    int n = 0;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, leadingzerostate, false, d);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while (scanf("%lld %lld", &a, &b) != EOF) {
        int x = g(a) - g(b);
        ll l = 1, r = 1000000000;
        r *= r;
        ll ans;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (g(mid) >= x + 1) {
                r = mid - 1;
                ans = mid;
            }
            else {
                l = mid + 1;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}