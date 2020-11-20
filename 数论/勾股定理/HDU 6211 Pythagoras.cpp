/*
题意：
1） x^2 + y^2 = z^2;
2) x < y < z <= 10^9
3) gcd(x,y) = 1, gcd(x,z)=1, gcd(y,z)=1
4) 给定 a[0] ... a[2^k-1] ,求 sum{a[i] | i=y % 2^k}

题解：

...

*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define LL __int64
#define L int
#define eps 1e-8
#define MAXV 2000000000
#define MAXP 44723
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];
const double SQ_ADD = (1 + sqrt(2.0));

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
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			//需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
			for (int j = i*i; j < MAXP; j += i) {
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


#define MASK ((1<<17)-1)
int yANS[MASK + 1];

bool isCoPrime(int v, vector <factor>& ans) {
	int s = ans.size();
	for (int i = 0; i < s; ++i) {
		if (v % ans[i].prime == 0) {
			return false;
		}
	}
	return true;
}

int k;
int val[MASK + 1];
int S2[MAXP];

int main() {
	Eratosthenes();
	for (int i = 1; i < MAXP; ++i) S2[i] = i*i;

	vector<factor> f;
	int u = 0, v = 0;
	int maxt = sqrt(MAXV - 1) + eps;
	int c = 0;
	for (int t = 3; t <= maxt; t += 2) {
		int t2 = t * t;
		int maxs = t - 2;
		Factorization(t, f);
		//printf("%d %d\n", s, maxt);

		for (int s = 1; s <= maxs; s += 2) {
			u++;
			if (!isCoPrime(s, f)) continue;
			v++;
			int s2 = S2[s];
			if (s2 + t2 > MAXV) {
				break;
			}
			int x = ((t2 - s2) >> 1);
			int y = s * t;
			int z = ((t2 + s2) >> 1);

			//printf("%d %d %d %d %d\n", s, t, x, y, z);
			if (x > y) {
				y = x;
			}
			++yANS[y & MASK];
		}
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &k);
		for (int i = 0; i < (1 << k); ++i) {
			scanf("%d", &val[i]);
		}
		LL ans = 0;
		for (int i = 0; i <= MASK; ++i) {
			ans += (LL)val[i & ((1 << k) - 1)] * yANS[i];
		}
		printf("%I64d\n", ans);
	}

	return 0;
}