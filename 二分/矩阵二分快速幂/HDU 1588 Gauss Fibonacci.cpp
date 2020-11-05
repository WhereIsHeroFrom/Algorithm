#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 4
#define LL __int64
LL MOD = 0;

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
					ret.pkData[i][j] += (v * other.pkData[k][j]);
					ret.pkData[i][j] %= MOD;
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
				printf("%d ", pkData[i][j]);
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
LL BArray[MAXN][MAXN] = {};

// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量

Matrix A, B, ret1, ret2;
Matrix AK, S, I, SN_2, SNK2, SNK;
Matrix SNK_EX, AB_1, T;

Matrix B2;


LL f(int n) {
	if (n <= 1) {
		return n;
	}
	else {
		Matrix::GetPow(A, n - 1, ret1);
		return ret1.get(0, 0);
	}
}

int main() {
	A.Reset(2, 2, AArray);

	int k, b, n, M;
	while (scanf("%d %d %d %d", &k, &b, &n, &M) != EOF) {
		MOD = M;

		int ans = 0;
		if (n == 0) {
			ans = 0;
		}
		else if (n == 1) {
			ans = f(b);
		}
		else if (n == 2) {
			ans = (f(b) + (k + b)) % MOD;
		}
		else {
			while (1) {

				if (b == 0) {
					if (k == 0) {
						ans = 0;
						break;
					}
					else {
						b = k;
						--n;
					}
				}

				// 计算 单位矩阵 I
				Matrix::Identity(2, I);
				// 计算 A^K 矩阵
				Matrix::GetPow(A, k, AK);
				// 计算 A^(b-1) 矩阵
				Matrix::GetPow(A, b - 1, AB_1);
				//      [A^K]
				// B2 = [ I ]
				B2.Reset(4, 2);
				B2.copyMatrix(AK, 0, 0);
				B2.copyMatrix(I, 2, 0);
				//    [A^k A^k]
				//S = [ O   I ]
				AK.getExtendMatrix(S, I);
				// 计算 S^((n-1)k)
				Matrix::GetPow(S, (LL)(n - 2), SN_2);
				//    [S(nk)]
				//    [  I  ]
				// S(nk) = A^k + A^2k + ... + A^nk
				Matrix::Multiply(SN_2, B2, SNK2);
				SNK2.getSubMatrix(SNK, 0, 0, 2, 2);
				// T = A^(b-1) + A^(k+b-1) + ... A^(ki+b-1)
				Matrix::Add(SNK, I, SNK_EX);
				Matrix::Multiply(AB_1, SNK_EX, T);
				ans = T.get(0, 0);

				break;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}