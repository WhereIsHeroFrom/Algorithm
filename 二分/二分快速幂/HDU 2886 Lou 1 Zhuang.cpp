#include <iostream> 
#include <cstdio>
#include <cstring>
#include <memory.h>

using namespace std;
#pragma warning(disable : 4996)

#define ll long long
ll exp(ll a, ll b, ll c) {
    if (b == 0) {
        return 1 % c;
    }
    ll tmp = exp(a * a % c, b >> 1, c);
    if (b & 1) {
        tmp = tmp * a % c;
    }
    return tmp;
}

/*
    将一个数 N 拆成乘积最大的数 P

    输出 P % 2009

    找规律：
        P 一定是由素因子 2 和 3 组成的，并且满足如下情况：

    N | 2的幂 | 3的幂
    - |   -  |   -
    1 |   0  |  0
    2 |   1  |  0
    3 |   0  |  1
    4 |   2  |  0
    5 |   1  |  1
    6 |   0  |  2
    7 |   2  |  1
    8 |   1  |  2
    9 |   0  |  3
   10 |   2  |  2
   11 |   1  |  3
   12 |   0  |  4
   13 |   2  |  3
   14 |   1  |  4
   15 |   0  |  5

   1 2 3 直接输出 n 即可。
   从 4 开始， 2的幂以  2 1 0 进行循环，所以 2 的幂 = 2 - (N-4)%3;
             3的幂以 012， 123， 234， 345 这样一组一组循环，所以 3 的幂 = (N-4) / 3 + (N-4)%3;
*/
int main() {

    int n;
    while (scanf("%d", &n) != EOF) {
        if (n <= 3) {
            printf("%d\n", n);
        }
        else {
            int p2 = 2 - (n - 4) % 3;
            int p3 = (n - 4) / 3 + (n - 4) % 3;
            int ans = exp(2, p2, 2009) * exp(3, p3, 2009) % 2009;
            printf("%d\n", ans);
        }
    }

    return 0;
}

