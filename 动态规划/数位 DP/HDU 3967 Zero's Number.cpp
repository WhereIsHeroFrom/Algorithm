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
const int leadingzerostate = 810;
const int maxstate = leadingzerostate + 1;
const int base = 10;
const int inf = -1;
const int mod = 21;
#define ll unsigned long long
#define stType int
ll f[maxl][maxstate][mod];
int K;

void stateSplit(stType st, int& isDivide, int& highMod, int& lowMod) {
    isDivide = (st & 1);
    st >>= 1;
    highMod = st / 20;
    lowMod = st % 20;
}

bool isEndStateValid(stType st) {
    int isDivide;
    int highMod;
    int lowMod;
    if (st == leadingzerostate) {
        return false;
    }
    stateSplit(st, isDivide, highMod, lowMod);
    if (!isDivide) {
        return 0;
    }
    return (highMod + lowMod) % K == 0 ? 1 : 0;
}

stType nextState(stType st, int split, int digit) {
    if (st == leadingzerostate) {
        if (split) {
            return invalidstate;
        }
        if (digit == 0) {
            return leadingzerostate;
        }
        st = 0;
    }
    int isDivide;
    int highMod;
    int lowMod;
    stateSplit(st, isDivide, highMod, lowMod);
    if (isDivide + split >= 2) {
        return invalidstate;
    }
    if (split) {
        lowMod = digit % K;
    }
    else {
        if (isDivide) {
            lowMod = (lowMod * 10 + digit) % K;
        }
        else {
            highMod = (highMod * 10 + digit) % K;
        }
    }
    isDivide |= split;
    return (highMod * 20 + lowMod) << 1 | (isDivide ? 1 : 0);
}

void init() {
    memset(f, inf, sizeof(f));
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if (n == 0)
        return isEndStateValid(state) ? 1 : 0;
    ll sum = f[n][state][K];
    if (lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for (int k = 0; k <= maxv; ++k) {
        bool nextlim = (k < maxv) || lim;
        for (int div = 0; div < 2; ++div) {
            stType st = nextState(state, div, k);
            if (invalidstate != st)
                sum += dfs(n - 1, st, nextlim, d);
        }
    }
    if (lim) f[n][state][K] = sum;
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
    init();
    ll A, B;
    while (scanf("%lld %lld %d", &A, &B, &K) != EOF) {
        ll ans = g(B) - g(A - 1);
        printf("%lld\n", ans);
    }
    return 0;
}

/*
333 333 3
10 100 2
*/