#include <iostream>

using namespace std;

#define MAXN 510
int n, m;
int mat[2][MAXN][MAXN];
int dp[MAXN][MAXN];
int R[MAXN][MAXN], C[MAXN][MAXN];

int Max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    int i, j, k;
    while(scanf("%d %d", &n, &m) != EOF) {
        if(!n && !m) {
            break;
        }
        for(k = 0; k < 2; ++k) {
            for(i = 1; i <= n; ++i) {
                for(j = 1; j <= m; ++j) {
                    scanf("%d", &mat[k][i][j]);
                }
            }
        }
        for(i = 1; i <= n; ++i) {
            for(j = 1; j <= m; ++j) {
                R[i][j] = R[i][j-1] + mat[0][i][j];
            }
        }
        for(i = 1; i <= m; ++i) {
            for(j = 1; j <= n; ++j) {
                C[j][i] = C[j-1][i] + mat[1][j][i];
            }
        }

        int maxAns = 0;
        for(i = 1; i <= n; ++i) {
            for(j = 1; j <= m; ++j) {
                dp[i][j] = Max(R[i][j] + dp[i-1][j], C[i][j] + dp[i][j-1]);
                //printf("%d ", dp[i][j]);
                maxAns = Max(maxAns, dp[i][j]);
            }
            //puts("");
        }
        printf("%d\n", maxAns);
    }
    return 0;
}
