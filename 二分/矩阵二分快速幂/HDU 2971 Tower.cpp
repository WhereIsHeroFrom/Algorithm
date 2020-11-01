#include <iostream>
using namespace std;
 

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
						ret.pkData[i][j] -= MOD;
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
// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量
 

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

int a2, N, M;

void fill(LL CM, LL CCM) {
	int i, j;
	for(i = 0; i < 4; ++i) {
		for(j = 0; j < 4; ++j) {
			AArray[i][j] = 0;
		}
	}
	AArray[0][0] = AArray[0][3] = AArray[3][1] = AArray[1][3] = 1;
	AArray[2][2] = M - 1;
	AArray[0][1] = AArray[1][1] = CCM * 4 % M;
	AArray[0][2] = AArray[1][2] = ((- 4 * CM) % M + M) % M;
	AArray[2][1] = 2 * CM % M;
}
int main() {
	Matrix A, B, ret1, ret2;
	
	int t;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d %d", &a2, &N, &M);		
		LL C = a2;
		LL CCM = C * C % M;
		LL CM = C % M;
		MOD = M;
		// 构造列向量 
		BArray[0][0] = 1 + CCM;
		BArray[1][0] = CCM;
		BArray[2][0] = CM;
		BArray[3][0] = 1;
		
		// 构造矩阵
		fill(CM, CCM);
		A.Reset(4, 4, AArray); 
		
		LL ans;
		if(N == 1) {
			ans = 1 % M;
		}else if(N == 2) {
			ans = BArray[0][0];
		}else {
			Matrix::GetPow(A, N-2, ret1);
			B.Reset(4, 1, BArray);
			Matrix::Multiply(ret1, B, ret2);
			ans = ret2.get(0,0);
		}
		printf("%d\n", (int)ans );
		
	}
	
	return 0;
}
