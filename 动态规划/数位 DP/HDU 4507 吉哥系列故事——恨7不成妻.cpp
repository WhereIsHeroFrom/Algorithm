#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#pragma warning(disable : 4996)
const int maxl = 22;
const int maxd = 7;
const int mod = (1e9 + 7);
#define ll long long

int n;
int d[maxl];
ll cnt[maxl][maxd][maxd][2];
ll sum[maxl][maxd][maxd][2];
ll sqr[maxl][maxd][maxd][2];
ll p[100];

struct Triple {
    ll cnt, sum, sqr;
    bool calc;
    void init() {
        calc = false;
    }
    bool isinit() {
        return calc;
    }
    void set(ll c, ll s1, ll s2) {
        cnt = c;
        sum = s1;
        sqr = s2;
        calc = true;
    }
}T[maxl][maxd][maxd][2];


Triple dfs(int n, int state1, int state2, bool inrange, int d[]) {
    Triple& now = T[n][state1][state2][inrange];
    if (now.isinit()) {
        return now;
    }
    if (n == 0) {
        if (state1 && state2) {
            now.set(1, 0, 0);
        }
        else {
            now.set(0, 0, 0);
        }
        return now;
    }
 
    int maxdigit = inrange ? 9 : d[n];
    ll cnt = 0, sum = 0, sqr = 0;
    for (int i = 0; i <= maxdigit; ++i) {
        if (i == 7) {
            continue;
        }
        int isinrange = (i < maxdigit) || inrange;
        Triple t = dfs(n - 1, (state1 + i) % 7, (state2 * 10 + i) % 7, isinrange, d);
        sqr += (p[2 * n - 2] * t.cnt % mod * i * i % mod + p[n-1] * t.sum % mod * i * 2 % mod + t.sqr) % mod;
        sum += (t.sum + p[n - 1] * i % mod * t.cnt) % mod;
        cnt += t.cnt;

        sqr %= mod;
        sum %= mod;
        cnt %= mod;
    }
    now.set( cnt, sum, sqr);
    return now;
}

void init() {
    for (int i = 1; i < maxl; ++i) {
        for (int j = 0; j < maxd; ++j) {
            for (int k = 0; k < maxd; ++k) {
                for (int l = 0; l < 2; ++l) {
                    T[i][j][k][l].init();
                }
            }
        }
    }
    p[0] = 1;
    for (int i = 1; i < 100; ++i) {
        p[i] = p[i - 1] * 10 % mod;
    }
}

ll ans(ll val) {
    if (val < 0) {
        return 0;
    }
    if (val == 0) {
        return 0;
    }

    int stk[maxl];
    int n = 0;
    while (val) {
        stk[++n] = val % 10;
        val /= 10;
    }
    init();
    Triple ret = dfs(n, 0, 0, 0, stk);
    return ret.sqr;
}

ll check(ll a, ll b) {
    ll ans = 0;
    for (ll i = a; i <= b; ++i) {
        if (i % 7 == 0) {
            continue;
        }
        int stk[maxl];
        int n = 0;
        ll val = i;
        while (val) {
            stk[++n] = val % 10;
            val /= 10;
        }
        bool f = false;
        int s = 0;
        for (int j = 1; j <= n; ++j) {
            if (stk[j] == 7) {
                f = true;
                break;
            }
            s += stk[j];
        }
        if (s % 7 == 0) {
            continue;
        }
        if (f) {
            continue;
        }
        ans += i * i;
        ans %= mod;
    }
    return ans % mod;
}
int main() {
    int t, cas = 0;
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", ((ans(b) - ans(a-1))%mod+mod)%mod  );
        //printf("%lld\n", check(a, b));
    }
    return 0;
}
/*
1000000000 1000200000
10000 20000
*/
