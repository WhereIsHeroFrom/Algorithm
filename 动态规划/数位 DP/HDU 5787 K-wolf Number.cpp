#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int leadingzerostate = 161052;
const int maxstate = leadingzerostate + 1;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];
short cas[maxl][maxstate], C;
int K;
int p11[10];

bool isValidState(stType state) {
	return true;
}

int getDigitCode(int digit) {
    return digit > 0 ? digit : 10;
}

stType nextState(stType preState, int digit) {
    if(preState == leadingzerostate) {
        if(digit == 0) 
            return leadingzerostate;
        preState = p11[K] - 1;
    }
    for(int i = 0; i < K - 1; ++i) {
        int predigit = (preState / p11[i]) % 11;
        if( predigit == digit ) {
            return invalidstate;
        }
    }
	return (preState * 11 + digit) %  p11[K];
}

void init() {
	memset(f, inf, sizeof(f));
	p11[0] = 1;
	for(int i = 1; i < 11; ++i) {
	    p11[i] = p11[i-1] * 11;
    }
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if(n == 0)
        return isValidState(state) ? 1 : 0;
    ll sum = f[n][state];
    if(lim && cas[n][state] == C) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, nextlim, d);
    }
    if(lim) f[n][state] = sum, cas[n][state] = C; 
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
    ++C;
    return dfs(n, leadingzerostate, false, d);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while (scanf("%lld %lld %d", &a, &b, &K) != EOF ) {
        printf("%lld\n", g(b) - g(a - 1));
    }
    return 0;
}
