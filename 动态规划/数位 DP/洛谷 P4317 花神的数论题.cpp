#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 65;
const int maxstate = 65;
const int startstate = 0;
const int invalidstate = -1;
const int base = 2;
const int inf = -1;
const int mod = 10000007;
#define ll long long
#define stType int
ll f[maxl][maxstate][maxstate];

bool isValidState(stType state, int digitcnt) {
	return state == digitcnt;
}

/*
    0      前导零状态
    > 0    1的个数 
*/ 

stType nextState(stType preState, int digit) {
	if(preState == startstate) {
	    return (digit == 0) ?  startstate : 1;
    } 
    return preState + digit;
}

void init() {
	memset(f, inf, sizeof(f));	
}

ll dfs(int n, stType state, bool lim, int d[], int digitcnt) {
    if(n == 0)
        return isValidState(state, digitcnt) ? 1 : 0;
    ll sum = f[n][state][digitcnt];
    if(lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, nextlim, d, digitcnt);
    }
    if(lim) f[n][state][digitcnt] = sum;
    return sum;
}

ll g(ll x, int cnt) {
    if (x < 0) return 0;
    if (x == 0) return 1;
    int d[maxl];
    int n = 0;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, startstate, false, d, cnt);
}

ll exp(ll a, ll b, ll c) {
    if(b == 0) {
        return 1;
    }
    ll tmp = exp(a*a%c, b>>1, c);
    if(b & 1) {
        tmp = tmp * a % c;
    }
    return tmp;
}

int main() {
    int t, cas = 0;
    init();
    ll n;
    while (scanf("%lld", &n) != EOF ) {
        ll ans = 1;
        for(int i = 1; i <= 63; ++i) {
            ll val = g(n, i);
            ans = ans * exp(i, val, mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
