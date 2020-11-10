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
int MOD = 8191;

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

LL AArray[MAXN][MAXN] = {};
LL BArray[MAXN][MAXN] = {};

LL Exp(LL a, LL b, LL c) {
	if(b == 0) {
		return 1 % c;
	}
	LL tmp = Exp(a*a % c, (b>>1), c);
	if(b & 1) {
		tmp = tmp * a % c;
	}
	return tmp;
}


// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量

Matrix A, B, ret1, ret2;
LL C[MAXN][MAXN];


void ConstructComb(){
	int i, j;
	C[0][0] = 1 % MOD;
	for(i = 1; i < MAXN; ++i) {
		for(j = 0; j < MAXN; ++j) {
			if(j == 0) {
				C[i][j] = 1 % MOD;
			}else {
				C[i][j] = ( C[i-1][j] + C[i-1][j-1] ) % MOD;
			}
		}
	}
}

void ContructMatrix(LL f1, LL f2, LL a, LL b, LL k) {
	int i, j, r, c;
	AArray[0][0] = 1;
	for(r = k + 1; r >= 0; --r) {
		if(r) {
			AArray[r][0] = 0;
		}else {
			BArray[r][0] = (Exp(f1, k, MOD) + Exp(f2, k, MOD)) % MOD;
			for(c = 1; c < k + 2; ++c) {
				AArray[0][c] = AArray[1][c];
			}
			continue; 
		}
		
		for(c = 1; c < k + 2; ++c) {
			i = r - 1;
			j = c - 1;
			
			if(i + j > k) {
				AArray[r][c] = 0;
			}else {
				AArray[r][c] = C[k-i][j] * Exp(a, k-i-j, MOD) % MOD * Exp(b, j, MOD) % MOD; 
			}
		}
		
		BArray[r][0] = (Exp(f2, k+1-r, MOD) * Exp(f1, r-1, MOD)) % MOD;
		
	}
	A.Reset(k+2, k+2, AArray);
	B.Reset(k+2, 1, BArray);
	
	//A.Print();
	//B.Print();
}

int main() {
	int t;
	int f1, f2, a, b, n, m, k;
	scanf("%d", &t);
	while(t--) {
		
		scanf("%d %d %d %d %d %d %d", &f1, &f2, &a, &b, &k, &n, &m);
		MOD = m;
		ConstructComb();
		ContructMatrix(f1, f2, a, b, k);
		
		int ans = 0;
		if(n <= 2) {
			if(n >= 1) {
				ans += Exp(f1, k, MOD); 
			}
			
			if(n >= 2) {
				ans += Exp(f2, k, MOD);
			}
			ans %= MOD;
		}else {
			Matrix::GetPow(A, n-2, ret1);
			Matrix::Multiply(ret1, B, ret2);
			ans = ret2.get(0, 0);
		}
		printf("%d\n", ans);
	}
	int i;

	return 0;	
} 


/*
5

1 2 3 2 2 1 10000000
1 2 3 2 2 2 10000000
1 2 3 2 2 3 10000000
1 2 3 2 2 4 10000000


*/
