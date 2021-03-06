#include <iostream>
#include <cmath>

using namespace std;

int n;
int i, j;

int V[ 1000 ];

int main() {
    for( i = -600; i <= 100; i ++ )
        V[ i+600 ] = i*i*i;

    while( scanf( "%d", &n ) != EOF && n ) {
        int flag = 0;
        for( i = -600; i <= 100; i ++ ) {
            int u = pow( n - V[i+600]*1.0, 1.0/3 );

            for( j = u-2; j <= u+2; j ++ ) {
                if( j*j*j + V[i+600] == n )
                    break;
            }
            if( j <= u+2 ) {
                flag = 1;
                break;
            }

        }
        if( flag )
            printf("%d %d\n", i, j );
        else
            printf("Impossible\n");
    }
    return 0;
}

