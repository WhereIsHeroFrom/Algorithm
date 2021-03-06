#include <iostream>
using namespace std;

#define maxn 110 
#define inf (1<<29)

int n, m;
int map[ maxn ][ maxn ];

int main() {
    int t;
    int i, j, k;
    int x, y, z;
    int As, Bs;

    scanf("%d", &t);

    while( t-- ) {
        scanf("%d %d", &n, &m );

        for( i = 1; i <= n; i++ ) {
            for( j = 1; j <= n; j ++ ) {
                if( i == j )
                    map[i][j] = 0;
                else
                    map[i][j] = inf;
            }
        }
        while( m-- ) {
            scanf("%d %d %d", &x, &y, &z );
            if( z < map[x][y] ) {
                map[x][y] = map[y][x] = z;
            }
        }

        scanf("%d %d", &As, &Bs );


        for( k = 1; k <= n; k ++ ) {
            for( i = 1; i <= n; i ++ ) {
                for( j = 1; j <= n; j ++ ) {
                    if( map[i][k] + map[k][j] < map[i][j] )
                        map[i][j] = map[i][k] + map[k][j];
                }
            }
        }



        int Q;
        scanf("%d", &Q );

        while( Q-- ) {
            scanf("%d", &x );
            for( i = 1; i <= n; i ++ ) {
                if( i != x ) {
                    if( map[i][As] + map[i][Bs] <
                        map[x][As] + map[x][Bs] )
                        break;
                }
            }

            if( i == n + 1 )
                printf("Yes\n");
            else
                printf("No\n");
        }

    
    }
    return 0;
}

