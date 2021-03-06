#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 110

LL dp[MAXN][MAXN][2];

int main() {
    int t;
    int c, n, k;
    int i;
    
    dp[0][0][0] = 1;
    
    for(n = 1; n <= 100; n++) {
        for(k = 0; k <= n; k++) {
            dp[n][k][0] = dp[n-1][k][0] + dp[n-1][k][1];
            dp[n][k][1] = dp[n-1][k][0] + (k==0?0:dp[n-1][k-1][1]);
        }
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &c, &n, &k);
        printf("%d %I64d\n", c, dp[n][k][0] + dp[n][k][1]);
    }
    return 0;
}

