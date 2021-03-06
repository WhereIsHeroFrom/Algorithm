#include <iostream>

using namespace std;

int n, m;
int Map[ 110 ][ 7 ];
int dp[ 7 ][ 110 ][ 730 ];
int now;
int f[ 7 ];


// 2表示当前层有放置    1表示上一层有放置   0表示近两层皆无放置
int T( int key, int z ) {
    return (key / f[ m-1-z ]) % 3;
}

int C( int key, int z, int num ) {
    return key + ( num - T( key, z ) ) * f[ m-1-z ];
}

void dfs( int d, int from, int to, int add ) {

    int i;
    int pre, nex;

    if( d == m ) {
        if( add > dp[m][ now ][ to ] )
            dp[m][ now ][ to ] = add;
        return ;
    }

    // 不放置任何图形
    int u = T( from, d );
    if( u == 2 )
        dfs( d+1, from, to*3 + u-1, add );
    else
        dfs( d+1, from, to*3, add );


    //横纵边界限制, 可行放置限制

    // -----
    //   |

    pre = from;
    nex = to;
    if( d >= 2 ) {
        if( T( from, d ) <= 1 && T( from, d-1 ) <= 1 && T( from, d-2) <= 1 ) {
            if( nex % 3 != 2 ) {
                pre = C( pre, d  , 2 );
                pre = C( pre, d-1, 2 );
                pre = C( pre, d-2, 2 );

                if( nex / 3 % 3 != 2 ) {
                    nex = nex + ( 1 - nex / 3 % 3 ) * 3;
                }
                nex = nex + ( 2 - nex % 3 );

                dfs( d+1, pre, nex * 3 + 1, add + 4);
            }
        }
    }

    // |
    // |--
    // |
    pre = from;
    nex = to;
    if( d >= 1 ) {
        if( T( from, d ) <= 1 && T( from, d-1 ) == 0 ) {
            if( nex % 3 != 2 ) {
                pre = C( pre, d  , 2 );
                pre = C( pre, d-1, 2 );

                nex = nex + ( 2 - nex % 3 );
                dfs( d+1, pre, nex * 3 + 1, add + 4);
            }
        }
    }


    //   |
    // -----
    //   |

    pre = from;
    nex = to;
    if( d >= 2 ) {
        if( T( from, d ) <= 1 && T( from, d-1 ) == 0 && T( from, d-2) <= 1 ) {
            if( nex % 3 == 0 ) {
                pre = C( pre, d  , 2 );
                pre = C( pre, d-1, 2 );
                pre = C( pre, d-2, 2 );

                if( nex / 3 % 3 != 2 ) {
                    nex = nex + ( 1 - nex / 3 % 3 ) * 3;
                }
                nex = nex + ( 2 - nex % 3 );

                dfs( d+1, pre, nex * 3 + 1, add + 5);
            }
        }
    }

    // -----
    // |


    pre = from;
    nex = to;
    if( d >= 2 ) {
        if( T( from, d ) <= 1 && T( from, d-1 ) <= 1 && T( from, d-2) <= 1 ) {
            if( nex / 3 % 3 != 2 ) {
                pre = C( pre, d  , 2 );
                pre = C( pre, d-1, 2 );
                pre = C( pre, d-2, 2 );

                nex = nex + ( 2 - nex / 3 % 3 ) * 3;
                nex = nex + ( 1 - nex % 3 );

                dfs( d+1, pre, nex * 3 + 1, add + 4);
            }
        }
    }


    // ---
    // |
    // |
    pre = from;
    nex = to;
    if( d >= 1 ) {
        if( T( from, d ) == 0 && T( from, d-1 ) == 0 ) {
            if( nex % 3 != 2 ) {
                pre = C( pre, d  , 1 );
                pre = C( pre, d-1, 2 );

                nex = nex + ( 2 - nex % 3 );
                dfs( d+1, pre, nex * 3 + 0, add + 4);
            }
        }
    }
}

int main() {

    int i, j, ty;

    f[0] = 1;
    for(i = 1; i < 7; i++)
        f[i] = f[i-1] * 3;

    memset( Map, -1, sizeof( Map ));
    memset( dp, -1, sizeof( dp ));

    for( ty = 1; ty <= 6; ty++) {

        n = 100;
        m = ty;
        dp[ty][0][ f[m] - 1 ] = 0;

        for(i = 1; i <= n; i++) {
            for(j = 0; j < f[m]; j++) {

                if( dp[ty][i-1][j] >= 0 ) { 
                    now = i;
                    dfs( 0, j, 0, dp[ty][i-1][j]);
                }
            }
        }
    }

    while( scanf("%d %d", &n, &m) != EOF ) {
        
        if( Map[n][m] != -1 ) {
            printf("%d\n", Map[n][m]);
            continue;
        }
    
        Map[n][m] = 0;
        for(i = 0; i < f[m]; i++) {
            if( dp[m][n][i] > Map[n][m] )
                Map[n][m] = dp[m][n][i];
        }
    
        printf( "%d\n", Map[n][m] );
    }
}
