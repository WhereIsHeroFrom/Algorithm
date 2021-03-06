#include <iostream>

using namespace std;

int n;
char str[ 1000 ];
char cmd[ 1000 ];

int now[ 200 ][ 200 ];
int id[ 200 ][ 200 ];
int l, r;
int i, j;

int main() {
    int Cas = 0;

    while( scanf( "%d", &n ) != EOF && n ) {
        scanf("%s", &str[1] );
        for( i = 1; i <= n; i++ ) {
            now[i][0] = 0;
            now[i][ ++now[i][0] ] = ( str[i] == 'U' ) ? 1 : 0;
            id[i][ now[i][0] ] = i;
        }
        l = 1;
        r = n;

        scanf("%s", cmd );

        for( i = 0; i < n-1; i ++ ) {
            if( cmd[i] == 'L' ) {
                for( j = now[l][0]; j >= 1; j-- ) {
                    now[l+1][ ++now[l+1][0] ] = (now[l][j]^1);
                    id[l+1][ now[l+1][0] ] = id[l][j];
                }
                l ++;
            }else {
                for( j = now[r][0]; j >= 1; j-- ) {
                    now[r-1][ ++now[r-1][0] ] = (now[r][j]^1);
                    id[r-1][ now[r-1][0] ] = id[r][j];
                }
                r --;
            }
        }

        int m;
        printf("Pile %d\n", ++Cas );
        scanf("%d", &m );

        for( i = 1; i <= m; i ++ ) {
            int x; 
            scanf( "%d", &x );
            printf( "Card %d is a face ", x );

            x = n+1 - x;
            if( !now[l][x] )
                printf("down");
            else
                printf("up");
            printf(" %d.\n", id[l][x] );
        }
    }
    return 0;
}

