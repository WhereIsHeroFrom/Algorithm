/*
	扩展欧拉定理前置三要素
		1、素数筛选
		2、欧拉函数求解
		3、二分快速幂
	当 b >= phi(c) 时
		a^b mod c = a^(b mod phi(c) + phi(c)) mod c
*/

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
			//需要注意i*i超出整型后变成负数的问题，所以转化成 long long
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
	if (n == 1)
		return 1;
	int ans = 1;
	for (int i = 1; i <= primes[0]; i++) {
		int p = primes[i];
		if (0 == n % p) {
			n /= p;
			ans *= (p - 1);
			while (0 == n % p) {
				n /= p;
				ans *= p;
			}
		}
		if (n == 1)
			return ans;
	}
	return ans * (n - 1);
}

ll Exp(ll a, ll n, ll Mod) {
	ll ans = 1;
	while (n) {
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

const int inf = -1;
const ll infmax = 2000000000;
ll f(int n) {
	if (n == 0) {
		return 1;
	}
	int bas = n % 10;
	if (bas == 1) {
		// 1. 底数是1，无论指数是什么，都为1
		return 1;
	}

	ll power = f(n / 10);

	if (bas == 0) {
		// 2. 底数是0，那么根据 指数特殊处理
		if (power == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	if (power == inf) {
		// 2. 底数不为0和1，指数无穷大，那么自身也为无穷大
		return inf;
	}
	else {
		ll ans = 1;
		for (int i = 0; i < power; ++i) {
			ans *= bas;
			if (ans >= infmax) return inf;
		}
		return ans;
	}
}

ll g(int n, int m) {
	ll power = f(n / 10);

	if (power == inf) {
		int eula = Phi(m);
		return Exp(n % 10, g(n / 10, eula) + eula, m);
	}
	else {
		return Exp(n % 10, power, m);
	}
}

int main() {
	Eratosthenes();
	int n, m;
	int t;
	scanf("%d", &t);
	while (t--) {
		int p;
		scanf("%d %d", &n, &m);
		int ans = g(n, m);
		printf("%d\n", ans);
	}
	return 0;
}
/*
*/