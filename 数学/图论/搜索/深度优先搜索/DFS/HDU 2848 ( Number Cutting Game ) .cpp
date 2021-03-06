#include <iostream>
#include <algorithm>
using namespace std;
#define Mod 100007
#define LL __int64
LL n;
int k;
LL TY[ 40 ][ 50000 ], TN[ 40 ];
LL R, Ten;
LL f[ 100 ];
int hash[ 20 ][ 100009 ];
LL Key[ 20 ][   100009 ];

int dfs( LL key );

void DFS( LL rem, LL Sum, int cut) {


    if( cut == 0 ) {
        Sum += rem;
        TY[ R ][ TN[R]++ ] = Sum;
        return ;
    }

    if( rem < f[ cut ] )
        return ;

    int i;
    LL tp = 10;
    LL nrem, nSum;

    while( 1 ) {
        nSum = Sum + rem % tp;
        nrem = rem / tp;

        if( nrem == 0 )
            return ;
        tp *= 10;
        DFS( nrem, nSum, cut-1 );
    }
}

LL _hash( LL N ) {
    LL s = N % Mod;

    while( 1 ) {
        if( hash[ k ][ s ] == -1 ) {
            hash[ k ][ s ] = dfs( N );
            Key[ k ][ s ] = N;
            return hash[ k ][ s ] ;
        }else {

            if( Key[ k ][ s ] == N ) {
                return hash[ k ][ s ];
            }else {
                s = ( s + 11 );

                if( s >= Mod )
                    s %= Mod;
            }
        }
    }
}

int dfs( LL key ) {
    int i;

    if( key < f[ k-1 ] )
        return 2;

    int buf = R;
    TN[ buf ] = 0;
    DFS( key, 0, k-1 );

    for(i = 0; i < TN[ buf ]; i ++ ) {

        R ++;
        int u = _hash( TY[buf][i] );
        if( u == 2 ) {
            R --;
            return 1;
        }
        R --;
    }
    return 2;
}

int main() {
    int i;
    R = 0;

    f[ 0 ] = 1;

    for(i = 1; i < 20; i++)
        f[i] = f[i-1] * 10;
    
    memset( hash, -1, sizeof( hash ) );
    while( scanf("%I64d %I64d", &n, &k) != EOF ) {

        R = 0;
        if( dfs( n ) == 1 )
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}
