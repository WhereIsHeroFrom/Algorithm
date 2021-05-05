#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int maxstate = 1000;
const int startstate = 0;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isValidState(stType state) {
    if(state / 10 % 10 < 3) {
        return false;
    }
    if(state % 10 == 3) {
        return false;
    }
	return true;
}

int getDigitCode(int digit) {
    if(digit == 4) {
        return 1 << 0;
    }else if(digit == 8) {
        return 1 << 1;
    }else {
        return 0;
    }
}

stType nextState(stType preState, int digit) {
	if(preState == startstate) {
	    return digit * 100 + 10 + getDigitCode(digit);
    }
    int prenumber = preState / 100;
    int precnt = preState / 10 % 10;
    int precode = preState % 10;
    if(prenumber == digit) {
        if(++precnt > 3) {
            precnt = 3;
        }
    }else {
        prenumber = digit;
        if(precnt < 3) {
            precnt = 1;
        }
    }
    precode |= getDigitCode(digit);
    return prenumber * 100 + precnt * 10 + precode;
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
    for(int k = (state==startstate?1:0); k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, nextlim, d);
    }
    if(lim) f[n][state] = sum;
    return sum;
}

ll g(ll x) {
    int d[maxl];
    int n = 0;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, startstate, false, d);
}

bool check(ll a) {
    int d[maxl];
    int n = 0;
    ll val = a;
    while(val) {
        d[n++] = val % 10;
        val /= 10;
    }
    int flag = 0;
    int code = 0;
    for(int i = 0; i < n; ++i) {
        if(i+2 < n && d[i] == d[i+1] && d[i+1] == d[i+2]) {
            flag = 1;
        }
        code |= getDigitCode(d[i]);
    }
    if(code < 3 && flag == 1) {
        return true;
    }
    return false;
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    while (scanf("%lld %lld", &a, &b) != EOF) {
        printf("%lld\n", g(b) - g(a) + (check(a)?1:0) );
    }
    return 0;
}
