#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;


/*
矩阵二分快速幂
递推公式的神级加速，转换成矩阵幂求解；
矩阵相乘的最内层循环加和如果不溢出，则憋着不取模；
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 103
#define LL __int64
int MOD = 0;

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
				if(!v) continue;
				for (j = 0; j < other.m; j++) {
					if(other.pkData[k][j])
						ret.pkData[i][j] += v * other.pkData[k][j];
				}
			}
		}
	}

	static void Add(const Matrix &me, const Matrix& other, Matrix& ret) {
		ret.Reset(me.n, other.m);
		int i, j;
		for (i = 0; i < me.n; i++) {
			for (j = 0; j < me.m; j++) {
				ret.pkData[i][j] = (me.pkData[i][j] + other.pkData[i][j]);
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

LL A[MAXN][MAXN], BB[MAXN][MAXN];
Matrix Start, ret1, B, ret2;

int main() {
	int i, j;
	int n, m, k;
	while(scanf("%d %d %d", &n, &m, &k) != EOF && (n||m||k)) {
		
		int N = n + 1, v, u;
		
		for(i = 0; i < N; ++i) {
			for(j = 0; j < N; ++j) {
				A[i][j] = (i==j) ? 1 : 0;
			}
		}
		
		while(k--) {

			char c[10];
			scanf("%s", c);
			
			if(c[0] == 'g') {
				scanf("%d", &v);
				--v;
				for(i = 0; i < N; ++i) {
					A[i][v] = A[i][v] + A[i][N-1];
				}
				
			}else if(c[0] == 'e') {
				scanf("%d", &v);
				--v;
				for(i = 0; i < N; ++i) {
					A[i][v] = 0;
				}
			}else if(c[0] == 's') {
				scanf("%d %d", &u, &v);
				--u;
				--v;
				for(i = 0; i < N; ++i) {
					LL tmp = A[i][v];
					A[i][v] = A[i][u];
					A[i][u] = tmp;
				}
			}
		}
		
		for(i = 0; i < N; ++i) {
			BB[0][i] = (i==N-1) ? 1 : 0;
		}
		Start.Reset(N, N, A);
		B.Reset(1, N, BB);
		Matrix::GetPow(Start, m, ret1);
		Matrix::Multiply(B, ret1, ret2);
		
		for(i = 0; i < n; ++i) {
			if(i) {
				printf(" ");
			}
			printf("%I64d", ret2.get(0, i));
		}
		puts("");
	}
	return 0;
}

/*
3 1000000000 6
g 1
g 2
g 2
s 1 2
g 3
e 2

3 1000000000 5
g 1
g 2
g 2
s 1 2
g 3

3 0 6
g 1
g 2
e 1
g 3
s 1 2
s 2 3


3 1 6
g 1
g 2
e 1
g 3
s 1 2
s 2 3

3 2 6
g 1
g 2
e 1
g 3
s 1 2
s 2 3

3 3 6
g 1
g 2
e 1
g 3
s 1 2
s 2 3


4 5 6
g 1
g 2
g 3
g 1
e 2
s 1 3




*/

