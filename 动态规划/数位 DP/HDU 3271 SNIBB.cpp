#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#pragma warning(disable : 4996)
const int maxl = 64;
const int maxd = 310;
const int mod = (1e9 + 7);
#define ll long long

int n;
ll f[maxl][maxd][2];
int cas[maxl][maxd][2], C;
int B, M;

ll dfs(int n, int state, bool inrange, int d[]) {
    ll &sum = f[n][state][inrange];
    if (cas[n][state][inrange] == C) {
        return sum;
    }
    if (n == 0) {
        return (state == M) ? 1 : 0;
    }
    if (state > M) {
        return 0;
    }

    int maxdigit = inrange ? B-1 : d[n];
    sum = 0;
    cas[n][state][inrange] = C;
    for (int i = 0; i <= maxdigit; ++i) {
        int isinrange = (i < maxdigit) || inrange;
        sum += dfs(n - 1, state + i, isinrange, d);
    }
    return sum;
}

void init() {
    ++C;
}

ll ans(ll val) {
    if (val < 0) {
        return 0;
    }
    if (val == 0) {
        return M == 0 ? 1 : 0;
    }

    int stk[maxl];
    int n = 0;
    while (val) {
        stk[++n] = val % B;
        val /= B;
    }
    init();
    ll s = dfs(n, 0, 0, stk);
    return s;
}

int main() {
    int Q, cas = 0;
    int a, b, K;
    while (scanf("%d", &Q) != EOF) {
        scanf("%d %d %d %d", &a, &b, &B, &M);
        if (a > b) {
            swap(a, b);
        }
        printf("Case %d:\n", ++cas);
        if (Q == 1) {
            printf("%d\n", ans(b) - ans(a-1));
        }
        else {
            scanf("%d", &K);
            ll l = a, r = b;
            ll kth = K + ans(a - 1);
            ll v = -1;
            while (l <= r) {
                ll mid = (l + r) / 2;
                if (ans(mid) >= kth) {
                    r = mid - 1;
                    v = mid;
                }
                else {
                    l = mid + 1;
                }
            }
            if (v == -1) 
                printf("Could not find the Number!\n");
            else
                printf("%lld\n", v);
        }
    }
    return 0;
}
/*
1 0 10 10 3
2 0 100 10 1 4
1 0 10 2 1
*/
