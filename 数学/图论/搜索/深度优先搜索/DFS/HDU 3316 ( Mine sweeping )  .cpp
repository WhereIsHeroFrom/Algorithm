#include <iostream>

using namespace std;

int N;
char map[1010][1010];
int x, y;
int hash[ 1010 ][ 1010 ];
int dir[8][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1 }
};

void dfs( int x, int y) {
    int tx, ty;
    int i;

    if( hash[x][y] != -1 ) return ;

    hash[x][y] = 0;
    for( i = 0; i < 8; i ++ ) {
        tx = x + dir[i][0];
        ty = y + dir[i][1];

        if( tx < 0 || ty < 0 || tx >= N || ty >= N )
            continue;
        hash[ x ][ y ] += (map[tx][ty] == 'X');
    }

    if( !hash[x][y] ) {
        for( i = 0; i < 8; i ++ ) {
            tx = x + dir[i][0];
            ty = y + dir[i][1];
            
            if( tx < 0 || ty < 0 || tx >= N || ty >= N )
                continue;
            dfs( tx, ty );
        }
    }
}
int main() {
    int i, j;
    while( scanf( "%d", &N ) != EOF ) {
        for( i = 0; i < N; i ++ ) {
            scanf("%s", map[i] );
        }
        scanf("%d %d", &x, &y );

        if( map[x][y] == 'X' )
            printf("it is a beiju!\n");
        else {
            memset( hash, -1, sizeof( hash ) );
            dfs( x, y );
            for( i = 0; i < N; i ++ ) {
                for( j = 0; j < N; j ++ ) {
                    if( hash[i][j] == -1 )
                        printf(".");
                    else
                        printf("%d", hash[i][j] );
                }
                puts("");
            }
        }
        puts("");
    }
    return 0;
}

