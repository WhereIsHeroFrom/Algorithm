#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 1010;
const int invalidstate = -123456789;
const int saturatedstate = 11;
const int leadingzerostate = 10;
const int maxstate = saturatedstate * 100 + saturatedstate + 1;
const int base = 10;
const int inf = -1;
const int mod = 1000000007;
#define ll long long
#define stType int
ll f[maxl][maxstate];

/*
          [10]          表示前导零状态 
          [11]          表示饱和状态 
     [10][0-9]          表示一位数字 
    [0-9][0-9]          表示两位以上数字的最后两位
*/


bool isEndStateValid(stType state) {
	return state == saturatedstate;
}

stType nextState(stType st, int digit) {
    if(st == leadingzerostate) {
        // 前导零状态，接受0，还是保持前导零状态 
        if(digit == 0) {
            return leadingzerostate;
        }
        // 否则
        st = leadingzerostate * 100 + leadingzerostate;
    }else if(st == saturatedstate) {
        return saturatedstate;
    }
    int high = st/100, low = st%100;
    if(high == digit || low == digit) {
        return saturatedstate;
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
        sum %= mod;
    }
    if(lim) f[n][state] = sum;
    return sum;
}

bool check(char *s) {
    int v = 0;
    int len = strlen(s);
    if(len == 1) {
        return false;
    }
    for(int i = 0; i < len - 1; ++i) {
        if(s[i] == s[i+1]) {
            return true;
        }    
        if(i+2 < len && s[i] == s[i+2]) {
            return true;
        }
    }
    return false;
}

int st[maxl];
ll g(char *s, bool docheck) {
    int n = strlen(s);
    ll al = 0;
    for(int i = n; i >= 1; --i) {
        st[i] = ( s[n-i] - '0' );
        al = (al * 10 + st[i]) % mod;
    } 
    ll sum = dfs(n, leadingzerostate, false, st);
    
    if(docheck && check(s)) {
        --sum;  // 多减1个，加回来 
    }
    return sum;
}

char a[maxl], b[maxl];

int main() {
    int t, cas = 0;
    init();
    while ( scanf("%s %s", &a, &b) != EOF) {
        ll ans = g(b, false) - g(a, true);
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
