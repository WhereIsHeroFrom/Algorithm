#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct point {
    double x, y;
    int fix;
}p[ 200 ];

int n;
int state = 0;
bool hash[1<<18];
double dp[1<<18];
bool can[19][19][19];
double T[19][19][19];
double A[3];

double Sqr( double x ) {
    return x * x;
}
double Dist( point a, point b ) {
    return sqrt( Sqr(a.x-b.x) + Sqr(a.y-b.y) );
}


int Sameline( point a, point b, point c ) {
    b.x -= a.x; b.y -= a.y;
    c.x -= a.x; c.y -= a.y;
    if( fabs( c.x * b.y - c.y * b.x ) < 1e-8 )
        return 1;
    return 0;
}

double Do( int now, int p1, int p2 ) {
    if( !can[now][p1][p2] )
        return -1000;
    return T[now][p1][p2];
}

double dfs( int key ) {
    int i, j, k;
    double Min = -10000;

    for( i = 0; i < n; i ++ ) {
        if( key & (1 << i) ) {

            int next = (key ^ (1<<i));
            if( !hash[next] ) {
                hash[next] = true;
                dp[next] = dfs( next );
            }
            if( dp[ next ] < 0 )
                continue;


            for( j = 0; j < n; j ++ ) {
                if( (key & ( 1<<j )) && j != i ) {
                    for( k = j+1; k < n; k ++ ) {
                        if( (key & (1<<k)) && k != i ) {
                            double ans;
                            if( p[i].fix ) 
                                ans = 0;
                            else
                                ans = Do( i, j, k );
                            if( ans < 0 )
                                continue;
                            if( Min < 0 || ans + dp[ next ] < Min )
                                Min = ans + dp[ next ];
                        }
                    }
                }
            }
        }
    }
    return Min;
}
bool Triangle( point a, point b, point c ) {
    return true;

    if( Sameline( a, b, c ) )
        return false;
    //printf("%.1lf %.1lf %.1lf %.1lf %.1lf %.1lf\n", a.x, a.y, b.x, b.y, c.x, c.y );
    A[0] = Dist( a, b );
    A[1] = Dist( b, c );
    A[2] = Dist( c, a );
    sort( A, A + 3 );
    if( A[0] + A[1] <= A[2] )
        return false;
    return true;
}


int main() {
    int i, j, k;
    while( scanf( "%d", &n ) != EOF && n ) {
        state = 0;
        for( i = 0; i < n; i ++ ) {
            scanf("%lf %lf %d", &p[i].x, &p[i].y, &p[i].fix );
            if( p[i].fix )
                state |= ( 1 << i );
        }
        memset( hash, false, sizeof( hash ) );
        memset( can, false, sizeof( can ) );

        for( i = 0; i < n; i ++ ) {
            for( j = 0; j < n; j ++ ) {
                for( k = 0; k < n; k ++ ) {
                    if( i == k || i == j || j == k )
                        continue;
                    can[i][j][k] = Triangle( p[i], p[j], p[k] );
                    if( can[i][j][k] ) {
                        //printf("<%d %d %d %d>\n", i, j, k, can[i][j][k] );
                        T[i][j][k] = Dist( p[i], p[j] ) + Dist( p[i], p[k] );
                    }
                }
            }
        }

        if( state == (1<<n) - 1 ) {
            printf("%.6lf\n", 0 );
            continue;
        }

        int son;
        for( son = state; son; son = ((son-1) & state) ) {
            hash[ son ] = true;
            dp[ son ] = 0;
        }
        dp[0] = 0;
        hash[0] = true;

        for( i = 0; i < (1<<n); i ++ ) {
            if( !hash[i] ) {
                hash[i] = true;
                dp[i] = dfs(i);
            }
        }

        if( dp[ ((1<<n)-1) ] < 0 )
            printf("No Solution\n");
        else
            printf("%.6lf\n", dp[ ((1<<n)-1) ] );
    }
    return 0;
}

/*
18
0 0 1
1 0 1
0 1 0
1 1 0
2 0 0
0 2 0
2 2 0
1 2 0
2 1 0
3 0 0
3 2 0
3 4 0
4 5 0
5 4 0
5 5 0
4 4 0
3 3 0
7 3 0

*/
