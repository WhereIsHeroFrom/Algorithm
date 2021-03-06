#include <iostream>

using namespace std;
#define ll __int64
#define mod 20090818

ll c[ 1010 ][ 1010 ];
ll f[ 1010 ];

int main() {
    int i, j;
    int n, m;
    f[0] = 1;
    f[1] = 0;
    f[2] = 1;
    for( i = 3; i <= 1000; i++ ) {
        f[i] = (i - 1) * (f[i-1] + f[i-2]) %  mod;
    }

    c[0][0] = 1;
    for( i = 1; i <= 1000; i ++ ) {
        for( j = 0; j <= i; j ++ ) {
            if( j == 0 || j == i )
                c[i][j] = 1;
            else
                c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % mod;
        }
    }
    while( scanf( "%d %d", &n, &m ) != EOF ) {
        ll ans = 0;
        for( i = 0; i <= m; i ++ ) {
            ans = ( ans + f[n-i] * c[n][i] ) % mod; 
        }
        printf("%I64d\n", ans );
    }
    return 0;
}

