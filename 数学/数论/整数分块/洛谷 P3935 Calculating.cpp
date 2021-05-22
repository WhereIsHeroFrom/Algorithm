#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;

#define ll long long
const double eps = 1e-8;
const int mod = 998244353;

struct Interval {
    ll val;
    ll l, r;  
    Interval(ll _l, ll _r, ll _val): l(_l), r(_r), val(_val) {}
    ll len() const {
        return r - l + 1;
    }
    void print() {
        printf("[%lld, %lld]\n", l, r);
    }
    ll implGetValue();
};

//  g(x) = n / x     (x in [1, maxx])
// 将 g(x) 的定义域 x 分拆成 最多 2sqrt(n) 个区间，存储在 ret 返回 
ll integerSplit(ll maxx, ll n) {
    double sqrtn = sqrt(n + 0.0);
    ll last = 1;
    ll ret = 0;
    // 1. 计算 x <= sqrt(n) 的部分； 
    for(int x = 1; x <= sqrtn; ++x) {
        if(x > maxx) {
            return ret;
        }
        ret += Interval(x, x, n/x).implGetValue();
        last = x;
    }
    int intsqrtn = (int)(sqrtn + eps);
    // 2. 计算 x > sqrt(n) 的部分 （即 g(x) < sqrt(n) 的情况）； 
    for(int x = intsqrtn; x >= 1; --x) {
        ll now = n / x;
        
        if(last+1 > now) {
            continue;
        }
        
        if(now > maxx) {
            now = maxx;
            ret += Interval(last+1, now, n/now).implGetValue();
            return ret;
        }
        ret += Interval(last+1, now, n/now).implGetValue();
        last = now;
    }
    return ret;
}

ll Interval::implGetValue() {
    return val % mod * (len() % mod) % mod;
}

ll s(ll n) {
    return integerSplit(n, n) % mod;
}

int main() {
    ll l, r;
    while(scanf("%lld %lld", &l, &r) != EOF) {
        ll ans = s(r) - s(l-1);
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
} 
