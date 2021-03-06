#include <iostream>

using namespace std;

int S, n, m;
char map[ 20 ][ 20 ];
int dp[ 20 ][ 20 ];

bool Is( int i, int j, int ui, int uj ) {
    if( i == ui ) {
        if( uj <= j && j  <= uj + S-1 )
            return true;
    }else if( i == ui + S-1 ) {
        if( uj <= j && j  <= uj + S-1 )
            return true;
    }else if( j == uj ) {
        if( ui <= i && i  <= ui + S-1 )
            return true;
    }else if( j == uj + S-1 ) {
        if( ui <= i && i  <= ui + S-1 )
            return true;
    }
    return false;
}

int main() {
    int t;
    int i, j;
    int Max;

    scanf("%d", &t );
    while( t-- ) {
        scanf("%d %d %d", &S, &n, &m );
        for( i = 1; i <= n; i ++ ) {
            scanf( "%s", &map[i][1] );
            for( j = 1; j <= m; j ++ ) {
                if( map[i][j] == 'x' )
                    dp[i][j] = 1;
                else
                    dp[i][j] = 0;
            }
        }

        for( i = 1; i <= n; i ++ ) {
            for( j = 1; j <= m; j ++ )
                dp[i][j] += dp[i][j-1];
        }

        for( i = 1; i <= n; i ++ ) {
            for( j = 1; j <= m; j ++ )
                dp[i][j] += dp[i-1][j];
        }

        /*for( i = 1; i <= n; i ++ ) {
            for( j = 1; j <= m; j ++ ) {
                printf("%d ", dp[i][j] );
            }
            puts("");
        }*/

        Max = -1;
        int ui, uj;

        for( i = 1; i <= n; i ++ ) {
            for( j = 1; j <= m; j ++ ) {
                if( i + S - 1 > n || j + S - 1 > m ) continue;

                int u = dp[i+S-1][j+S-1] + dp[i-1][j-1] - 
                    dp[i+S-1][j-1] - dp[i-1][j+S-1];
                if( u > Max ) {
                    Max = u;
                    ui = i;
                    uj = j;
                }
            }
        }

        printf("Trapped %d enemy(ies).\n", Max );
        for( i = 1; i <= n; i ++ ) {
            for( j = 1; j <= m; j ++ ) {
                if( Is( i, j, ui, uj ) ) {
                    if( map[i][j] == '.' )
                        printf("T");
                    else
                        printf("I");
                }else
                    printf("%c", map[i][j] );
            }
            puts("");
        }
        puts("");
    }
    return 0;
}

