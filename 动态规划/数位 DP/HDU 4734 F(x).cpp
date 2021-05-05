#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxl = 20;
const int maxstate = 4700;
const int startstate = 0;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll int
#define stType int
ll f[maxl][maxstate];
int cas[maxl][maxstate], C;

bool isValidState(stType state, stType stateMax) {
	return state <= stateMax;
}

int mem[maxstate][10][10];
int p10[10];

stType nextState(stType preState, int digit, int n) {
    if(!mem[preState][digit][n])
        mem[preState][digit][n] = preState + digit * (1<<n);
	return mem[preState][digit][n];
}

void init() {
	memset(f, inf, sizeof(f));	
	p10[0] = 1;
	for(int i = 1; i < 10; ++i) {
	    p10[i] = p10[i-1] * 10;
    }
}

ll dfs(int n, stType state, bool lim, int d[], int FA) {
    if(state > FA) {
        return 0;
    }
    if(n == 0) {
        return 1;
    }
    ll sum = f[n][state];
    if(lim) {
        if(cas[n][state] == C) {
            return sum;
        }
        cas[n][state] = C;
        int nextstate = state + 9 * ((1<<n) - 1);
        if(nextstate <= FA) {
            return f[n][state] = p10[n];
        } 
    }   
    sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k, n-1);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, nextlim, d, FA);
    }
    if(lim) {
        f[n][state] = sum;
    }
    return sum;
}

ll aval(int x) {
    int v = 0;
    ll s = 0;
    while (x) {
        s += (x % base) * (1<<v);
        x /= base;
        ++v;
    }
    return s;
}

ll g(ll x, int K) {
    if (x < 0) return 0;
    if (x == 0) {
        return 0 <= K;
    }
    int d[maxl];
    int n = 0;
    while (x) {
        d[++n] = x % base;
        x /= base;
    }
    return dfs(n, startstate, false, d, K);
}

int main() {
    int t, cas = 0;
    init();
    int a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &a, &b);
        ++C;
        printf("Case #%d: %d\n", ++cas, g(b, aval(a)));
    }
    return 0;
}
