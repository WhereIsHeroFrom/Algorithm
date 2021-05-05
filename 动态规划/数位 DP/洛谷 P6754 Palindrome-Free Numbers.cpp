#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 1010;
const int invalidstate = -123456789;
const int leadingzerostate = 10;
const int maxstate = leadingzerostate * 100 + leadingzerostate + 1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

/*
          [10]          表示前导零状态  
     [10][0-9]          表示一位数字 
    [0-9][0-9]          表示两位以上数字的最后两位
*/


bool isEndStateValid(stType state) {
	return true;
}

stType nextState(stType st, int digit) {
    if(st == leadingzerostate) {
        // 前导零状态，接受0，还是保持前导零状态 
        if(digit == 0) {
            return leadingzerostate;
        }
        // 否则
        st = leadingzerostate * 100 + leadingzerostate;
    }
    int high = st/100, low = st%100;
    if(high == digit || low == digit) {
        return invalidstate;
    }
    return low * 100 + digit;
}
void init() {
	memset(f, inf, sizeof(f));	
}

ll dfs(int n, stType state, bool lim, int d[]) {
    if(n == 0)
        return isEndStateValid(state) ? 1 : 0;
    ll sum = f[n][state];
    if(lim && sum != inf) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : (d[n]);
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
    return dfs(n, leadingzerostate, false, d);
}

int main() {
    int t, cas = 0;
    ll a, b; 
    init();
    while ( scanf("%lld %lld", &a, &b) != EOF) {
        ll ans = g(b) - g(a-1);
        printf("%lld\n", ans);
    }
    return 0;
}
