#include <iostream>

using namespace std;

struct point {
    __int8 w, x, y, z;
}p[32][32][32][32], temp;

int A[32][32];
int B[32][32];
double M[32][32];

double dp[32][32][32][32];
int i, j, k, l;
inline double Max(double a, double b) {
    return a > b ? a : b;
}

double low, high, mid;
int up, down;
int n, m;

int gcd(int a, int b) {
    int m = 1;
    if(a == 0)
        return b;
    if(b == 0)
        return a;
    while(m) {
        m = a % b;
        a = b;
        b = m;
    }
    return a;
}
int main() {
    while(scanf("%d %d", &n, &m) != EOF) {
        
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                scanf("%d", &A[i][j]);
            }
        }

        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                scanf("%d", &B[i][j]);
            }
        }        
        for(i = 0; i <= n + 1; i++) {
            for(j = 0; j <= m + 1; j ++) {
                for(k = 0; k <= n + 1; k++) {
                    for(l = 0; l <= m + 1; l ++) {
                        dp[i][j][k][l] = -10000000000000.0;
                    }
                }
            }
        }

        up = down = 0;

        p[1][2][2][1].w = 1;
        p[1][2][2][1].x = 1;
        p[1][2][2][1].y = 1;
        p[1][2][2][1].z = 1;

        p[2][1][1][2].w = 1;
        p[2][1][1][2].x = 1;
        p[2][1][1][2].y = 1;
        p[2][1][1][2].z = 1;

        low = 0;
        high = 10000000000.0;

        while(low < high) {

            mid = (low + high) / 2;

            for(i = 1; i <= n; i++) {
                for(j = 1; j <= m; j++) {
                    M[i][j] = A[i][j] - B[i][j] * mid;
                }
            }

            dp[1][2][2][1] = M[1][2] + M[2][1];
            dp[2][1][1][2] = M[2][1] + M[1][2];

            for(i = 1; i <= n; i++) {
                for(j = 1; j <= m; j++) {
                    for(k = 1; k <= n; k++) {
                        for(l = 1; l <= m; l++) {
                        
                            if(i == 1 && j == 1 && k == 1 && l == 1)
                                continue;

                            if(i + j != k + l)
                                continue;

                            if(i == k && j == l)
                                continue;

                            if(i == 1 && j == 2 && k == 2 && l == 1)
                                continue;

                            if(i == 2 && j == 1 && k == 1 && l == 2)
                                continue;    

                            if( !(i-1 == k-1 && j == l) ) {
                                dp[i][j][k][l] = dp[i-1][j][k-1][l] + M[i][j] + M[k][l];

                                p[i][j][k][l].w = i - 1;
                                p[i][j][k][l].x = j;
                                p[i][j][k][l].y = k-1;
                                p[i][j][k][l].z = l;
                            }

                            if( !(i-1 == k && j == l-1) ) {
                                if( dp[i-1][j][k][l-1] + M[i][j] + M[k][l] > dp[i][j][k][l] ) {

                                    dp[i][j][k][l] = dp[i-1][j][k][l-1] + M[i][j] + M[k][l];

                                    p[i][j][k][l].w = i - 1;
                                    p[i][j][k][l].x = j;
                                    p[i][j][k][l].y = k;
                                    p[i][j][k][l].z = l-1;
                                }
                            }
                            if( !(i == k-1 && j-1 == l) ) {

                                if( dp[i][j-1][k-1][l] + M[i][j] + M[k][l] > dp[i][j][k][l] ) {
                                    dp[i][j][k][l] = dp[i][j-1][k-1][l] + M[i][j] + M[k][l];

                                    p[i][j][k][l].w = i;
                                    p[i][j][k][l].x = j - 1;
                                    p[i][j][k][l].y = k - 1;
                                    p[i][j][k][l].z = l;
                                }
                            }


                            if( !(i == k && j == l) ) {
                                if( dp[i][j-1][k][l-1] + M[i][j] + M[k][l] > dp[i][j][k][l] ) {

                                    dp[i][j][k][l] = dp[i][j-1][k][l-1] + M[i][j] + M[k][l];

                                    p[i][j][k][l].w = i;
                                    p[i][j][k][l].x = j-1;
                                    p[i][j][k][l].y = k;
                                    p[i][j][k][l].z = l-1;
                                }
                            }
                        }
                    }
                }
            }

            if( Max( dp[n][m-1][n-1][m], dp[n-1][m][n][m-1]) > 0 ) {
                low = mid + 1e-7;
            }else
                high = mid - 1e-7;
        }
        if(dp[n][m-1][n-1][m] > dp[n-1][m][n][m-1] ) {
            temp = p[n][m-1][n-1][m];
            up = A[n][m-1] + A[n-1][m];    
            down = B[n][m-1] + B[n-1][m];
        }else {
            temp = p[n-1][m][n][m-1];
            up = A[n][m-1] + A[n-1][m];
            down = B[n][m-1] + B[n-1][m];
        }

        while(! (temp.w == 1 && temp.x == 1 && temp.y == 1 && temp.z == 1) ) {
            up += A[ temp.w ][ temp.x ];
            up += A[ temp.y ][ temp.z ];
            down += B[ temp.w ][ temp.x ];
            down += B[ temp.y ][ temp.z ];
            temp = p[ temp.w ][ temp.x ][ temp.y ][ temp.z ];
        }

        int G = gcd(up, down);
        printf("%d/%d\n", up / G, down / G);
    }
    return 0;
}
