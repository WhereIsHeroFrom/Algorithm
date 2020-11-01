#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 4
#define LL __int64
LL MOD = 1000000000 + 7;

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
		puts("");
	}
};

Matrix Matrix::s_kMatrix[64];
Matrix Matrix::s_kMultiplyTemp;

LL AArray[][MAXN] = {
	{ 5, 12 },
	{ 2, 5 },
};

LL BArray[][MAXN] = {
	{ 5 },
	{ 2 },
};

LL Exp(LL a, LL b, LL c) {
	if(b == 0) {
		return 1 % c;
	}
	LL tmp = Exp(a*a%c, (b>>1), c);
	if(b&1) {
		tmp = tmp * a % c;
	}
	return tmp;
}

// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量

Matrix A, B, ret1, ret2;
Matrix P[50000];
int has[50000];

Matrix GA, GB;

LL GAArray[][MAXN] = {
	{ 49, 120, 0, 0 },
	{ 20, 49, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
};

LL GBArray[][MAXN] = {
	{ 49, 120 },
	{ 20, 49 },
	{ 5, 12 },
	{ 2, 5 },
};


int main() {
	A.Reset(2, 2, AArray);
	B.Reset(2, 1, BArray);
	
	GA.Reset(4, 4, GAArray);
	GB.Reset(4, 2, GBArray);
	
	Matrix::GetPow(A, 2, ret1); ret1.Print();
	Matrix::GetPow(A, 4, ret1); ret1.Print();
	Matrix::GetPow(A, 8, ret1); ret1.Print();
	
	
	Matrix::GetPow(GA, 0, ret1); Matrix::Multiply(ret1, GB, ret2); ret2.Print();
	Matrix::GetPow(GA, 1, ret1); Matrix::Multiply(ret1, GB, ret2); ret2.Print();
	Matrix::GetPow(GA, 2, ret1); Matrix::Multiply(ret1, GB, ret2); ret2.Print();
	
	int t, c = 0;
	LL x;
	int M;
	scanf("%d", &t);
	while(t--) {
		memset(has, -1, sizeof(has));
		LL n, ans;
		scanf("%I64d %d", &x, &M);
		MOD = M;
		printf("Case #%d: ", ++c);
		if(M == 2) {
			printf("1\n");
		}else {
			int ans;
			if(x < 3) {
				Matrix::GetPow(A, (1<<x), ret1);
				Matrix::Multiply(ret1, B, ret2);
				ans = (ret2.get(0, 0) * 2 + M - 1) % M;
			}else {
				Matrix::GetPow(GA, x, ret1);
				Matrix::Multiply(ret1, GB, ret2);
				ret2.Print();
				ans = (ret2.get(0, 0) * 5 + ret2.get(0, 1) * 2) % M;
				ans = (ans * 2 + M - 1) % M;
			}
			printf("%d\n", ans); 
		}
	}
}
