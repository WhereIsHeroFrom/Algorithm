#include <iostream>
#include <string>
#include <cmath>
using namespace std;


/*
矩阵二分快速幂
递推公式的神级加速，转换成矩阵幂求解；
矩阵相乘的最内层循环加和如果不溢出，则憋着不取模；
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 60
#define LL __int64
int MOD = 1000000007;

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

	static void Add(const Matrix &me, const Matrix& other, Matrix& ret) {
		ret.Reset(me.n, other.m);
		int i, j;
		for (i = 0; i < me.n; i++) {
			for (j = 0; j < me.m; j++) {
				ret.pkData[i][j] = (me.pkData[i][j] + other.pkData[i][j]) % MOD;
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
		ret.Reset(n * 2, n * 2);
		ret.copyMatrix(*this, 0, 0);
		ret.copyMatrix(*this, 0, n);
		ret.copyMatrix(I, n, n);
	}

	// 获取 this 矩阵的 (r,c) - (n,m) 的子矩阵存到 ret
	void getSubMatrix(Matrix& ret, int r, int c, int n, int m) {
		ret.n = n;
		ret.m = m;
		for (int i = r; i < r + n; i++) {
			for (int j = c; j < c + m; j++) {
				ret.pkData[i - r][j - c] = pkData[i][j];
			}
		}
	}

	// 将矩阵A拷贝到当期矩阵的(r, c)位置
	void copyMatrix(Matrix& A, int r, int c) {
		for (int i = r; i < r + A.n; i++) {
			for (int j = c; j < c + A.m; j++) {
				pkData[i][j] = A.pkData[i - r][j - c];
			}
		}
	}

	void Print() {
		int i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%I64d ", pkData[i][j]);
			}
			puts("");
		}
	}
};

Matrix Matrix::s_kMatrix[64];
Matrix Matrix::s_kMultiplyTemp;

LL AArray[MAXN][MAXN] = {
};
LL BArray[MAXN][MAXN] = {
};

LL Exp(LL a, LL b, LL c) {
	if (b == 0) {
		return 1 % c;
	}
	LL tmp = Exp(a*a % c, (b >> 1), c);
	if (b & 1) {
		tmp = tmp * a % c;
	}
	return tmp;
}


// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量

Matrix A, B, ret1, ret2;


/*
线性同余
求解同余方程第一步是转化成一般式：ax + by = c，这个方程的求解步骤如下：
i) 首先求出a和b的最大公约数d = gcd(a, b)，那么原方程可以转化成d(ax/d + by/d) = c，容易知道(ax/d + by/d)为整数，如若d不能整除b，方程必然无解，算法结束；否则进入ii)。
ii) 由i)可以得知，方程有解则一定可以表示成 ax + by = c = gcd(a, b)*c'，那么我们先来看如何求解d = gcd(a, b) = ax + by，根据欧几里德定理，有：
d = gcd(a, b) = gcd(b, a%b) = bx' + (a%b)y' = bx' + [a-b*(a/b)]y' = ay' + b[x' - (a/b)y'], 于是有x = y',  y = x' - (a/b)y'。
由于gcd(a, b)是一个递归的计算，所以在求解(x, y)时，(x', y')其实已经利用递归计算出来了，递归出口为b == 0的时候（对比辗转相除，也是b == 0的时候递归结束），那么这时方程的解x0 = 1, y0 = 0。
Author: WhereIsHeroFrom
Update Time: 2018-3-23
Algorithm Complexity: O(log(n))
*/

LL GCD(LL a, LL b) {
	return b ? GCD(b, a%b) : a;
}

// 扩展欧几里得
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
	LL q, temp;
	if (!b) {
		q = a; X = 1; Y = 0;
		return q;
	}
	else {
		q = ExpGcd(b, a % b, X, Y);
		temp = X;
		X = Y;
		Y = temp - (a / b) * Y;
		return q;
	}
}

int Map[MAXN][MAXN];

int main() {
	int N, M, Q, u, K;
	int i, j;
	while (scanf("%d %d", &N, &M) != EOF) {
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				Map[i][j] = 0;
			}
		}
		while (M--) {
			int from, to;
			scanf("%d %d", &from, &to);
			--from;
			--to;
			Map[from][to] ++;
		}

		for (i = 0; i < N; ++i) {
			int c = 0;
			for (j = 0; j < N; ++j) {
				c += Map[i][j];
			}
			LL X, Y;
			if (c) {
				ExpGcd(c, MOD, X, Y);
				X = (X % MOD + MOD) % MOD;
			}
			else {
				X = 0;
			}

			for (j = 0; j < N; ++j) {
				AArray[j][i] = Map[i][j] ? X : 0;
			}
		}

		A.Reset(N, N, AArray);

		scanf("%d", &Q);

		while (Q--) {
			scanf("%d %d", &u, &K);
			--u;
			for (i = 0; i < N; ++i) {
				BArray[i][0] = (i == u) ? 1 : 0;
			}
			B.Reset(N, 1, BArray);
			Matrix::GetPow(A, K, ret1);
			Matrix::Multiply(ret1, B, ret2);

			for (i = 0; i < N; ++i) {
				printf("%d ", (int)ret2.get(i, 0));
			}
			puts("");
		}
	}
	return 0;
}

/*
3 6
1 2
1 3
2 1
2 2
2 3
3 2

10
1 0
2 0
3 0
1 1
2 1
3 1
1 2
2 2
3 2
*/