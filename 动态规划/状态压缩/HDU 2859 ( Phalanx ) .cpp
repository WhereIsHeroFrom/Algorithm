#include <iostream>

using namespace std;

char map[1001][1001];
short dp[1001][1001];
int n;

int main() {
    int i, j, k;
    int Min, S;
    while( scanf("%d", &n) != EOF && n ) {

        for(i = 1; i <= n; i++) {
            scanf( "%s", &map[i][1] );
        }
        if( n == 1 ) {
            puts("1");
            continue;
        }
        Min = 0;
        for(i = n-1; i >= 1; i--) {
            for(j = 2; j <= n; j++) {
                dp[i][j] = 0;
                if( map[i][j-1] == map[i+1][j] ) {
                    S = dp[i][j-1] < dp[i+1][j] ? dp[i][j-1] : dp[i+1][j] + 1;
                    for( k = S; ; k++) {
                        if( k > dp[i+1][j-1] + 1 || map[i][j-k] != map[i+k][j] ) {
                            dp[i][j] = k - 1; break;
                        }
                    }
                    if( dp[i][j] > Min )
                        Min = dp[i][j];
                }
            }
        }
        printf("%d\n", Min + 1 );
    }
    return 0;
}
