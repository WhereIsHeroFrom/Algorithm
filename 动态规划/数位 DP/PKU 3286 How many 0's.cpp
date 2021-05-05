#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int invalidstate = -123456789;
const int saturatedstate = 10;
const int leadingzerostate = 11;
const int maxstate = leadingzerostate + 1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isEndStateValid(stType state, int targetdigit) {
	return false;
}

stType nextState(stType st, int digit, int len) {
    if(st == leadingzerostate) {
        if(digit == 0 && len > 1) {
            return leadingzerostate;
        }
        st = 0; 
    }
	return digit;
}

ll p10[maxl];
void init() {
	memset(f, inf, sizeof(f));	
	p10[0] = 1;
	for(int i = 1; i < maxl; ++i) {
	    p10[i] = p10[i-1] * 10;
    }
}

ll dfs(int n, stType state, bool lim, int d[], ll val, int targetdigit) {
    if(n == 0)
        return isEndStateValid(state, targetdigit) ? 1 : 0;
    ll sum = f[n][state]; 
    if(lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k, n);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st) {
            sum += dfs(n-1, st, nextlim, d, val, targetdigit);
            if(k == targetdigit) {
                if(targetdigit == 0) {
                    if(leadingzerostate == st) continue;
                }
                if(nextlim) {
                    sum += p10[n-1]; 
                }else {
                    
                    sum += val % p10[n-1] + 1;
                }
            }

        }
    }
    if(lim) f[n][state] = sum;

    return sum;
}

ll g(ll x, int digit) {
    if (x < 0) return 0;
    if (x == 0) return digit == 0 ? 1 : 0;
    int d[maxl];
    int n = 0;
    ll val = x;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, leadingzerostate, false, d, val, 0);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while ( scanf("%lld %lld", &a, &b)&& a >= 0 ) {        
        printf("%lld\n", g(b, 0) - g(a - 1, 0));
    }
    return 0;
}
