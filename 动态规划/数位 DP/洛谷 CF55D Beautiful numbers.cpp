#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;          
const int maxlcm = 50;         // 1-9 这些数组合出开最多 48 种情况 
const int maxmod = 2525;       // 1-9 这些数组合出的最大的 lcm 为 2520 
const int startstate = 0;      
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxlcm][maxmod];
int cas[maxl][maxlcm][maxmod], C;
int LCM[512], LCMHash[maxmod];
int LCMList[maxmod], LCMCnt, LCMIndex[maxmod];
int nextv[maxmod][10];

int gcd(int a, int b) {
    return !b ? a : gcd(b, a%b);
}

int lcm(int a, int b) {
    return a / gcd(a,b) * b;
}

bool isValidState(stType lcmv, stType lcmmode) {
	return lcmmode % lcmv == 0;
}

stType nextStateBitmask(stType preState, int digit) {
	if(digit) {
	    preState |= (1 << (digit - 1));
    }
    return preState;
}

void init() {
	//memset(f, inf, sizeof(f));	
	++C;
}

ll dfs(int n, stType bitmaskstate, stType lcmmode, bool lim, int d[]) {
    int lcmmask = LCM[bitmaskstate];
    int lcm = LCMIndex[ lcmmask ];

    if(n == 0)
        return isValidState(lcmmask, lcmmode) ? 1 : 0;
    ll sum = f[n][lcm][lcmmode];
    if(lim && C == cas[n][lcm][lcmmode]) return sum;
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        bool nextlim = (k < maxv) || lim;
        
        sum += dfs(
            n-1, 
            nextStateBitmask(bitmaskstate, k),
            // (lcmmode * 10 + k) % 2520,
            nextv[lcmmode][k],
            nextlim, 
            d
        );
    }
    if(lim) {
        f[n][lcm][lcmmode] = sum;
        cas[n][lcm][lcmmode] = C;
    }
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
    ll ans = 0;
    //init();
    ans += dfs(n, 0, 0, false, d);
    return ans;
}

int main() {
    
    // 第 i 位，表示 digit = i+1 是否出现； 
    for(int i = 0; i < 512; ++i) {
        int v = 1;
        for(int j = 0; j < 9; ++j) {
            if(i & (1<<j)) {
                int d = j + 1;
                v = lcm(v, d);
            }
        }
        LCM[i] = v;
        LCMHash[v] = 1;
    }
    LCMCnt = 0;
    for(int i = 1; i < maxmod; ++i) {
        if(LCMHash[i]) {
            LCMList[LCMCnt] = i;
            LCMIndex[i] = LCMCnt;
            ++LCMCnt;
        }
    }
    for(int i = 0; i < 2520; ++i) {
        for(int j = 0; j < 10; ++j) {
            nextv[i][j] = (i * 10 + j) % 2520;
        }
    } 
    /*printf("%d\n", LCMCnt);
    for(int i = 0; i < LCMCnt; ++i) {
        printf("%d ", LCMList[i]);
    }
    puts("");*/
    
          
    int t, cas = 0;
    init();
    ll a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%I64d %I64d", &a, &b);
        printf("%I64d\n", g(b) - g(a - 1));
    }
    return 0;
}
/*
11
8000000000000000000 9000000000000000000
1746119600141635

*/
