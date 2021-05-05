#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int maxl = 20;
const int leadingzerostate = 20;
const int maxstate = 40;
const int basestate = 19; 
const int invalidstate = -1007;
const int base = 10;
const int inf = -1;
#define ll long long
#define stType int
ll f[maxl][maxstate];

bool isValidState(stType state) {
    if(state == leadingzerostate) {
        return false;
    }
	return state == 0;
}

stType nextState(stType preState, int digit) {
	if(preState == leadingzerostate) {
	    if(digit == 0) {
	        return leadingzerostate;
        }
        preState = 0;
    }
    if(digit == 4) {
        ++preState;
    }else if(digit == 7){
        --preState;
    }else {
        return invalidstate;
    }
    return preState;
}

void init() {
	memset(f, inf, sizeof(f));	
}
ll sortAns[217000];

ll dfs(int n, stType state, ll val, bool lim, int d[]) {
    if(n == 0) {
        if( isValidState(state) ) {
            sortAns[ ++sortAns[0] ] = val;
        }
        return isValidState(state) ? 1 : 0;
    }
    //ll sum = f[n][state + basestate];
    //if(lim && sum != inf) return sum;
    ll sum = 0;
    int maxv = lim ? base - 1 : d[n];
    for(int k = 0; k <= maxv; ++k) {
        stType st = nextState(state, k);
        bool nextlim = (k < maxv) || lim;
        if(invalidstate != st)
            sum += dfs(n-1, st, val*10 + k, nextlim, d);
    }
    //if(lim) f[n][state + basestate] = sum;
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
    return dfs(n, leadingzerostate, 0, false, d);
}

int main() {
    int t, cas = 0;
    init();
    ll a, b;
    g(1000000000000000000ll);
    sort(sortAns + 1, sortAns + 1 + sortAns[0]);
    //printf("%d\n", sortAns[0]);
    /*for(int i = 1; i <= sortAns[0]; ++i) {
        printf("%lld ", sortAns[i]);
    }*/
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &a);
        
        ll l = 1, r = sortAns[0];
        ll ans = -1;
        while(l <= r) {
            ll mid = (l + r) >> 1;
            if(sortAns[mid] >= a) {
                r = mid - 1;
                ans = sortAns[mid];
            }else {
                l = mid + 1;
            }
        }
        if(ans == -1) {
            for(int i = 0; i < 10; ++i) {
                printf("4");
            }
            for(int i = 0; i < 10; ++i) {
                printf("7");
            }
            puts("");
            continue;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
