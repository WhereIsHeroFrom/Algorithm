#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int maxstate = 9 * 19;
const int startstate = 0;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate][maxstate];
int cas[maxl][maxstate][maxstate], C;

bool isValidState(stType sumstate, stType modstate, stType mod) {
	return modstate == 0 && (sumstate == mod);
}

stType nextStateSum(stType preState, int digit) {
	return preState + digit;
}

stType nextStateMod(stType preState, int digit, int mod) {
	return (preState * 10 + digit) % mod;
}

void init() {
	memset(f, inf, sizeof(f));	
}

ll dfs(int n, stType sumstate, stType modstate, bool lim, int d[], int mod) {
    if(n == 0)
        return isValidState(sumstate, modstate, mod) ? 1 : 0;
    ll sum = f[n][sumstate][modstate];
    if(lim && cas[n][sumstate][modstate] == C ) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        bool nextlim = (k < maxv) || lim;
        sum += dfs(n-1, 
            nextStateSum(sumstate, k),
            nextStateMod(modstate, k, mod)
        , nextlim, d, mod);
    }
    if(lim) {
        f[n][sumstate][modstate] = sum;
        cas[n][sumstate][modstate] = C;
    }
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
    ll ans = 0; 
    for(int i = 1; i <= 9*n; ++i) {
        ++C;
        ans += dfs(n, 0, 0, false, d, i);
    }
    return ans;
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while (scanf("%lld %lld", &a, &b) != EOF) {
        printf("%lld\n", g(b) - g(a - 1));
    }
    return 0;
}
