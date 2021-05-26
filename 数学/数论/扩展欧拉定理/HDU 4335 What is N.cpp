#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory.h>
#include <cmath>
using namespace std;

#pragma warning(disable : 4996)

#define ll unsigned long long
#define MAXP 65540

int primes[MAXP];
bool notprime[MAXP];

// 厄尔多塞素数筛选法 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for (int i = 2; i < MAXP; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
            for (ll j = (ll)i * i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

// 欧拉函数 - 获取小于n的数中与n互素的数的个数 
// 举例：
// Phi(10) = 4
// 即 1、3、7、9  总共4个 
int Phi(int n) {
    if (n == 1) {
        return 1;
    }
    int ans = 1;
    // 素数试除 
    for (int i = 1; i <= primes[0]; i++) {
        int p = primes[i];
        if (n % p == 0) {
            n /= p;
            ans *= (p - 1);
            while (!(n % p)) {
                n /= p;
                ans *= p;
            }
        }
        if (n == 1) {
            return ans;
        }
    }
    return ans * (n - 1);
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
ll XJ[maxn];
ll XJMod[maxn];
ll g[maxn], xp[maxn];

int main() {
    Eratosthenes();
    int t, b, P;
    ll M;
    int cas = 0;

    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %llu", &b, &P, &M);

        if (b == 0 && P == 1 && M == 18446744073709551615ll) {
            printf("Case #%d: 18446744073709551616\n", ++cas);
            continue;
        }

        // 1. 计算 P 的欧拉函数
        int eula = Phi(P);
        // 2. 初始化 x 阶乘 Mod P的欧拉函数
        XJMod[0] = 1 % eula;
        XJ[0] = 1;
        for (int i = 1; i <= 100000; ++i) {
            XJMod[i] = XJMod[i - 1] * i % eula;
            XJ[i] = XJ[i - 1] * i;
        }
        // 3. 枚举所有 x 属于 [1, M]，判定可行性
        ll cnt = 0;
        int flag = -1;
        for (ll x = 0; x <= M; ++x) {
            if (x < 10) {
                ll ans = Exp(x, XJ[x], P);
                if (ans == b) {
                    ++cnt;
                }
            }
            else {
                if (XJMod[x] == 0) {
                    flag = x;
                    break;
                }
                ll ans = Exp(x, XJMod[x] + eula, P);
                if (ans == b) {
                    ++cnt;
                }
            }
        }
        if (flag != -1) {
            // 4. 计算 [x, M] 这部分 
            // 目前的值等于 x ^ phi(P) mod P
            // 假设 g(x) 代表 [0, x] 中满足 x ^ phi(P) mod P = b 的 x 的个数 
            // 利用差分可以得到 g(M) - g(x-1) 就是我们要求的解。
            // 那么 i = [0，P-1] 的情况，利用二分快速幂枚举暴力计算
            // 存储的 g[i] 中，代表 [0, i] 中满足条件的个数；
            // 然后利用循环节计算后面大的部分 
            ll x = flag;
            for (int i = 0; i < P; ++i) {
                xp[i] = (Exp(i, eula, P) == b ? 1 : 0);
                if (i) {
                    xp[i] += xp[i - 1];
                }
            }
            ll r = (M / P) * xp[P - 1] + xp[M % P];
            ll l = ((x - 1) / P) * xp[P - 1] + xp[(x - 1) % P];
            cnt += r - l;
            //printf("???? %llu\n", r - l);
        }
        /*
        ll gg = 0;
        for (ll x = 0; x <= M; ++x) {
            ll ans = Exp(x, XJ[x], P);
            if (ans == b) {
                ++gg;
            }
        }
        printf("%llu\n", gg);*/
        printf("Case #%d: %llu\n", ++cas, cnt);
    }
    return 0;
}