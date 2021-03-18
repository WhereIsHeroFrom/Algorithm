#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 85
#define LL int

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

    bool operator == (const Matrix& o) const {
        if (n != o.n || m != o.m) {
            return false;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (pkData[i][j] != o.pkData[i][j]) {
                    return false;
                }
            }
        }
        return true;
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



typedef int ValueType;
const int maxn = 105;
const ValueType inf = 1e9;
ValueType mat[maxn][maxn];

void init(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = (i == j) ? 0 : inf;
        }
    }
}

void addEdge(int u, int v, int w) {
    mat[u][v] = min(mat[u][v], w);
}

void FloydWarshall(int n) {
    int i, j, k;
    for (k = 0; k < n; ++k)
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}


Matrix M[maxn];
Matrix ret;
LL data[MAXN][MAXN];

int main() {
    int n, m;
    int i, j, k;
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        init(n);
        for (i = 0; i < n; ++i) {
            for (int r = 0; r < m; ++r)
            {
                for (int c = 0; c < m; ++c) {
                    scanf("%d", &data[r][c]);
                }
            }
            M[i].Reset(m, m, data);
        }
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                if (j == i) continue;
                Matrix::Multiply(M[i], M[j], ret);
                for (k = 0; k < n; ++k) {
                    if (k == j) continue;
                    if (ret == M[k]) {
                        addEdge(i, k, 1);
                    }
                }
            }
        }
        FloydWarshall(n);
        int Q;
        scanf("%d", &Q);
        while (Q--) {
            int u, v;
            scanf("%d %d", &u, &v);
            --u, --v;
            ValueType ans = mat[u][v];
            if (ans == inf) printf("Sorry\n");
            else printf("%d\n", ans);
        }


    }
    return 0;
}