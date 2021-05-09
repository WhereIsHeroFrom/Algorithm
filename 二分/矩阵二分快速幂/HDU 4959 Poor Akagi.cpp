#include <iostream> 
#include <cmath>

using namespace std;

#define maxk 100010
#define ll long long
#define MOD 1000000007


/*
矩阵二分快速幂
递推公式的神级加速，转换成矩阵幂求解；
矩阵相乘的最内层循环加和如果不溢出，则憋着不取模；
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 3

class Matrix {
private:
    int n, m;
    ll** pkData;

    static Matrix s_kMatrix[64], s_kMultiplyTemp;

    void _Alloc() {
        // 之所以把空间放在堆上，是因为当MAXN很大时，栈上分配不了这么多空间
        pkData = new ll *[MAXN];
        for (int i = 0; i < MAXN; ++i) {
            pkData[i] = new ll[MAXN];
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

    ll get(int i, int j) const {
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
                ll v = me.pkData[i][k];
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

    void Reset(int nn, int mm, ll data[][MAXN]) {
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

ll AArray[MAXN][MAXN] = { 0 };
ll BArray[MAXN][MAXN] = { 0 };

// 1. 构造系数矩阵
// 2. 构造列向量
// 3. 二分幂矩阵 * 列向量

Matrix A, B, ret1, ret2;


// x + y * sqrt(5) 
struct Complex {
    ll x, y;
    
    Complex () {
    }
    Complex(ll _x, ll _y) : x(_x), y(_y) {
        if(x >= MOD) x %= MOD;
        if(y >= MOD) y %= MOD;
    }
    
    Complex(const Complex& p) {
        *this = Complex(p.x, p.y);
    }
    
    Complex operator + (const Complex& o) const {
        return Complex( x + o.x, y + o.y );
    }
    
    Complex operator * (const Complex& o) const {
        Complex ret;
        ret.x = (x * o.x) % MOD + y * o.y % MOD * 5 % MOD;
        ret.y = x * o.y % MOD + y * o.x % MOD;
        return Complex( ret.x, ret.y );
    }
    
    void print() {
        printf("<%lld, %lld * sqrt[5]>\n", x, y);
    }
    
    Complex getPow(ll n) {
        Complex ret(1, 0);
        Complex p = Complex(*this);
        while(n) {
            if(n & 1) {
                ret = ret * p;
            }
            p = p * p;
            n >>= (ll)1;
        }
        return ret;
    }
    
}p15[maxk], n15[maxk];

ll exp(ll a, ll b, ll c) {
    ll ret = 1 % c;
    ll p = a % c;
    while(b) {
        if(b & 1) {
            ret = ret * p;
            if(ret >= c) {
                ret %= c;
            }
        }
        b >>= 1;
        p = p * p;
        if(p >= c) p %= c;
    }
    return ret;
}

ll inv(ll x) {
    return exp(x, MOD-2, MOD);
}

ll Inv[maxk];
ll pow2[maxk], Inv2[maxk];

int main() {
    int i;
    p15[0] = Complex(1, 0);
    n15[0] = Complex(1, 0);
    for(i = 1; i < maxk; ++i) {
        p15[i] = p15[i-1] * Complex(1, 1);
        n15[i] = n15[i-1] * Complex(1, MOD-1);
    }
    for(i = 1; i < maxk; ++i) {
        Inv[i] = inv(i);
        if( i * Inv[i] % MOD != 1) {
            printf("oh no!");
        }
    }
    pow2[0] = Inv2[0] = 1;
    for(i = 1; i < maxk; ++i) {
        pow2[i] = pow2[i-1] * 2 % MOD;
        Inv2[i] = inv(pow2[i]);
        if( pow2[i] * Inv2[i] % MOD != 1) {
            printf("oh no!");
        }
    }
    

    int t;
    ll n;
    int j, k;
    
    scanf("%d", &t);
    
    while(t--) {
        scanf("%lld %d", &n, &k);
        
        AArray[0][0] = 1;
        AArray[1][0] = 0;
        AArray[2][0] = 0;
        
        BArray[0][0] = BArray[1][0] = 1;
        BArray[2][0] = 0;
        
        ll ans = 0;
        ll C = 1;
        for(j = 0; j <= k; ++j) {
            if(j) {
                C *= Inv[j];       if(C >= MOD) C %= MOD;
                C *= (k - j + 1);  if(C >= MOD) C %= MOD;
            }
            Complex e = p15[k-j] * n15[j];
            e.x = e.x * Inv2[k] % MOD;
            e.y = e.y * Inv2[k] % MOD;
            
            AArray[0][1] = AArray[1][1] = AArray[2][2] = e.x;
            AArray[0][2] = AArray[1][2] = e.y * 5 % MOD;
            AArray[2][1] = e.y;
            A.Reset(3, 3, AArray);
            B.Reset(3, 1, BArray);
            Matrix::GetPow(A, n, ret1);
            Matrix::Multiply(ret1, B, ret2);
            ans += ret2.get(0,  0) * C % MOD;
            
            if(ans >= MOD) ans %= MOD;
        }
        printf("%lld\n", ans);
    }
    
    return 0;
}
