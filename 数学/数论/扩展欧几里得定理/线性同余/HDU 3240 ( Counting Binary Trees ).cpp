/*
线性同余
求解同余方程第一步是转化成一般式：ax + by = c，这个方程的求解步骤如下：
      i) 首先求出a和b的最大公约数d = gcd(a, b)，那么原方程可以转化成d(ax/d + by/d) = c，容易知道(ax/d + by/d)为整数，如若d不能整除b，方程必然无解，算法结束；否则进入ii)。
      ii) 由i)可以得知，方程有解则一定可以表示成 ax + by = c = gcd(a, b)*c'，那么我们先来看如何求解d = gcd(a, b) = ax + by，根据欧几里德定理，有：
      d = gcd(a, b) = gcd(b, a%b) = bx' + (a%b)y' = bx' + [a-b*(a/b)]y' = ay' + b[x' - (a/b)y'], 于是有x = y',  y = x' - (a/b)y'。
      由于gcd(a, b)是一个递归的计算，所以在求解(x, y)时，(x', y')其实已经利用递归计算出来了，递归出口为b == 0的时候（对比辗转相除，也是b == 0的时候递归结束），那么这时方程的解x0 = 1, y0 = 0。
Author: WhereIsHeroFrom
Update Time: 2018-3-23
Algorithm Complexity: O(log(n))
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

const int MAX_NUMBER = 40010;
const int MAXP = 40010;                // (int)(sqrt(MAX_NUMBER*1.0) + 1);
#define LL long long

bool notprime[MAX_NUMBER];
int primes[MAXP];

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

void factorPrint(vector <factor> factors) {
    int i;
    for(i = 0; i < factors.size(); ++i) {
        factors[i].print();
    }
}

void factorFilter() {
    int i, j;
    notprime[1] = 1;

    for(i = 2; i < MAX_NUMBER; ++i) {
        if(!notprime[i]) {

            if(i < MAXP) {
                primes[ ++primes[0] ] = i;
            }
            for(j = i+i; j < MAX_NUMBER; j += i) {
                notprime[j] = 1;
            }
        }
    }
}

LL GCD(LL a, LL b) {
    return b ? GCD(b, a%b) : a;
}

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

// 因式分解 - 将n分解成素数幂乘积的形式
// 举例：
// 252 = (2^2) * (3^2) * (7^1) 
// 则 ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
    ans.clear();
    if(n == 1) {
        return ;
    }
    // 素数试除 
    int nsq = sqrt(n*1.0) + 1;

    for(int i = 1; i <= primes[0]; i++) {
        if(primes[i] > nsq)
            break;
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

#define INVALID -2
int n, m;
vector< factor > M;
int pCnt[MAXP];
int FactorMIndex[400010];
int Inv[400010];

int getFactorMIndex(int p) {
    int i;
    if(FactorMIndex[p] != INVALID) {
        return FactorMIndex[p];
    }
    for(i = 0; i < M.size(); ++i) {
        if(M[i].prime == p) {
            return FactorMIndex[p] = i;
        }
    }
    return FactorMIndex[p] = -1;
}

LL power(LL a, LL b, LL c) {
    if(!b) {
        return 1 % c;
    }
    LL x = power(a*a % c, b/2, c);
    if(b&1) {
        x = x * a % c;
    }
    return x;
}

LL inv(LL a, LL mod) {
    LL X, Y;
    // a*X % mod = 1
    // a*X + mod*Y = 1;
    ExpGcd(a, mod, X, Y);
    X %= mod;
    if(X < 0) X += mod;
    return X;
}


int main() {
    factorFilter();
    LL ans, sum;
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF && (n||m)) {
        ans = 1;
        sum = 1;
        Factorization(m, M);
        memset(pCnt, 0, sizeof(pCnt));

        for(i = 1; i <= 4*n; ++i) {
            Inv[i] = inv(i, m);
            FactorMIndex[i] = INVALID;
        }

        for(i = 2; i <= n; ++i) {
            vector <factor> U;
            vector <factor> D;
            Factorization(4*i-2, U);
            Factorization(i+1, D);

            for(j = 0; j < U.size(); ++j) {
                int pIdx = getFactorMIndex(U[j].prime);
                if(pIdx == -1) {
                    ans = ans * power(U[j].prime, U[j].count, m) % m;
                }else {
                    pCnt[pIdx] += U[j].count;
                }
            }
            for(j = 0; j < D.size(); ++j) {
                int pIdx = getFactorMIndex(D[j].prime);
                if(pIdx == -1) {
                    ans = ans * power( Inv[D[j].prime], D[j].count, m) % m;
                }else {
                    pCnt[pIdx] -= D[j].count;
                }
            }

            LL now = ans;
            for(j = 0; j < M.size(); ++j) {
                now = now * power(M[j].prime, pCnt[j], m) % m;
            }
            sum = (sum + now) % m;
        }
        printf("%d\n", int(sum % m) );
    }
    return 0;
}

/*
100000 999999999
224872240
*/
