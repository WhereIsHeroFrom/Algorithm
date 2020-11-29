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

#define MAXN 6

#define LL __int64

LL MOD = 1234567891;

class Matrix {
public:
	int n, m;
	LL d[MAXN][MAXN];
	Matrix() {
		n = m = 0;
		int i, j;
		for (i = 0; i < MAXN; i++) {
			for (j = 0; j < MAXN; j++) {
				d[i][j] = 0;
			}
		}
	}
	Matrix operator *(const Matrix& other) {
		Matrix ret;
		ret.n = n;
		ret.m = other.m;
		int i, j, k;
		for (j = 0; j < ret.m; j++) {
			for (i = 0; i < ret.n; i++) {
				ret.d[i][j] = 0;
				for (k = 0; k < m; k++) {
					ret.d[i][j] += d[i][k] * other.d[k][j];
					if (ret.d[i][j] >= MOD)
						ret.d[i][j] %= MOD;
				}
			}
		}
		return ret;
	}

	Matrix Identity(int _n) {
		Matrix I;
		I.n = I.m = _n;
		int i, j;
		for (i = 0; i < _n; i++) {
			for (j = 0; j < _n; j++) {
				I.d[i][j] = (i == j) ? 1 : 0;
			}
		}
		return I;
	}

	Matrix getPow(unsigned __int64 e) {
		Matrix tmp = *this;
		Matrix ret = Identity(n);
		while (e) {
			if (e & 1) {
				ret = ret * tmp;
			}
			e >>= 1;
			tmp = tmp * tmp;
		}
		return ret;
	}

	// | A  A |
	// | O  I |
	// 扩展矩阵用于求A + A^2 + A^3 + ... + A^n
	Matrix getExtendMatrix() {
		Matrix ret;
		ret.n = ret.m = n * 2;
		ret.copyMatrix(*this, 0, 0);
		ret.copyMatrix(*this, 0, n);
		ret.copyMatrix(Identity(n), n, n);
		return ret;
	}

	// 将矩阵A拷贝到当期矩阵的(r, c)位置
	void copyMatrix(Matrix A, int r, int c) {
		for (int i = r; i < r + A.n; i++) {
			for (int j = c; j < c + A.n; j++) {
				d[i][j] = A.d[i - r][j - c];
			}
		}
	}

	void Print() {
		int i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%d ", d[i][j]);
			}
			puts("");
		}
	}
};


#define MAXG 25
LL f[MAXG];
LL g[MAXG];

LL n, y, x, s;

int main() {
	f[0] = 0;
	f[1] = 1;
	g[0] = 0;
	g[1] = 1;
	Eratosthenes();

	int i;
	for (i = 2; i < MAXG; ++i) {
		f[i] = f[i - 1] * 2 + f[i - 2];
		g[i] = g[i - 1] + f[i] * f[i];
		//printf("%d %I64d\n", i, g[i]);
	}
	Matrix A;
	A.n = A.m = 4;
	A.d[0][0] = 1; A.d[0][1] = 4; A.d[0][2] = 4; A.d[0][3] = 1;
	A.d[1][0] = 0; A.d[1][1] = 4; A.d[1][2] = 4; A.d[1][3] = 1;
	A.d[2][0] = 0; A.d[2][1] = 2; A.d[2][2] = 1; A.d[2][3] = 0;
	A.d[3][0] = 0; A.d[3][1] = 1; A.d[3][2] = 0; A.d[3][3] = 0;

	Matrix B;
	B.n = 4; B.m = 1;
	B.d[0][0] = 1;
	B.d[1][0] = 1;
	B.d[2][0] = 0;
	B.d[3][0] = 0;

	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%I64d %I64d %I64d %I64d", &n, &y, &x, &s);
		n *= y;
		if (n < 25) {
			printf("%I64d\n", Exp(x, g[n], s + 1));
		}
		else {
			LL sph = Phi(s + 1);
			MOD = sph;
			LL v = Exp(x, (A.getPow(n - 1) * B).d[0][0] + sph, s + 1);
			printf("%I64d\n", v);
		}

	}

	return 0;
}