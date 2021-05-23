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

const int MAX_NUMBER = 3165;
const int MAXP = 3165;                // (int)(sqrt(MAX_NUMBER*1.0) + 1);
#define ll long long

bool notprime[MAX_NUMBER];
int primes[MAXP];
int p10[10];
int eulaCache[10000002];

void Eratosthenes() {
    int i, j;
    p10[0] = 1;
    for(i = 1; i < 10; ++i) {
        p10[i] = p10[i-1] * 10;
    }
    
    notprime[1] = 1;
    
    // 1.枚举每个数
    for (i = 2; i < MAX_NUMBER; ++i) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            for (j = i + i; j < MAX_NUMBER; j += i) {
                notprime[j] = 1;
            }
        }
    }
}

int Phi(int n) {
    if(eulaCache[n]) {
        return eulaCache[n];
    }
    int sn = n;
	if(n == 1) {
		return eulaCache[sn] = 1;
	}
	int ans = 1; 
	// 素数试除 
	for(int i = 1; i <= primes[0]; i++) {
		int p = primes[i];
		if(n % p == 0) {
			n /= p;
			ans *= (p - 1);
			while( !(n % p) ) {
				n /= p;
				ans *= p;
			}
		}
		if(n == 1) {
			return eulaCache[sn] = ans;
		}
	}
	return eulaCache[sn] = ans * (n - 1);
}


ll Exp(ll a, ll n, ll Mod){
	ll ans = 1;
	if (a == 0 || a == 1) {
		return a % Mod;
	}
    a %= Mod;
	while (n){
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

const int inf = -1;
int f(int b, int x, int phic) {
    if(b == 1 || x == 0) {
        return 1;
    }
    if(x > 5) {
        return inf;
    }
    //printf("%d %d %d\n", b, x, phic); 
    int power = f(b, x-1, phic);
    if(power == inf) {
        return inf;
    }
    int ans = 1;
    for(int i = 0; i < power; ++i) {
        ans *= b;
        if(ans >= phic) {
            return inf;
        }
    }
    return ans;
}

// fmod = b ^ fmod(x-1) % mod
int fmod(int b, int x, int mod) {
    if(b == 1) {
        return 1;
    }
    
    if(x == 0) {
        return 1 % mod;
    }
    
    if(mod == 1) {
        return 0;
    }
    
    int eulan = Phi(mod);
    
    int power = f(b, x-1, eulan);
    if(power == inf) {
        return Exp(b, fmod(b, x-1, eulan) + eulan, mod );
    }else {
        return Exp(b, power, mod);
    }
    
}

int has[110][110];

int main() {
    Eratosthenes();
    memset(has, -1, sizeof(has));

    int b, n, t;
    char fmt[100];
    while ( scanf("%d", &b) && b) {
        scanf("%d %d", &t, &n);
        if(has[b][t] == -1)
            has[b][t] = fmod(b, t, p10[7]);
        int ans = has[b][t] % p10[n];
        sprintf(fmt, "%%0%dd\n", n);
        printf(fmt, ans);
    }
    return 0;
}
