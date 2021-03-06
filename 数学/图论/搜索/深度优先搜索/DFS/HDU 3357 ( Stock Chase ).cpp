#include <iostream>

using namespace std;

int n, m;
int map[235][235];
int ans = 0;
int i;
int cas;

void dfs( int x, int y ) {
    int i;
    for( i = 1; i <= n; i ++ ) {
        if( map[y][i] == cas ) {
            if( map[x][i] != cas ) {
                map[x][i] = cas;
                dfs( x, i );
            }
        }
    }
}

int main() {
    while( scanf( "%d %d", &n, &m ) != EOF && (n||m) ) {
        cas ++;
        ans = 0;
        while( m-- ) {
            int x, y;
            scanf("%d %d", &x, &y );
            if( x == y ) {
                ans ++;
                continue;
            }
            if( map[x][y] == cas )
                continue;
            if( map[y][x] == cas ) {
                ans ++;
                continue;
            }
            map[x][y] = cas;
            dfs( x, y );

            for( i = 1; i <= n; i ++ ) {
                if( map[i][x] == cas ) {
                    map[i][y] = cas;
                    dfs( i, y );
                }
            }
        }

        printf("%d. %d\n", cas, ans );

    }
    return 0;
}

