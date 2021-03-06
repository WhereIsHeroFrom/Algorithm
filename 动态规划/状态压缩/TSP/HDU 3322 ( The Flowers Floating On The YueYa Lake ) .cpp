#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct point { 
    double x, y;
}p[ 1010 ];

double w[1010][1010], sum[ 1010 ][ 1010 ];
double D[ 1010 ];        // 由第i个点从左至右再回到i-1的点的最优值

bool cmp( point a, point b ) {
    return a.x < b.x;
}

double Sqr( double x ) {
    return x * x;
}
double Dist( point a, point b ) {
    return sqrt( Sqr(a.x-b.x) + Sqr(a.y-b.y) );
}

int n;
int hash[ 1010 ];

double dfs( int u ) {
    if( u == n )
        return w[u][u-1];
    double Min = -1;

    for( int i = u; i < n;  i++ ) {
        
        if( !hash[i+1] ) {
            D[i+1] = dfs(i+1);
            hash[i+1] = 1;
        }
        double buf = sum[u][i] + D[i+1] + w[i+1][u-1];
        if( Min < 0 || buf < Min )
            Min = buf;
    }
    return Min;
}

int main() {
    int i, j;

    //freopen( "buf.in", "r", stdin );

    while( scanf( "%d", &n ) != EOF && n ) {
        p[0].x = p[0].y = 0;
        p[1].x = p[1].y = 0;

        for( i = 2; i <= n + 1; i ++ ) {
            scanf("%lf %lf", &p[i].x, &p[i].y );
        }
        n ++;
        sort( p, p+n+1, cmp );
        p[0] = p[1];
        for( i = 0; i <= n; i ++ ) {
            w[i][i] = 0;
            for( j =i+1; j <= n; j ++ ) {
                w[i][j] = w[j][i] = Dist( p[i], p[j] );
            }
        }
        for( i = 0; i <= n; i ++ ) {
            sum[i][i] = 0;
            for( j = i+1; j <= n; j ++ ) {
                sum[j][i] = sum[i][j] = sum[i][j-1] + w[j-1][j];
            }
        }

        memset( hash, 0, sizeof( hash ) );
        D[1] = dfs(1);
        printf("%.2lf\n", D[1] );
    }
    return 0;
}
