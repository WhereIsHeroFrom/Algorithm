#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXP 1000010
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

LL gcd(LL a, LL b) {
	return b ? gcd(b, a%b) : a;
}

struct factor {
	int prime, count;
	factor() {
	}
	factor(int p, int c) {
		prime = p;
		count = c;
	}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};

// 厄尔多塞素数筛选法 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			//需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
			for (LL j = (LL)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// 因式分解 - 将n分解成素数幂乘积的形式
// 举例：
// 252 = (2^2) * (3^2) * (7^1) 
// 则 ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
	ans.clear();
	if (n == 1) {
		return;
	}
	// 素数试除 
	for (int i = 1; i <= primes[0]; i++) {
		if (n % primes[i] == 0) {
			factor f(primes[i], 0);
			while (!(n % primes[i])) {
				n /= primes[i];
				f.count++;
			}
			ans.push_back(f);
		}
		if (n == 1) {
			return;
		}
	}
	// 漏网之素数， 即大于MAXP的素数，最多1个 
	ans.push_back(factor(n, 1));
}

LL G, X, Y, K;

int main() {
	Eratosthenes();
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%I64d %I64d %I64d", &X, &Y, &K);
		G = gcd(X, Y);
		vector <LL> ans;
		for (LL i = 1; i*i <= G; i++) {
			if (G % i == 0) {
				ans.push_back(i);
				if (G / i != i) {
					ans.push_back(G / i);
				}
			}
		}

		if (K > ans.size()) {
			printf("-1\n");
		}
		else {
			sort(ans.begin(), ans.end());
			printf("%I64d\n", ans[ans.size() - K]);
		}
	}
	return 0;
}