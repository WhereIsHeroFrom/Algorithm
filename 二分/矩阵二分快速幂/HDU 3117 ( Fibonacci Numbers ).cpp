#include <iostream>
#include <cmath>
using namespace std;


#define MAXN 20
#define MOD 10000

class Matrix {
public:
    int n, m;
    int d[MAXN][MAXN];
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
        for(i = 0; i < ret.n; i++) {
            for(j = 0; j < ret.m; j++) {
                ret.d[i][j] = 0;
                for(k = 0; k < m; k++) {
                    ret.d[i][j] += d[i][k] * other.d[k][j];
                    ret.d[i][j] %= MOD;
                }
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

__int64 f[100];

int main() {
    f[0] = 0;
    f[1] = 1;
    for(int i = 2; i < 100; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    int n;
    while( scanf("%d", &n) != EOF ) {
        if(n < 40) {
            printf("%I64d\n", f[n]);
        }else {
            Matrix M;
            M.n = M.m = 2;
            M.d[0][0] = M.d[0][1] = M.d[1][0] = 1;
            int c = M.getPow(n-1).d[0][0];
            
            double sf = sqrt(5.0);
            double p = (n*log( (sf+1)/2.0 ) + log(1.0) - log(sf) ) / log(10.0);
            int v = int( pow(10.0, p - int(p)) * 1000 );
            printf("%d...%04d\n", v, c);
        }
    }
    return 0;
}

