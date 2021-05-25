#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory.h>
#include <cmath>
using namespace std;

#pragma warning(disable : 4996)

#define ll long long
#define MAXP 65540

int primes[MAXP];
bool notprime[MAXP];

// 厄尔多塞素数筛选法 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			//需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
			for (ll j = (ll)i * i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// 欧拉函数 - 获取小于n的数中与n互素的数的个数 
// 举例：
// Phi(10) = 4
// 即 1、3、7、9  总共4个 
int Phi(int n) {
	if (n == 1) {
		return 1;
	}
	int ans = 1;
	// 素数试除 
	for (int i = 1; i <= primes[0]; i++) {
		int p = primes[i];
		if (n % p == 0) {
			n /= p;
			ans *= (p - 1);
			while (!(n % p)) {
				n /= p;
				ans *= p;
			}
		}
		if (n == 1) {
			return ans;
		}
	}
	return ans * (n - 1);
}


ll Exp(ll a, ll n, ll Mod) {
	ll ans = 1;
	if (a == 0 || a == 1) {
		return a % Mod;
	}
	while (n) {
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

int w[100010];
int o[100010];

const int inf = -1;
ll f(int l, int r, int maxv) {
    if(l == r) {
        return w[l];
    }
    if(l == o[l]) {
        return 1;
    }
    if(o[l] <= r) {
        r = o[l] - 1;
    }
    if(r - l >= 4) {
        return inf;
    }else if(l == r) {
        return w[l];
    }

    int power = f(l+1, r, maxv);
    if(power == inf) {
        return inf;
    }
    ll ans = 1;
    for(int i = 0; i < power; ++i) {
        ans *= w[l];
        if(ans >= maxv) {
            return inf;
        }
    }
    return ans;
}
int pp[10000];

ll g(int l, int r, int pidx) {
    if(pp[pidx] == 1) {
        return 0;
    }
    
    if(l == r) {
        return w[l] % pp[pidx];
    }    

    if(w[l] == 1) {
        return 1;
    }
    
    int eula =  pp[pidx+1];
    int power = f(l+1, r, eula);
    if( power == inf ) {
        return Exp(w[l],  g(l+1, r, pidx+1) + eula , pp[pidx]);
    }else {
        return Exp(w[l], power, pp[pidx]);
    }
}


int main() {
	Eratosthenes();
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
	    pp[0] = m;
	    for(int i = 1; ; ++i) {
	        pp[i] = Phi( pp[i-1] );
	        if(pp[i] == 1) break;
        } 
        
	    for(int i = 1; i <= n; ++i) {
	        scanf("%d", &w[i]);
        }
        int nowo = n+1;
        for(int i = n; i >= 1; --i) {
            if(w[i] == 1) {
                nowo = i;
            }
            o[i] = nowo;
        }
        
        int Q, l, r;
        scanf("%d", &Q);
        while(Q--) {
            scanf("%d %d", &l, &r);
            int ans = g(l, r, 0);
            printf("%d\n", ans);
        }

	}
	return 0;
}
