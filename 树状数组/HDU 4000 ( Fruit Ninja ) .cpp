#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100010
#define LL long long
#define MOD 100000007

LL c[MAXN];
int n;

int lowbit(int x) {
    return x & -x;
}

void reset(LL *c) {
    memset(c, 0, sizeof(c));
}

void add(int x, LL *c) {
    while(x <= n) {
        ++c[x];
        x += lowbit(x);
    }
}

LL sum(int x, LL *c) {
    LL s = 0;
    while(x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}

int a[MAXN];

int main() {
    int t, cases = 0;
    int i;
    scanf("%d", &t);
    while(t--) {
        LL s = 0;
        scanf("%d", &n);
        for(i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        memset(c, 0, sizeof(c));
        for(i = n; i >= 1; --i) {
            int &v = a[i]; 
            LL cnt = (n-i) - sum(v, c);
            s += cnt * (cnt - 1) / 2;
            add(v, c);
        }
        
        memset(c, 0, sizeof(c));
        for(i = 1; i <= n; ++i) {
            int &v = a[i];
            LL cnt = sum(v, c);
            LL ncnt = (n-v)-(i-1-cnt);
            s -= cnt * ncnt;
            add(v, c);
        }
        s %= MOD;
        s = (s + MOD) % MOD;
        
        printf("Case #%d: %lld\n", ++cases, s );
    }
    return 0;
} 
