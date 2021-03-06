#include <iostream>

using namespace std;

#define INF 1000000000

int dp[1010][60];

int Min(int a, int b) {
    return a < b ? a : b;
}
int Max(int a, int b) {
    return a > b ? a : b;
} 

int main() {
    int i, j, k;

    for(i = 0; i <= 1000; i++) {
        for(j = 1; j <= 50; j++) {
            if(i == 0) {
                dp[i][j] = 0;
                continue;
            }else if(j == 1) {
                dp[i][j] = i;
                continue;
            }
            dp[i][j] = INF;
            for(k = 1; k <= i; k++) {
                dp[i][j] = Min(dp[i][j], Max(dp[i-k][j], dp[k-1][j-1]) + 1 );
            }
        }
    }    
    int t;
    scanf("%d", &t);
    while(t--) {
        int c, n, k;
        scanf("%d %d %d", &c, &k, &n);
        printf("%d %d\n", c, dp[n][k]);
    }
    return 0;
}

