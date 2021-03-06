#include <iostream>

using namespace std;

__int64 c[1001][1001];
__int64 f[100];
__int64 n, m;
__int64 dp[1001];

int main() {
    int t;
    int i, j;
    c[1][0] = 1;
    c[1][1] = 1;
    f[0] = 1;

    for(i = 1; i < 100; i++) {
        f[i] = f[i-1] * 2;
    }

    scanf("%d", &t);

    while(t--) {

        scanf("%I64d %I64d", &n, &m);
        for(i = 2; i <= 1000; i++) {
            c[i][0] = c[i][i] = 1;
            for(j = 1; j < i; j++) {
                c[i][j] = (c[i-1][j-1] + c[i-1][j]) % m;
            }
        }
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 1;

        for(i = 3; i <= n; i++) {
            for(j = 1; ; j++) {
                if( f[j] - 1 >= i)
                    break;
            }
            j --;
            __int64 rt = i - ( f[j] - 1 );
            rt = (rt >= f[j-1] ) ? f[j-1] : rt;
            rt += (f[j] - 1) / 2;
            dp[i] = c[i-1][rt] % m * dp[rt] % m * dp[(i-1-rt)] % m;
        }
        printf("%I64d\n", dp[n]);
    }
}
