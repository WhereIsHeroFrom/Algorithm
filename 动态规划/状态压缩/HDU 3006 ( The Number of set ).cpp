#include <iostream>

using namespace std;

int n, m;
int i, j;

int dp[ 1<<14 ];
int main() {
    while( scanf( "%d", &n ) != EOF ) {
        memset( dp, 0, sizeof( dp ) );
        scanf("%d", &m );
        dp[0] = 1;
        for( i = 0; i < n; i ++ ) {
            int k;
            scanf("%d", &k );
            int x = 0, y;
            while( k-- ) {
                scanf("%d", &y );
                x |= (1 << (y-1));
            }
            for( j = (1<<m)-1; j >= 0; j-- ) {
                dp[ j | x ] = dp[ j | x ] | dp[j];
            }
        }

        int C = 0;
        for( i = 1; i < (1<<m); i++ ) {
            if( dp[i] )
                C++;
        }
        printf("%d\n", C );
    }
    return 0;
}

