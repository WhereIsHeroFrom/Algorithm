#include <iostream>
#include <cstdio>
#include <cstring>
 
#define ll long long 
#define maxn 10010
const int MAXP = 10010;

ll FacCache[1320][10010];

int primes[MAXP];
int primeIndex[MAXP];
bool notprime[MAXP];
 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < MAXP; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
			primeIndex[i] = primes[0];
		    //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
			for(ll j = (ll)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// 二分快速幂 
ll Exp(ll a, ll n, ll Mod){
	ll ans = 1;
	while (n){
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

// 费马小定理 
ll Inv(ll a, ll p) {
    return Exp(a, p-2, p);
}

// 计算阶乘 模 p，存入 FacCache
void CalcCache(int n, int p) {
    int pIdx = primeIndex[p];
    FacCache[pIdx][0] = 1 % p;
    for(int i = 1; i <= n; ++i) {
        FacCache[pIdx][i] = FacCache[pIdx][i-1] * i;
        if(FacCache[pIdx][i] >= p) 
            FacCache[pIdx][i] %= p;
    }
}

void PreCaclCache() {
    for(int i = 1; i <= primes[0]; ++i) {
        int p = primes[i];
        CalcCache(p-1, p);
    }
}

// 小组合数模 p 
// n,m < p
ll SmallComb(int n, int m, int p) {
    if(m == 0 || m == n) {
        return 1;
    }else if(m > n) {
        return 0;
    }
    int pIdx = primeIndex[p];
    // n! * m!^(-1) * (n-m)!^(-1)
    ll ans = FacCache[pIdx][n] * Inv( FacCache[pIdx][m], p) % p;
    return ans * Inv( FacCache[pIdx][n-m], p) % p;
} 

// lucas 定理
ll Lucas (ll n, ll m, int p) {
    if(m == 0) {
        return 1;
    }
    return Lucas(n/p, m/p, p) * SmallComb(n % p, m % p, p) % p;
}
 
// 大组合数模 p
ll BigComb(ll n, ll m, int p) {
    if(p == 1) {
        return 0;
    }
    return Lucas(n, m, p);
} 

int main() {
    Eratosthenes();
    PreCaclCache();
    
    int n, k, p;
    int cases = 1;
    while(scanf("%d %d %d", &n, &k, &p) != EOF){ 
        if(k>n/2) k=n-k;
        int ans = (BigComb(n+1, k, p) + n - k) % p;
        printf("Case #%d: %d\n", cases++, ans);
    }
    return 0;
}
