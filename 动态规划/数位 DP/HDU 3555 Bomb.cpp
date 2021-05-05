#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int invalidstate = -123456789;
const int saturatedstate = 10;
const int maxstate = 11;
const int base = 10;
const int inf = -1;
 
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isEndStateValid(stType state) {
	return (state == saturatedstate); 
}

stType nextState(stType st, int digit) {
    if(st == 4 && digit == 9) {
        st = saturatedstate;
    }else if(st != saturatedstate){
        st = digit;
    }
	return st;
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
    if (x == 0) return 0;
    int d[maxl];
    int n = 0;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, 0, false, d);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &a);
        printf("%lld\n", g(a));
    }
    return 0;
}
