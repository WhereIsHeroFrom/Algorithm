#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int maxstate   = 100010;
const int leadingzerostart = 100008;
const int invalidstate = -1;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType ll
ll f[maxl][maxstate];
ll X;
bool digithash[10];

bool isValidState(stType state) {
    if(state == startstate) {
        return true;
    }
	return state == 0;
}

stType nextState(stType st, int digit) {
    if(preState == startstate) {
        if(digit == 0) {
            return startstate;
        }
    }
    if(!digithash[digit]) {
        return invalidstate;
    }
    if(preState == startstate) {
        preState = 0;
    }
	return (preState * 10 + digit) % X;
}

void init() {
	memset(f, inf, sizeof(f));	
	memset(digithash, false, sizeof(digithash));
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
    return dfs(n, startstate, false, d);
}

char c[100];
int main() {
    int t, cas = 0;
    
    ll a, b;
    while (scanf("%lld %lld %lld", &X, &a, &b) != EOF) {
        init();
        scanf("%s", c);
        for(int i = 0; c[i]; ++i) {
            digithash[ c[i] - '0' ] = true;
        }
        if(X < 100000) {
            printf("%lld\n", g(b) - g(a - 1));
        }else {
            ll nX = 0;
            int ans = 0;
            while(nX <= b) {
                if(nX >= a) {
                    ll v = nX;
                    while(v) {
                        if( !digithash[ v % 10 ]){
                            break;
                        }
                        v /= 10;
                    }
                    if(!v) {
                        ++ans;
                    }
                }
                nX += X;
            }
            printf("%d\n", ans);
        } 
        
    }
    return 0;
}
