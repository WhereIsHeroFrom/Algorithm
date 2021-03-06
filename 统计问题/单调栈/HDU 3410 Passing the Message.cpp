#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

int    a[ 50010 ];
int O[2][ 50010 ];

int stack[ 50010 ], top;
int i, j, n;

int main() {
    int t;
    int ty;
    scanf("%d", &t );
    ty = t;
    while( t-- ) {
        scanf("%d", &n );
        for( i = 1; i <= n; i ++ ) {
            scanf("%d", &a[i] );
        }
        for( i = 0; i < 2; i ++ ) {
            top = 0;
            stack[ ++top ] = 1;
            for( j = 1; j <= n; j ++ )
                O[i][j] = 0;

            for( j = 2; j <= n; j++ ) {
                int now = a[j];
                int pre = a[ stack[ top ] ];
                while( top && now > pre ) {
                    top --;
                    if( top )
                        pre = a[ stack[ top ] ];
                }
                stack[ ++top ] = j;
                
                if( top > 1 ) {
                    O[i][ stack[top-1 ] ] = j;
                    //printf("%d %d\n", a[ stack[top-1] ], a[j] );
                }
            }
            for( j = 1; j <= n / 2; j ++ ) {
                int tmp = a[j];
                a[j] = a[ n+1-j ];
                a[ n+1-j ] = tmp;
            }
        }


        printf("Case %d:\n", ty - t );
        for( i = 1; i <= n; i ++ ) {
            printf("%d %d\n", O[1][n+1-i] ? n+1 - O[1][n+1-i] : 0, O[0][i] );
        }
    }
    return 0;
}
