#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxl = 110;
const int maxstate = 30;
const int startstate = 0;
const int invalidstate = -1;
const int mod = 1000000007; 
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isValidState(stType state) {
	return true;
}

/*
状态用两位表示：

第一位： 
    0    前导零状态
    1    尚未出现过递增
    2    出现过递增 

第二位：
    0-9  前缀的最后一位数字 
    
*/ 
stType nextState(stType preState, int digit) {
	if(preState == 0) {
	    return digit == 0 ? 0 : (10 + digit);
    }
    int bAsc = (preState / 10 == 2);
    if(bAsc) {
        if( digit < preState % 10 ) {
            return invalidstate;
        }
    }else {
        if(digit <= preState % 10) {
            return 10 + digit;
        }
    }
    return 20 + digit;
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
        sum %= mod;
    }
    if(lim) f[n][state] = sum;
    return sum;
}

int stk[maxl];

ll g(char *c) {
    if (c[0] == '0') return 0;
    int n = strlen(c);
    for(int i = n; i >= 1; --i) {
        stk[i] = c[n-i] - '0';
    }
    return dfs(n, startstate, false, stk);
}

char c[maxl];

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", c);
        printf("%lld\n", (g(c) - 1 + mod) % mod );
    }
    return 0;
}
