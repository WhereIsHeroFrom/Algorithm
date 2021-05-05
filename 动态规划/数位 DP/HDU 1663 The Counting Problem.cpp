#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxl = 10;
const int maxstate = 2;    // 0 还没出现过非零数    1 已经出现了非零数 
const int maxd = 10; 
const int startstate = 0;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate][maxd];
ll p10[maxl];

bool isValidState(stType state) {
	return false;
}

stType nextState(stType preState, int digit) {
    if(preState == startstate) {
        return digit == 0 ? startstate : 1;
    } 
	return 1;
}

void init() {
	memset(f, inf, sizeof(f));	
	p10[0] = 1;
	for(int i = 1; i < maxl; ++i) {
	    p10[i] = p10[i-1] * 10;
    }
}

ll dfs(int n, stType state, bool lim, ll val, int d[], int digit) {
    if(n == 0)
        return isValidState(state) ? 1 : 0;
    ll sum = f[n][state][digit];
    if(lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        sum += dfs(n-1, st, nextlim, val, d, digit);
        if(digit == k) {
            if(state == startstate && k == 0 && n > 1) {
                continue;
            }
            if(nextlim) {
                sum += p10[n-1];
            } else {
                sum += val % p10[n-1] + 1;
            }
        }
        
    }
    if(lim) f[n][state][digit] = sum;
    return sum;
}

ll g(ll x, int digit) {
    if (x < 0) return 0;
    if (x == 0) return digit == 0 ? 1 : 0;
    int d[maxl];
    int n = 0;
    ll xx = x;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, startstate, false, xx, d, digit);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while (scanf("%lld %lld", &a, &b) != EOF && (a || b)) {
        if(a > b) swap(a, b);
        for(int i = 0; i < 10; ++i) {
            if(i) printf(" ");
            printf("%lld", g(b, i) - g(a - 1, i));
        }
        puts(""); 
        
    }
    return 0;
}
