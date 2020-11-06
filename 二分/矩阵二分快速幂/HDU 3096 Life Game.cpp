#include <iostream>

using namespace std;

/*
矩阵二分快速幂
递推公式的神级加速，转换成矩阵幂求解；
矩阵相乘的最内层循环加和如果不溢出，则憋着不取模；
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 100
#define LL __int64
int MOD = 1234567891;

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


/*
蜂巢坐标系 模板
记当前格子的编号记为(r, c)：
1）行列数目。行数为2N-1，列数和行号（从0开始数）强相关。令行号r<N，则列数为r+N；否则，列数为(3N-2)-r。
2）合法区域。如何判断一个坐标(x, y)是否在合法区域内，先判x，x的范围为[0, 2N-1)；再判y，y的范围为[0, 列数)，列数的计算参照1）。
3）6个邻居坐标。
a.左右邻居。   (r,c-1)和(r,c+1)。
b.上排邻居。   行号r<N时，上排邻居坐标(r-1,c-1)和(r-1,c)；否则，上排邻居坐标(r-1,c)和(r-1,c+1)。
c.下排邻居。    行号r<N-1时，下排邻居坐标(r+1,c)和(r-1,c+1)；否则，下排邻居坐标(r+1,c-1)和(r+1,c)。
注：以上邻居坐标都需要通过2）的合法区域坐标检测。
4）N = 6时的格子总数为1 + 6 + 12 + 18 + 24 + 30 = 91。 (每次加一圈，一圈个数为  6*(N-1))
Author: WhereIsHeroFrom
Update Time: 2018-3-29
Algorithm Complexity: O(N^2)
*/

struct HoneycombNode {
	int r, c;
	HoneycombNode() {}
	HoneycombNode(int _r, int _c) {
		r = _r;
		c = _c;
	}

	HoneycombNode left() {
		return HoneycombNode(r, c - 1);
	}

	HoneycombNode right() {
		return HoneycombNode(r, c + 1);
	}
};

// 蜂巢坐标系
#define MAXH 6

class HoneycombAxis {
	int n;
	int id[2 * MAXH][2 * MAXH];
	int idCount;
	HoneycombNode nodes[4 * MAXH*MAXH];

public:
	void init(int _n) {
		n = _n;
		int i, j;
		idCount = 0;
		for (i = 0; i < getRowCount(); ++i) {
			for (j = 0; j < getColCount(i); ++j) {
				id[i][j] = idCount;
				nodes[idCount] = HoneycombNode(i, j);
				++idCount;
			}
		}
	}

	// 返回行数
	int getRowCount() {
		return 2 * n - 1;
	}

	// 返回列数
	int getColCount(int r) {
		if (r < n) {
			return n + r;
		}
		else {
			return 3 * n - 2 - r;
		}
	}

	// 返回格子个数
	int getIDCount() {
		return idCount;
	}

	// 返回格子连续编号
	int getNodeID(HoneycombNode& node) {
		return id[node.r][node.c];
	}

	// 通过ID返回格子
	HoneycombNode getNode(int id) {
		return nodes[id];
	}

	// 返回当前格子的编号是否合法
	bool isValid(HoneycombNode& node) {
		// 超行
		if (node.r < 0 || node.r >= getRowCount()) {
			return false;
		}
		// 超列
		if (node.c < 0 || node.c >= getColCount(node.r)) {
			return false;
		}
		return true;
	}

	void getNeighbors(HoneycombNode now, int &retSize, HoneycombNode *ret) {
		HoneycombNode tmp[6];
		int i;

		// 本行邻居
		tmp[0] = now.left();
		tmp[1] = now.right();

		// 上排邻居
		if (now.r < n) {
			tmp[2] = HoneycombNode(now.r - 1, now.c - 1);
		}
		else {
			tmp[2] = HoneycombNode(now.r - 1, now.c);
		}
		tmp[3] = tmp[2].right();

		// 下排邻居
		if (now.r < n - 1) {
			tmp[4] = HoneycombNode(now.r + 1, now.c);
		}
		else {
			tmp[4] = HoneycombNode(now.r + 1, now.c - 1);
		}
		tmp[5] = tmp[4].right();


		retSize = 0;
		for (i = 0; i < 6; ++i) {
			if (isValid(tmp[i])) {
				ret[retSize++] = tmp[i];
			}
		}
	}
}HX;

HoneycombNode HN[MAXN];

Matrix A, B, ret1, ret2;

int main() {
	int N, L;
	int i, j, cas = 0;
	while (scanf("%d %d %d", &N, &MOD, &L) != EOF && (N || MOD || L)) {
		HX.init(N);
		int ALL = HX.getIDCount();

		for (i = 0; i < ALL; ++i) {
			for (j = 0; j < ALL; ++j) {
				AArray[i][j] = (i == j) ? 1 : 0;
			}
		}

		for (i = 0; i < ALL; ++i) {
			HoneycombNode node = HX.getNode(i);
			int v;
			scanf("%d", &v);
			BArray[i][0] = v;

			int size = 0;
			HX.getNeighbors(node, size, HN);

			for (j = 0; j < size; ++j) {
				++AArray[HX.getNodeID(HN[j])][i];
			}
		}
		A.Reset(ALL, ALL, AArray);
		B.Reset(ALL, 1, BArray);

		Matrix::GetPow(A, L, ret1);
		Matrix::Multiply(ret1, B, ret2);

		LL ans = 0;
		for (i = 0; i < ALL; ++i) {
			ans += ret2.get(i, 0);
		}

		printf("Case %d: %I64d\n", ++cas, ans);
	}


	return 0;
}