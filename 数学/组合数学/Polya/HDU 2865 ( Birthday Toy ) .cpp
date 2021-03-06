#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

#define MAXN 3
#define MAXP 65540
#define MOD 1000000007
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

class Matrix {
public:
    int n, m;
    LL d[MAXN][MAXN];
    Matrix() {
        n = m = 0;
        int i, j;
        for(i = 0; i < MAXN; i++) {
            for(j = 0; j < MAXN; j++) {
                d[i][j] = 0;
            }
        }
    }
    Matrix operator *(const Matrix& other) {
        Matrix ret;
        ret.n = n;
        ret.m = other.m;
        int i, j, k;
        for(j = 0; j < ret.m; j++) {
            for(i = 0; i < ret.n; i++) {
                ret.d[i][j] = 0;
                for(k = 0; k < m; k++) {
                    ret.d[i][j] += d[i][k] * other.d[k][j];
                }                             
                if (ret.d[i][j] >= MOD) ret.d[i][j] %= MOD;           
            }
        }
        return ret;
    }
    
    Matrix Identity(int _n) {
        Matrix I;
        I.n = I.m = _n;
        int i, j;
        for(i = 0; i < _n; i++) {
            for(j = 0; j < _n; j++) {
                I.d[i][j] = (i == j) ? 1 : 0;
            }
        }
        return I;
    }
    
    Matrix getPow(int e) {
        Matrix tmp = *this;
        Matrix ret = Identity(n);
        while(e) {
            if(e & 1) {
                ret = ret * tmp;
            }
            e >>= 1;
            tmp = tmp * tmp;
        }
        return ret;
    }

    // | A  A |
    // | O  I |
    // 扩展矩阵用于求A + A^2 + A^3 + ... + A^n
    Matrix getExtendMatrix() {
        Matrix ret;
        ret.n = ret.m = n * 2;
        ret.copyMatrix( *this, 0, 0);
        ret.copyMatrix( *this, 0, n);
        ret.copyMatrix( Identity(n), n, n);
        return ret;
    }

    // 将矩阵A拷贝到当期矩阵的(r, c)位置
    void copyMatrix(Matrix A, int r, int c) {
        for(int i = r; i < r + A.n; i++) {
            for(int j = c; j < c + A.n; j++) {
                d[i][j] = A.d[i-r][j-c];
            }
        }
    }
    
    void Print() {
        int i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                printf("%d ", d[i][j]);
            }
            puts("");
        }
    }
};

// 扩展欧几里得
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
     }
}

struct factor {
    int prime, count;
    factor() {
    } 
    factor(int p, int c) {
        prime = p;
        count = c;
    }
    void print() {
        printf("(%d, %d)\n", prime, count);
    }
};

// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for(int i = 2; i < MAXP; i++) {
        if( !notprime[i] ) {
            primes[ ++primes[0] ] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for(LL j = (LL)i*i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

// 因式分解 - 将n分解成素数幂乘积的形式
// 举例：
// 252 = (2^2) * (3^2) * (7^1) 
// 则 ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
    ans.clear();
    if(n <= 1) {
        return ;
    }
    // 素数试除 
    for(int i = 1; i <= primes[0]; i++) {
        if(n % primes[i] == 0) {
            factor f(primes[i], 0);
            while( !(n % primes[i]) ) {
                n /= primes[i];
                f.count ++;
            }
            ans.push_back(f);
        }
        if(n == 1) {
            return ;
        }
    }
    // 漏网之素数， 即大于MAXP的素数，最多1个 
    ans.push_back( factor(n, 1) );
}

LL power(LL a, LL b, LL c) {
    if(b == 0) {
        return 1 % c; 
    }
    LL x = power(a*a%c, b/2, c);
    if(b&1)
        x = x * a % c;
    return x;
}

// n颗珠子、m种颜色
int n, m;
// 环形项链的方案数
LL ans;
Matrix A;

LL G(int x) {
    int color = m - 1;
    if(x == 1) {
        return 1;
    }else if(x == 2) {
        return color - 2;
    }
    A.n = A.m = 2;
    A.d[0][0] = color - 2;
    A.d[0][1] = color - 1;
    A.d[1][0] = 1;
    A.d[1][1] = 0;
    Matrix B = A.getPow(x - 2);
    return (B.d[0][0] * (color - 2) % MOD + B.d[0][1]) % MOD;
}

LL F(int x) {
    int color = m - 1;
    return G(x - 1) * (color - 1) % MOD;
}

// 经过x步从i到i的方案数
int matrixStep(int x) {
    if(x <= 1) {
        return 0;
    }
    int color = m - 1;
    return F(x) * color % MOD;
}

int polyaPart(int fac, LL facEula) {
    return facEula % MOD * matrixStep(n/fac) % MOD;
}

// 因式分解后递归枚举所有因子 
// 枚举因子的同时，枚举每个因子的欧拉函数 
void emunFactor(int depth, vector <factor> fact, int now, int eula) {
    if(fact.size() == depth) {
        //printf("%d %d\n", now, eula);
        ans = (ans + polyaPart(now, eula) );
        if(ans >= MOD) ans %= MOD;
        return ;
    }
    factor &f = fact[depth];
    int i;
    emunFactor(depth+1, fact, now, eula);
    eula *= (f.prime - 1);
    now *= f.prime;
    for(i = 1; i <= f.count; ++i) {
        emunFactor(depth+1, fact, now, eula);
        now *= f.prime;
        eula *= f.prime;
    }
}

int main() {
    Eratosthenes();
    while(scanf("%d %d", &n, &m) != EOF) {
        ans = 0;
        vector <factor> v;
        Factorization(n, v);
        emunFactor(0, v, 1, 1);
        LL X, Y;
        ExpGcd(n, MOD, X, Y);
        X = ((X % MOD) + MOD) % MOD;
        X = X * ans % MOD * m % MOD;
        printf("%I64d\n", X);
    }
    return 0;
} 

