#include <iostream>

using namespace std;

int n, m, K;
double dp[25][40000];
int i, j, k;

int main() {
    while( scanf("%d %d %d", &n, &m, &K) != EOF ) {
        if( !n && !m && !K )
            break;

        dp[0][0] = 1;
        for( i = 1; i <= n; i++) {
            for(j = 0; j <= n*m; j++) {

                dp[i][j] = 0;
                for(k = 1; k <= m; k++) {
                    if( (j - k) >= (i-1) && (j - k) <= (i-1)*m ) {
                        dp[i][j] += dp[i-1][ j-k ] / m;
                    }
                }
            }
        }

        double sum = 0;
        for(i = 0; i <= n*m; i++) {
            if( i <= K + 1) {
                sum += dp[n][i] * 1;
            }else
                sum += dp[n][i] * ( i - K );
        }

        printf("%.11lf\n", sum );
    }
    return 0;
}
