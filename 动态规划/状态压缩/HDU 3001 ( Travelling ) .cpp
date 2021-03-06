#include <iostream>

using namespace std;

#define maxn 12
#define inf -1
#define imp -2
int n, m;
int map[maxn][maxn];
int dp[maxn][ 59049 ];
int f[maxn];

int C( int state, int k ) {
    return (state % f[ k+1 ]) / f[k];
}

int ChangeTo( int state, int k, int to ) {
    return state + ( to - C( state, k ) ) * f[k];
}

int dfs( int now, int state ) {
    int I = C( state, now );
    if( !I ) return imp;


    int pre = ChangeTo( state, now, I-1 );
    int Min = imp;
    int i;
    for( i = 0; i < n; i ++ ) {    
        if( map[i][now] != inf ) {

            if( dp[i][pre] == -1 )
                dp[i][pre] = dfs( i, pre );    
            if( dp[i][pre] != imp ) {
                if( dp[i][pre] + map[i][now] < Min || Min == imp ) {
                    Min = dp[i][pre] + map[i][now];
                }
            }
        }
    }
    return Min;
}

int main() {

    f[0] = 1;
    int i, j;
    for( i = 1; i < maxn; i ++ ) {
        f[i] = f[i-1] * 3;
    }
    int a, b, c;
    while( scanf( "%d %d", &n, &m ) != EOF ) {
        memset( map, inf, sizeof( map ) );
        for( i = 0; i < n; i ++ )
            map[i][i] = 0;
        while( m-- ) {
            scanf("%d %d %d", &a, &b, &c );
            a--; b--;
            if( c < map[a][b] || map[a][b] == inf )
                map[a][b] = map[b][a] = c;
        }
        memset( dp, -1, sizeof( dp ) );
        for( i = 0; i < n; i ++ )
            dp[i][ f[i] ] = 0;

        for( j = 0; j < f[n]; j++ ) {
            for( i = 0; i < n; i ++ ) {
                if( dp[i][j] == -1 )
                    dp[i][j] = dfs( i, j );
            }
        }

        int Min = -1;
        for( j = 0; j < f[n]; j ++ ) {
            for( i = 0; i < n; i ++ ) {
                if( C(j, i) == 0 )
                    break;
            }

            if( i == n ) {
                for( i = 0; i < n; i ++ ) {
                    if( dp[i][j] != imp && (dp[i][j] < Min || Min == -1 ) )
                        Min = dp[i][j];
                }
            }
        }
        printf("%d\n", Min );
    }
    return 0;
}

