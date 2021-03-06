#include <iostream>

using namespace std;

struct point {
    double V;
    double p;
}p[ 210 ];

int cmp( const void *a, const void *b ) {
    point *c = ( point *)a;
    point *d = ( point *)b;
    return 1;
}
int n, m;
int t;
int i, j, k;
double dp[ 210 ][ 200 ];
double V[1000 ];

int main() {
    int t;
    scanf("%d", &t);
 
    int ty = t;
    while( t-- ) {
        scanf("%d %d", &n, &m);
        for(i = 1; i <= n; i++) {
            scanf("%lf %lf", &p[i].V, &p[i].p);
        }

        for(i = 0; i <= n; i++) {
            for(j = 0; j <= m; j++) {
                dp[i][j] = 0;
            }
        }
        double ans = 0;
        dp[0][m] = 1;

        V[0] = 0;
        for(i = 1; i <= n; i++) {
            V[i] = V[i-1] + p[i].V;
        }

        for(i = 1; i <= n; i++) {
            for(j = 0; j <= m; j++) {
                
                dp[i][j] = 0;
                if( j+1 <= m ) {
                    dp[i][j] = dp[i-1][j+1];
                }

                if( dp[i-1][j] * p[i].p > dp[i][j] )
                    dp[i][j] = dp[i-1][j] * p[i].p;

                if( dp[i][j] * V[i] > ans )
                    ans = dp[i][j] * V[i];
            }
        }

        printf("Case %d:\n%.3lf\n", ty - t, ans);
    }
    return 0;
}
