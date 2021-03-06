#include <iostream>
#include <cmath>
using namespace std;

struct point {
    __int64 n;
    __int64 x;
}f[ 200 ], R[ 200 ];
int top;
__int64 n;

int main() {
    __int64 i;
    /*for(i = 1; ; i++) {
        __int64 rt = 2 * i * i + 3 * i + 1 ;
        if( rt % 6 == 0 ) {
            rt /= 6;
            __int64 p = sqrt( rt * 1.0 );
            if( p * p == rt ) {
                printf("%I64d %I64d %I64d\n", i, 4 * i + 3, p );
            }
        }
    }*/

    top = 0;

    f[1].n = 7;
    f[1].x = 1;

    R[ top ].n = f[1].n / 4;
    R[ top++ ].x = 1;

    for(i = 2; i <= 50; i++) {
        f[i].n = 7 * f[i-1].n + 48 * f[i-1].x;
        f[i].x = f[i-1].n + 7 * f[i-1].x;

        if( f[i].x > 0 ) {
            if( f[i].n % 4 == 3 ) {
                R[ top ].n = f[i].n / 4;
                R[ top++ ].x = f[i].x;
            }
        }else
            break;
    }

    while( scanf( "%I64d", &n ) != EOF && n ) {
        for(i = 0; i < top; i++) {
            if( R[i].n > n )
                break;
        }
        printf( "%I64d %I64d\n", R[i - 1].n, R[i - 1].x );
    }
}
