#include <iostream>

using namespace std;

int n, m;
int dp[ 100 ][ 100 ];
int S;
char map[ 100 ][ 100 ];

int dfs( int x, int y ){
    bool hash[ 1000 ];
    int i, j;
    memset( hash, 0, sizeof( hash ));

    if( x == 1 && y == 1 )
        return 0;
    if( x > 1 && y > 1 ) {
        for(i = 1; i < x; i++) {
            for( j = 1; j < y; j++) {

                if( dp[x][j] == -1 )
                    dp[x][j] = dfs( x, j );

                if( dp[i][y] == -1 )
                    dp[i][y] = dfs( i, y );

                hash[ dp[i][y] ^ dp[x][j] ] = 1;
            }
        }
    }else if( x == 1 && y > 1 ) {
        for(i = 1; i < y; i++) {
            if( dp[x][i] == -1 )
                dp[x][i] = dfs( x, i );
            hash[ dp[x][i] ] = 1;
        }

    }else if( x > 1 && y == 1 ) {
        for(i = 1; i < x; i++) {
            if( dp[i][y] == -1 )
                dp[i][y] = dfs( i, y );
            hash[ dp[i][y] ] = 1;
        }
    }

    for(i = 0; ; i++) {
        if( !hash[i] )
            return i;
    }
}

int main() {
    int i, j;

    memset( dp, -1, sizeof( dp ));

    while( scanf("%d %d", &n, &m) != EOF && (n || m ) ) {
        for(i = 1; i <= n; i++) {
            scanf("%s", &map[i][1] );
        }
        S = 0;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                if( i == 1 && j == 1 )
                    continue;
                if( map[i][j] == '#' ) {
                    if( dp[i][j] == -1 )
                        dp[i][j] = dfs( i, j );
                    S ^= dp[i][j];
                }
            }
        }

        if( S )
            printf("John\n");
        else
            printf("Jack\n");
    }
    return 0;
}
