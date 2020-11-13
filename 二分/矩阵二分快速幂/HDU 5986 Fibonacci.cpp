#include <iostream>
#include <string>
#include <cmath>
#include <map>
using namespace std;


/*
矩阵二分快速幂
递推公式的神级加速，转换成矩阵幂求解；
矩阵相乘的最内层循环加和如果不溢出，则憋着不取模；
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 2
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
				if (j) printf(" ");
				printf("%d", pkData[i][j]);
			}
			puts("");
		}
	}
};

Matrix Matrix::s_kMatrix[64];
Matrix Matrix::s_kMultiplyTemp;

LL AArray[MAXN][MAXN] = {
	{ 1, 1 },
	{ 1, 0 }
};

LL BArray[MAXN][MAXN] = {
	{ 1 },
	{ 0 }
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
int Cycle[2000000];
int HasT[2000000], cas;
int F[2000000];

int getCycle(int p) {
	if (p == 1) {
		Cycle[p] = 1;
		return 1;
	}
	if (Cycle[p]) {
		return Cycle[p];
	}
	int fprepre = 0;
	int fpre = 1;
	int fnow;
	for (int i = 1;; ++i) {
		fnow = (fpre + fprepre) % p;
		if (fnow == 1 && fpre == 0) {
			Cycle[p] = i;
			return i;
		}
		fprepre = fpre;
		fpre = fnow;
	}
}

int X0;

int f(int v, int mod) {
	if (v == 0) {
		return 0;
	}
	MOD = mod;
	Matrix::GetPow(A, v - 1, ret1);
	Matrix::Multiply(ret1, B, ret2);
	return ret2.get(0, 0);
}

int XnModP(int n, int p) {
	if (n == 0) {
		return X0 % p;
	}
	int k = getCycle(p);
	int v = f(XnModP(n - 1, k), p);
	return v;
}

int P[100];

void CaclP(int p, int *P, int& PSize) {
	P[0] = p;
	for (int i = 1;; ++i) {
		P[i] = getCycle(P[i - 1]);
		if (P[i] == P[i - 1]) {
			PSize = i;
			return;
		}
	}
}

int TryToGetN(int X0, int *P, int PSize) {
	int i;
	for (i = 1; i <= PSize; ++i) {
		int v = XnModP(i, P[0]);
		if (v == X0 % P[0]) {
			return i;
		}
	}
	return -1;
}

int FindAllN(int X0, int *P, int PSize) {
	int i, j;
	++cas;
	F[0] = 0;
	F[1] = 1 % P[PSize];
	for (i = 2; i <= P[PSize]; ++i) {
		F[i] = (F[i - 1] + F[i - 2]);
		if (F[i] >= P[PSize]) F[i] %= P[PSize];
	}

	int T = X0 % P[PSize];
	for (i = 1;; ++i) {
		if (HasT[T] == cas) {
			return -1;
		}
		HasT[T] = cas;
		int TT = T;
		int ans = 0;
		for (j = PSize; j >= 0; j--) {
			TT = f(TT, P[j]);
		}
		if (TT == X0 % P[0]) {
			return PSize + i;
		}

		T = F[T];
	}
}

int main() {
	int t, p;
	int i, m;
	A.Reset(2, 2, AArray);
	B.Reset(2, 1, BArray);

	scanf("%d", &t);
	while (t--) {
		// p = 877
		scanf("%d %d", &X0, &p);
		CaclP(p, P, m);
		int ans = TryToGetN(X0, P, m);
		if (ans == -1) {
			ans = FindAllN(X0, P, m);
		}
		printf("%d\n", ans);

	}
	return 0;
}

/*
1111
0 1

0 2 1 2 2 2 3 2 4 2 5 2 6 2 7 2 8 2

0 3 1 3 2 3 3 3 4 3 5 3 6 3 7 3 8 3

0 4 1 4 2 4 3 4 4 4 5 4 6 4 7 4 8 4

1 100007 2 100007 3 100007 4 100007 5 100007 6 100007 7 100007 8 100007 9 100007 10 100007
*/