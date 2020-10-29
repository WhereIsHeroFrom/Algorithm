/*
欧拉函数：
n分解素因子表示为n = p1^e1 * p2^e2 * ... * pk^ek
则n的欧拉函数为 f(n) = (p1-1)p1^(e1-1) * (p2-1)p2^(e2-1) * ... * (pk-1)pk^(ek-1)

扩展欧拉定理：
a^b % c
当 b >= phi(c), a^b % c = a^(b % phi(c) + phi(c)) % c

Author: WhereIsHeroFrom
Update Time: 2020-10-29
Algorithm Complexity: O(sqrt(n))

*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXP 65540
#define LL __int64

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
			for (LL j = (LL)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// 欧拉函数 - 获取小于n的数中与n互素的数的个数 
// 举例：
// Phi(10) = 4
// 即 1、3、7、9  总共4个 
LL Phi(LL n) {
	if (n == 1) {
		return 1;
	}
	LL ans = 1;
	// 素数试除 
	for (int i = 1; i <= primes[0]; i++) {
		LL p = primes[i];
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

LL Exp(LL a, LL b, LL c) {
	if (b == 0) {
		return 1 % c;
	}
	LL tmp = Exp(a*a%c, (b >> 1), c);
	if (b & 1) {
		tmp = tmp * a % c;
	}
	return tmp;
}

// 扩展欧拉函数计算 a^b MOD c
LL ExtendPhi(LL a, LL b, LL c) {
	LL ph = Phi(c);
	if (b <= ph) {
		return Exp(a, b, c);
	}

	// 实际用到欧拉函数计算的时候
	// b 往往是一个很大的数，且 b 是个表达式，是矩阵或者递推式
	return Exp(a, b % ph + ph, c);
}




const LL MAXINT = (((LL)1) << 40) - 996;

LL f(LL n) {
	if (n == 0) {
		return 1;
	}

	LL a = n % 10;
	LL b = f(n / 10);

	if (!a) {
		return !b ? 1 : 0;
	}
	else if (a == 1) {
		return 1;
	}
	else {
		LL val = f(n / 10);
		LL ret = 1;
		while (val--) {
			ret *= a;
			if (ret > MAXINT) {
				return MAXINT;
			}
		}
		return ret;
	}
}

// f(n) = (n%10)^f(n/10) % m
LL f(LL n, LL m) {
	LL a = (n % 10);
	LL b = f(n / 10);

	if (!a && !b) {
		return 1 % m;
	}
	else if (a == 0 || m == 1) {
		return 0;
	}
	else if (a == 1) {
		return 1 % m;
	}


	if (b == MAXINT) {
		LL ph = Phi(m);
		LL b = f(n / 10, ph) + ph;
		return Exp(a, b, m);
	}

	return Exp(a, b, m);
}

int main() {
	Eratosthenes();
	int n, m;
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		printf("%I64d\n", f(n, m));
	}
	return 0;
}

/*
10
24 20
25 20
*/
