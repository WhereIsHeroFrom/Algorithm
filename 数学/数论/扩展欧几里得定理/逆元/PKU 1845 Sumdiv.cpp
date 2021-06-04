/*
线性同余
求解同余方程第一步是转化成一般式：ax + by = c，这个方程的求解步骤如下：
      i) 首先求出a和b的最大公约数d = gcd(a, b)，那么原方程可以转化成d(ax/d + by/d) = c，容易知道(ax/d + by/d)为整数，如若d不能整除b，方程必然无解，算法结束；否则进入ii)。
      ii) 由i)可以得知，方程有解则一定可以表示成 ax + by = c = gcd(a, b)*c'，那么我们先来看如何求解d = gcd(a, b) = ax + by，根据欧几里德定理，有：
      d = gcd(a, b) = gcd(b, a%b) = bx' + (a%b)y' = bx' + [a-b*(a/b)]y' = ay' + b[x' - (a/b)y'], 于是有x = y',  y = x' - (a/b)y'。
      由于gcd(a, b)是一个递归的计算，所以在求解(x, y)时，(x', y')其实已经利用递归计算出来了，递归出口为b == 0的时候（对比辗转相除，也是b == 0的时候递归结束），那么这时方程的解x0 = 1, y0 = 0。
*/

/*
逆元
已知 a 和 b，对于同余式：   ax % b = 1  求 x
1) 如果 a 和 b 不互素，则逆元不存在；
2）可以转化成   ax + bn = 1 ，求解一个可行解 x；
3）x = (x % n + n) % n 转换成最小的正整数；
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

#define ll long long
#pragma warning(disable : 4996)

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

// 扩展欧几里得
// aX + bY = 1 
ll ExpGcd(ll a, ll b, ll& X, ll& Y) {
    ll q, temp;
    if (!b) {
        q = a; X = 1; Y = 0;
        return q;
    }
    else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X;
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
    }
}

// a * x % b = 1
// 求 x 
ll Inv(ll a, ll b) {
    ll X, Y;
    ExpGcd(a, b, X, Y);
    X = (X % b + b) % b;
    return X;
}

ll Exp(ll a, ll n, ll Mod) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans = ans * a % Mod;
        a = a * a % Mod;
        n >>= 1;
    }
    return ans;
}

const int maxn = 100005;

int primes[maxn];
bool notprime[maxn];

struct factor {
    int prime, count;
    factor() :prime(0), count(0) {}
    factor(int p, int c) : prime(p), count(c) {}
    void print() {
        printf("(%d, %d)\n", prime, count);
    }
};
// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for (int i = 2; i < maxn; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for (ll j = (ll)i * i; j < maxn; j += i) {
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
    if (n == 1) {
        return;
    }
    // 素数试除 
    for (int i = 1; i <= primes[0]; i++) {
        if (n % primes[i] == 0) {
            factor f(primes[i], 0);
            while (!(n % primes[i])) {
                n /= primes[i];
                f.count++;
            }
            ans.push_back(f);
        }
        if (n == 1) {
            return;
        }
    }
    // 漏网之素数， 即大于MAXP的素数，最多1个 
    ans.push_back(factor(n, 1));
}
const int mod = 9901;

int main() {
    Eratosthenes();
    int a, b;
    while ( scanf("%d %d", &a, &b) != EOF ) {
        if(!a) {
            if(b == 0) printf("1\n");
            else printf("0\n");
            continue;
        }

        vector <factor> v;
        Factorization(a, v);
        ll ans = 1;
        for(int i = 0; i < v.size(); ++i) {
            if( (v[i].prime - 1) % mod == 0 ) {
                ans *= ((ll)v[i].count * b + 1) % mod;
                ans %= mod;
                continue;
            }
            ans *= ( Exp(v[i].prime, (ll)v[i].count * b + 1, mod) - 1);
            ans %= mod;
            ans *= Inv(v[i].prime - 1, mod);
            ans %= mod;
        }
        ans = (ans % mod + mod) % mod;
        printf("%d\n", (int)ans);
    }
    return 0;
}
