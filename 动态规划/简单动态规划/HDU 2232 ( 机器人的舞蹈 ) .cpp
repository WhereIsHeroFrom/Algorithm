#include <iostream>

using namespace std;

int dp[101][4][4][4][4];
int sum[ 101 ];

int main() {
    dp[0][0][1][2][3] = 1;
    sum[0] = 1;


    int n, i, j, k, l, ii, jj, kk, ll;
    for( n = 1; n <= 100; n++ ) {
        for(i = 0; i < 4; i++) {
            for(j = 0; j < 4; j++) {
                for(k = 0; k < 4; k++) {
                    for(l = 0; l < 4; l++) {
                        for(ii = -1; ii <= 1; ii ++) {
                            for(jj = -1; jj <= 1; jj ++) {
                                for(kk = -1; kk <= 1; kk++) {
                                    for(ll = -1; ll <= 1; ll++) {
                                        int a = (i + ii + 4) % 4;
                                        int b = (j + jj + 4) % 4;
                                        int c = (k + kk + 4) % 4;
                                        int d = (l + ll + 4) % 4;
                                        dp[n][i][j][k][l] += dp[n-1][a][b][c][d];
                                        dp[n][i][j][k][l] %= 9937;
                                        if(i != j && i != k && i != l && j != k && j != l && k != l) {
                                            //printf("%d %d %d %d %d\n", i, j ,k , l, dp[n-1][a][b][c][d] );
                                            sum[n] = (sum[n] + dp[n-1][a][b][c][d]) % 9937;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /*for(i = 1; i <= 100; i++) {
        printf("%d\n", sum[i]);
    }*/

    while( scanf("%d", &n) != EOF ){
        printf("%d\n", sum[n]);
    }
}
