#include <iostream>

using namespace std;

#define LL long long
#define MOD 1000000007
#define MAXN 100010

LL power(LL a, LL b) {
    if(b == 0) {
        return 1;
    }
    int x = power(a*a%MOD, b/2);
    if(b&1) x = x * a % MOD;
    return x;
}

int a[MAXN];

int main() {
    int T;
    int n, t, k;
    int i;
    scanf("%d", &T);
    while( T-- ) {
        scanf("%d %d %d", &n, &t, &k);
        LL p = power(k, t);
        for(i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        for(i = 0; i < n; ++i) {
            
            int idx = (i - t) % n;
            if(idx < 0) idx += n;
            LL v = p * a[idx] % MOD;
            if(i) printf(" ");
            printf("%lld", v);
        }
        puts("");
    }
    return 0;
}
