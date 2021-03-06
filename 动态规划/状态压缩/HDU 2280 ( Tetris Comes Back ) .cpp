#include <iostream>

using namespace std;

int m = 5;
int f[ 10 ];
int n, c;
char map[ 1010 ][ 10 ];
int dp[ 1010 ][ 243 ];
int now;


int T( int key, int z ) {
    return key / f[ m-1-z ] % 3;
}

int C( int key, int z, int num ){
    return key + ( num - T( key, z ) ) * f[ m-1-z ];
}

void dfs( int depth, int from, int to, int add) {
    if( depth == m ) {
        if( add < dp[ now ][ to ] )
            dp[ now ][ to ] = add;
        return ;
    }
    int pre, nex;

    // 不放置

    if( map[ now ][ depth ] == '1' ) {

        if( T( from, depth ) == 1 ) {
            dfs( depth+1, from, to * 3 + 2, add+1 );
        }else if( T( from, depth ) == 2 )
            dfs( depth+1, from, to * 3 + 2, add );
    }else {
        if( T( from, depth ) == 2 )
            dfs( depth+1, from, to * 3 + T( from, depth ) - 1, add );
        else
            dfs( depth+1, from, to * 3, add );

        // 1*1
        if( T( from, depth ) == 2 )
            dfs( depth+1, from, to*3+2, add+1 );
    }

    // 1*2
    if( depth >= 1 ) {
        pre = from;
        nex = to;

        if( map[ now ][ depth ] == '0' && map[ now ][ depth-1 ] == '0' ) {
            if(  T( from, depth ) == 2 && T( from, depth-1 ) == 2 ) {
                if( nex % 3 != 2 ) {
                    nex = nex + ( 2 - nex % 3 );
                    dfs( depth+1, from, nex * 3 + 2, add );
                }
            }
        }
    }

    if( depth >= 0 ) {
        pre = from;
        nex = to;

        if( map[ now ][ depth ] == '0' && map[ now-1][ depth ] == '0' ) {
            if( T( from, depth ) == 1 ) {
                pre = C( pre, depth, 2 );
                dfs( depth+1, from, nex * 3 + 2, add );
            }
        }
    }

    // -----
    // |
    // |
    if( depth >= 1 ) {
        pre = from;
        nex = to;

        if( map[ now-1 ][ depth ] == '0' && map[ now-1 ][ depth-1 ] == '0' && map[ now ][ depth-1 ] == '0' ) {
            if( T( from, depth ) == 1 && T( from, depth-1 ) == 1 ) {
                pre = C( pre, depth, 2 );
                pre = C( pre, depth-1, 2 );

                if( nex % 3 != 2 ) {
                    nex = nex + ( 2 - nex % 3);
                    if( map[ now ][ depth ] == '1' ) 
                        dfs( depth+1, pre, nex * 3 + 2, add );
                    else
                        dfs( depth+1, pre, nex * 3 + 1, add );
                }
            }
        }
    }

    // -----
    //     |
    //     |

    if( depth >= 1 ) {

        pre = from;
        nex = to;

        if( map[ now-1 ][ depth ] == '0' && map[ now-1 ][ depth-1 ] == '0' && map[ now ][ depth ] == '0' ) {
            if( T( from, depth ) == 1 && T( from, depth-1 ) == 1 ) {
                pre = C( pre, depth, 2 );
                pre = C( pre, depth-1, 2 );

                if( nex % 3 != 2 ) {
                    nex = nex + ( 1 - nex % 3 );
                    dfs( depth+1, pre, nex * 3 + 2, add );
                }
            }
        }
    }

    // |
    // |
    // -----
    if( depth >= 1 ) {

        pre = from;
        nex = to;

        if( map[ now ][ depth ] == '0' && map[ now ][ depth-1 ] == '0' && map[ now-1 ][ depth-1 ] == '0' ) {
            if( T( from, depth-1 ) == 1 ) {

                if( T( from, depth ) == 2 ) {
                    pre = C( pre, depth-1, 2 );

                    if( nex % 3 != 2 ) {
                        nex = nex + ( 2 - nex % 3 );
                        dfs( depth+1, pre, nex * 3 + 2, add );
                    }
                }else if( T( from, depth ) == 1 ){
                    pre = C( pre, depth-1, 2 );

                    if( nex % 3 != 2 ) {
                        nex = nex + ( 2 - nex % 3 );
                        dfs( depth+1, pre, nex * 3 + 2, add+1 );
                    }
                }

            }
        }
    }

    //     |
    //     |
    // -----

    if( depth >= 1 ) {
        pre = from;
        nex = to;

        if( map[ now ][ depth-1 ] == '0' && map[ now ][ depth ] == '0' && map[ now-1 ][ depth ] == '0' ) {
            pre = from;
            nex = to;

            if( T( from, depth ) == 1 ) {
                if( T( from, depth-1 ) == 2 ) {

                    pre = C( pre, depth, 2 );

                    if( nex % 3 != 2 ) {
                        nex = nex + ( 2 - nex % 3 );
                        dfs( depth+1, pre, nex * 3 + 2, add );
                    }
                }else if ( T( from, depth-1 ) == 1 ){
                    pre = C( pre, depth, 2 );

                    if( nex % 3 != 2 ) {
                        nex = nex + ( 2 - nex % 3 );
                        dfs( depth+1, pre, nex * 3 + 2, add+1 );
                    }
                }
            }
        }
    }

}

int main() {
    int i, j
        ;
    f[0] = 1;
    for(i = 1; i < 10; i++)
        f[i] = f[i-1] * 3;

    while( scanf("%d %d", &n, &c) != EOF ) {
        for(i = 1; i <= n; i++) {
            scanf("%s", map[i]);
        }

        for(i = 0; i <= n; i++) {
            for(j = 0; j < 243; j++) {
                dp[i][j] = 10000000;
            }
        }
        dp[0][ f[m] - 1 ] = 0;

        for(i = 1; i <= n; i++) {
            for(j = 0; j < f[m]; j++) {
                if( dp[i-1][j] != 10000000 ) {
                    now = i;
                    dfs( 0, j, 0, dp[i-1][j] );
                }
            }
        }

        if( dp[ n ][ f[m] - 1 ] <= c )
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
