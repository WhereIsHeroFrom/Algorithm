#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 60
#define LL int
LL MOD = 2008;

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

LL AArray[MAXN][MAXN] = { 0 };
LL BArray[MAXN][MAXN] = { 0 };

// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量

const int MASK = (1 << 17) - 1;
int hashKey[MASK + 1], hashKeyCnt;
unsigned int hashValue[MASK + 1];

int HASH(unsigned int val) {
	int key = (val & MASK);
	while (1) {
		if (hashKey[key] == -1) {
			hashKey[key] = hashKeyCnt++;
			hashValue[key] = val;
			return hashKey[key];
		}
		else {
			if (hashValue[key] == val) {
				return hashKey[key];
			}
			key = ((key + 1) & MASK);
		}
	}
}

Matrix A, B, ret1, ret2;

Matrix SAM, SBM, SI;

int getAns(int N, int t, int v) {
	if (t <= 0) {
		return 0;
	}

	Matrix::Identity(N, SI);
	A.getExtendMatrix(SAM, SI);
	Matrix::GetPow(SAM, t, ret1);
	ret1.getSubMatrix(ret2, 0, N, N, N);

	Matrix::Multiply(ret2, B, ret1);
	return ret1.get(v, 0);
}


int main() {
	int m;
	while (scanf("%d", &m) != EOF) {
		memset(hashKey, -1, sizeof(hashKey));
		memset(AArray, 0, sizeof(AArray));
		hashKeyCnt = 0;
		while (m--) {
			unsigned int x, y;

			scanf("%u %u", &x, &y);
			int t = HASH(x);
			int s = HASH(y);
			++AArray[s][t];
			if (AArray[s][t] >= MOD) AArray[s][t] -= MOD;
		}
		int N = hashKeyCnt;
		A.Reset(N, N, AArray);
		int v1, v2, t1, t2;
		int k, ans;
		scanf("%d", &k);
		while (k--) {
			scanf("%d %d %d %d", &v1, &v2, &t1, &t2);
			int s = HASH(v1);
			int t = HASH(v2);
			if (s >= N || t >= N) {
				ans = 0;
			}
			else {
				for (int i = 0; i < N; ++i) {
					if (s == i) {
						BArray[i][0] = 1;
					}
					else {
						BArray[i][0] = 0;
					}
				}
				B.Reset(N, 1, BArray);
				ans = ((getAns(N, t2, t) - getAns(N, t1 - 1, t)) % MOD + MOD) % MOD;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

/*
6
1 2
1 3
2 3
3 2
3 1
2 1
3
1 2 0 0
1 2 1 100
4 8 3 50
*/