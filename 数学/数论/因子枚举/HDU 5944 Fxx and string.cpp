#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;


#define MAXP 65540
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

struct factor {
	LL prime;
	int count;
	factor() {
	}
	factor(LL p, int c) : prime(p), count(c)  {}
	void print() {
		printf("(%I64d, %d)\n", prime, count);
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
void Factorization(LL n, vector <factor>& ans) {
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

char str[100000];
int len, c = 0;


typedef void(*emunFactorCallback) (LL val, LL fact, LL eula);

// 调用 emunFactor(0, fact, 1, 1, func);
// 因式分解后递归枚举所有因子 
// 枚举因子的同时，同时计算每个因子的欧拉函数 
void emunFactor(int depth, vector <factor>& fact, LL val, LL now, LL eula, emunFactorCallback func) {
	if (fact.size() == depth) {
		func(val, now, eula);
		return;
	}

	factor &f = fact[depth];
	emunFactor(depth + 1, fact, val, now, eula, func);
	eula *= (f.prime - 1);
	now *= f.prime;
	for (int i = 1; i <= f.count; ++i) {
		emunFactor(depth + 1, fact, val, now, eula, func);
		now *= f.prime;
		eula *= f.prime;
	}
}

void emunFactorCB(LL val, LL fact, LL eula) {
	if (fact == 1) {
		return;
	}

	if (val * fact > len) {
		return;
	}
	int i = val / fact;
	int k = val * fact;

	if (str[i] == 'y' && str[k] == 'x') {
		c++;
	}

	i = val * fact;
	k = val / fact;

	if (str[i] == 'y' && str[k] == 'x') {
		c++;
	}
}

vector <factor> fac[10010];

int main() {
	int i;
	Eratosthenes();
	for (i = 1; i < 10010; ++i) {
		Factorization(i, fac[i]);
	}

	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%s", &str[1]);
		c = 0;
		len = strlen(&str[1]);
		vector <factor> ans;
		for (i = 2; i <= len; ++i) {
			if (str[i] != 'r') {
				continue;
			}
			emunFactor(0, fac[i], i, 1, 1, emunFactorCB);
		}
		printf("%d\n", c);
	}

	return 0;
}

/*
10
yyyrrrrrrxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxrrrrrryyy
*/