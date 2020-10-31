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

#define MAXP 10010
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

#define MAXN 4
#define LL __int64
LL MOD = 1234567891;

class Matrix {
private:
	int n, m;
	LL** pkData;

	static Matrix s_kMatrix[64], s_kMultiplyTemp;

	void _Alloc() {
		// 之所以把空间放在堆上，是因为当MAXN很大时，栈上分配不了这么多空间
		pkData = new LL *[MAXN];
		for (int i = 0; i < MAXN; ++i) {
			pkData[i] = new LL[MAXN];
		}
	}

	void _Dealloc() {
		if (pkData) {
			// 先释放低维空间，再释放高维的
			for (int i = 0; i < MAXN; ++i) {
				delete[] pkData[i];
			}
			delete[] pkData;
			pkData = NULL;
		}
	}
public:
	Matrix() : n(0), m(0), pkData(NULL) {
		_Alloc();
	}
	virtual ~Matrix() {
		_Dealloc();
	}

	LL get(int i, int j) const {
		return pkData[i][j];
	}

	int getN() const {
		return n;
	}

	static void Identity(int _n, Matrix& ret) {
		ret.n = ret.m = _n;
		int i, j;
		for (i = 0; i < _n; i++) {
			for (j = 0; j < _n; j++) {
				ret.pkData[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	static void GetPow(Matrix& raw, unsigned __int64 e, Matrix& ret) {
		int index = 1;
		Matrix::Identity(raw.getN(), ret);       // 0次幂
		Matrix::s_kMatrix[1].Copy(raw);          // 1次幂
		while (e) {
			if (e & 1) {
				Matrix::Multiply(ret, Matrix::s_kMatrix[index], Matrix::s_kMultiplyTemp);
				ret.Copy(Matrix::s_kMultiplyTemp);
			}
			e >>= 1;
			Matrix::Multiply(Matrix::s_kMatrix[index], Matrix::s_kMatrix[index], Matrix::s_kMatrix[index + 1]);
			++index;
		}
	}

	static void Multiply(const Matrix &me, const Matrix& other, Matrix& ret) {
		// assert(m == other.n);
		ret.Reset(me.n, other.m);
		int i, j, k;
		for (i = 0; i < me.n; i++) {
			for (k = 0; k < me.m; k++) {
				LL v = me.pkData[i][k];
				for (j = 0; j < other.m; j++) {
					ret.pkData[i][j] += v * other.pkData[k][j];
					if (ret.pkData[i][j] >= MOD) {
						ret.pkData[i][j] %= MOD;
					}
				}
			}
		}
	}

	void Reset(int nn, int mm, LL data[][MAXN]) {
		n = nn;
		m = mm;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				pkData[i][j] = data[i][j];
			}
		}
	}

	void Reset(int nn, int mm) {
		n = nn;
		m = mm;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				pkData[i][j] = 0;
			}
		}
	}

	void Copy(const Matrix& other) {
		n = other.n;
		m = other.m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				pkData[i][j] = other.pkData[i][j];
			}
		}
	}



	// | A  A |
	// | O  I |
	// I 需要手动调用 Identity(n);
	// 扩展矩阵用于求A + A^2 + A^3 + ... + A^n
	void getExtendMatrix(Matrix& ret, Matrix& I) {
		ret.n = ret.m = n * 2;
		ret.copyMatrix(*this, 0, 0);
		ret.copyMatrix(*this, 0, n);
		ret.copyMatrix(I, n, n);
	}

	// 将矩阵A拷贝到当期矩阵的(r, c)位置
	void copyMatrix(Matrix& A, int r, int c) {
		for (int i = r; i < r + A.n; i++) {
			for (int j = c; j < c + A.n; j++) {
				pkData[i][j] = A.pkData[i - r][j - c];
			}
		}
	}

	void Print() {
		int i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%d ", pkData[i][j]);
			}
			puts("");
		}
	}
};

Matrix Matrix::s_kMatrix[64];
Matrix Matrix::s_kMultiplyTemp;

LL AArray[][MAXN] = {
	{ 1, 4, 4, 1 },
	{ 0, 4, 4, 1 },
	{ 0, 2, 1, 0 },
	{ 0, 1, 0, 0 },
};

LL BArray[][MAXN] = {
	{ 1 },
	{ 1 },
	{ 0 },
	{ 0 },
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
	Matrix A, B, ret, tmp;
	A.Reset(4, 4, AArray);
	B.Reset(4, 1, BArray);
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
			Matrix::GetPow(A, n - 1, ret);
			Matrix::Multiply(ret, B, tmp);
			LL v = Exp(x, tmp.get(0, 0) + sph, s + 1);
			printf("%I64d\n", v);
		}

	}

	return 0;
}