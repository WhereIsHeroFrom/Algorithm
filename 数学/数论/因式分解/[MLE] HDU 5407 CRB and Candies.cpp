/*
Eratosthenes 因子筛选
	在素数筛选的时候同时将因子筛选出来

Author: WhereIsHeroFrom
Update Time: 2021-06-03
Algorithm Complexity: O(n)
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1000005;
const int maxp = 80000;
#define ll long long

int primes[maxp];
bool notprime[maxn];

struct factor {
	int prime;
	char count;
	factor() :prime(0), count(0) {}
	factor(int p, int c) : prime(p), count(c) {}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};
vector < factor > vF[maxn];

// 厄尔多塞素数筛选法
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < maxn; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			vF[i].push_back(factor(i, 1));
			for (int j = i * 2; j < maxn; j += i) {
				notprime[j] = true;
				int val = j / i;
				int cnt = 1;
				while (val % i == 0) {
					val /= i;
					++cnt;
				}
				vF[j].push_back(factor(i, cnt));
			}
		}
	}
}

short primehash[maxn], hashcase = 0;
char primecnt[maxn];
char primemax[maxn];
const int mod = 1000000007;

ll Exp(ll a, ll n, ll Mod) {
	ll ans = 1;
	while (n) {
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

void add(int prime, int cnt) {
	if (primehash[prime] < hashcase) {
		primehash[prime] = hashcase;
		primecnt[prime] = cnt;
		primemax[prime] = cnt;
		return;
	}

	primecnt[prime] += cnt;
	primemax[prime] = max(primemax[prime], primecnt[prime]);
}

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int main() {
	Eratosthenes();
	int t, n;
	scanf("%d", &t);
	while (t--) {
		hashcase++;
		scanf("%d", &n);
		for (int m = 1; m <= n; ++m) {
			// n - m + 1
			// m
			int nm = n - m + 1;
			int m_ = m;
			int g = gcd(nm, m);
			nm /= g;
			m_ /= g;

			for (int k = 0; k < vF[nm].size(); ++k) {
				add(vF[nm][k].prime, vF[nm][k].count);
			}

			for (int k = 0; k < vF[m_].size(); ++k) {
				add(vF[m_][k].prime, -vF[m_][k].count);
			}
		}
		ll ans = 1;
		for (int i = 1; i <= primes[0]; ++i) {
			int p = primes[i];
			if (primehash[p] < hashcase) {
				continue;
			}
			ans *= Exp(p, primemax[p], mod);
			if (ans >= mod) ans %= mod;
		}
		printf("%d\n", (int)ans);
	}

	return 0;
}


