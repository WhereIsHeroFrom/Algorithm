#include <iostream>
#include <cmath>
using namespace std;

#define LL __int64

char N[1010];
int n;
int m;
LL f[1000010];

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%s %d", N, &m);
        n = 0;
        int bas = 1;
        for(i = 0; N[i]; ++i) {
            n = n * 10 + (N[i]-'0');
            if(n >= m) {
                break;
            }
        }
        f[0] = 1;
        LL ans = f[0];
        for(i = 1; i <= n; ++i) {
            f[i] = i*f[i-1];
            if(f[i] >= m) f[i] %= m;
            if(f[i] == 0) break;
            ans += f[i];
            if(ans >= m) ans %= m;
        }
        printf("%I64d\n", ans % m);
    }
    return 0;
}
