#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;
#pragma warning(disable : 4996)


const int maxl = 20;
const int invalidstate = -123456789;
const int leadingzerostate = 448;
const int maxstate = leadingzerostate + 1;
const int base = 10;
const int inf = -1;
const int mod = 21;
#define ll unsigned long long
#define stType int
ll f[maxl][maxstate];
int X, Y;

bool isEndStateValid(stType st) {
    if (leadingzerostate == st) {
        return (0 == X) && (0 == Y);
    }
    int four = st / mod;
    int seven = st % mod;

    return (four == X) && (seven == Y);
}

stType nextState(stType st, int digit) {
    if (st == leadingzerostate) {
        if (digit == 0) {
            return leadingzerostate;
        }
        st = 0;
    }
    int four = st / mod;
    int seven = st % mod;
    if (digit == 4) {
        ++four;
    }
    else if (digit == 7) {
        ++seven;
    }
    if (four > X || seven > Y) {
        return invalidstate;
    }

    return four * mod + seven;
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
    if (x == 0) return 1;
    int d[maxl];
    int n = 0;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, leadingzerostate, false, d);
}

int main() {
    int t, cas = 0, cascnt;

    ll a, b;
    scanf("%d", &t);
    while (t--) {
        int x;
        ll P, Q;
        ll val;
        scanf("%llu %llu %d %d", &P, &Q, &X, &Y);
        init();
        val = g(P);
        scanf("%d", &cascnt);
        printf("Case #%d:\n", ++cas);
        while (cascnt--) {
            ll K;
            scanf("%lld", &K);
            ll l = P + 1, r = Q;
            ll ans = -1;
            while (l <= r) {
                ll mid = (l + r) >> 1;
                if (g(mid) - val >= K) {
                    r = mid - 1;
                    ans = mid;
                }
                else {
                    l = mid + 1;
                }

            }
            if (ans == -1) {
                printf("Nya!\n");
            }
            else {
                printf("%llu\n", ans);
            }
        }

    }
    return 0;
}

/*

1
38 400 1 1
10
1
2
3
4
5
6
7
8
9
10

Case #1:
47
74
147
174
247
274
347
374
Nya!
Nya!
*/