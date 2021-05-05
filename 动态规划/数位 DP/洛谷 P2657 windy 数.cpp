#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int maxl = 20;
const int maxstate = 12;
const int startstate = 11;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isValidState(stType state) {
	return true;
}

stType nextState(stType preState, int digit) {
    if(preState == startstate) {
        return digit ? digit : startstate;
    }
    int sub = preState - digit;
    if(sub < 0) sub = -sub;
    if(sub < 2) {
        return invalidstate;
    }
	return digit;
}

void init() {
	memset(f, inf, sizeof(f));	
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if(n == 0)
        return isValidState(state) ? 1 : 0;
    ll sum = f[n][state];
    if(lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, nextlim, d);
    }
    if(lim) f[n][state] = sum;
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
    return dfs(n, startstate, false, d);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while (scanf("%lld %lld", &a, &b) != EOF){
        printf("%lld\n", g(b) - g(a - 1));
    }
    return 0;
}
