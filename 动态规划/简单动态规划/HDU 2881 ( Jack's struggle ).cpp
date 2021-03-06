#include <iostream>
#include <cmath>

using namespace std;

int n, m;

struct point {
    int t;
    int x;
    int y;
    int sum;
}p[ 100000 ];

int cmp( const void *a, const void *b ) {
    point *c = ( point *)a;
    point *d = ( point *)b;
    if( c->t == d->t )
        return c->sum - d->sum;
    return c->t - d->t;
}



int dp[ 100000 ];
int main() {
    int i, j;

    while( scanf("%d %d", &n, &m) != EOF && (n||m) ) {
        for(i = 0; i < m; i++)
            dp[i] = -1;

        for( i = 0; i < m; i++) {
            scanf("%d %d %d", &p[i].t, &p[i].x, &p[i].y );
            p[i].sum = p[i].x + p[i].y;
        }

        qsort( p, m, sizeof( point ), cmp );

        int Max = 1;
        dp[0] = 1;

        for(i = 1; i < m; i++) {
            dp[i] = 1;
            int coun = 0;
            for(j = i - 1; j >= 0 ; j-- ) {
                if( abs(p[i].x-p[j].x) + abs(p[i].y-p[j].y) <= p[i].t - p[j].t ) {
                    if( dp[j] + 1 > dp[i] )
                        dp[i] = dp[j] + 1;
                }
                if( coun ++ > 100 )
                    break;
            }

            if( dp[i] > Max )
                Max = dp[i];
        }

        printf("%d\n", Max);
    }
}
