#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 66;
const int maxstate = 2049;
const int startstate = 2048;
const int invalidstate = -1;
int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate][10];

bool isValidState(stType state) {
	return (startstate == state || 0 == state);
}

stType nextState(stType preState, int digit) {
    if(preState == startstate) {
        return digit == 0 ? startstate : (1<<digit);
    }
	return preState ^ (1 << digit);
}

void init() { 
	memset(f, inf, sizeof(f));	
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if(n == 0)
        return isValidState(state) ? 1 : 0;
    ll sum = f[n][state][base];
    if(lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, nextlim, d);
    }
    if(lim) f[n][state][base] = sum;
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
    while (scanf ("%d", &t) != EOF) {
    
        while(t--) {
            scanf("%d %lld %lld", &base, &a, &b);
            printf("%lld\n", g(b) - g(a - 1));
        }
    }
    return 0;
}
/*
2
2 4 9
3 1 10

2
2 1 100
5 1 100
*/
