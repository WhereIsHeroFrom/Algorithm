
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
#pragma warning(disable : 4996)

const int maxl = 20;
const int invalidstate = -123456789;
int saturatedstate;
const int leadingzerostate = 11;
const int maxstate = leadingzerostate + 1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate][11][11];
int targetK;

/*
* 状态0：前缀数字最后位不是6，且未出现过连续3个6；
* 状态1：前缀数字最后位连续6的个数为1个，且未出现过连续3个6；
* 状态2：前缀数字最后位连续6的个数为2个，且未出现过连续3个6；
* 状态3：已经出现过连续3个6，饱和状态；
*/
bool isEndStateValid(stType state) {
    return (state == saturatedstate);
}

stType nextState(stType st, int digit) {
    if (st == leadingzerostate) {
        if (digit == 0) {
            return leadingzerostate;
        }
        st = 0;
    }
    if (st == saturatedstate) {
        return saturatedstate;
    }
    if (digit == targetK) {
        return st + 1;
    }
    return 0;
}

void init() {
    memset(f, inf, sizeof(f));
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if (n == 0)
        return isEndStateValid(state) ? 1 : 0;
    ll sum = f[n][state][targetK][saturatedstate];
    if (lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for (int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if (invalidstate != st)
            sum += dfs(n - 1, st, nextlim, d);
    }
    if (lim) f[n][state][targetK][saturatedstate] = sum;
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
    init();
    int t;
    ll n;
    while (scanf("%d %d %lld", &saturatedstate, &targetK, &n) != EOF) {
        ll l = 0, r = INT_MAX - 4;
        r *= r;
        ll val = 0;
        while (l <= r) {
            ll m = (l + r) / 2;
            if (g(m) >= n) {
                r = m - 1;
                val = m;
            }
            else {
                l = m + 1;
            }
        }
        printf("%lld\n", val);
    }
    return 0;
}

/*
3
2
3
187

1666
2666
66666
*/
