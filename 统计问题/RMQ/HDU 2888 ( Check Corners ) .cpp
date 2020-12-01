#include <iostream>
#include <cmath>
using namespace std;


int Max[301][301][9][9];
int map[301][301];
int n, m;
int f[ 11 ];
int Log[ 310 ];

struct RMQ {
    void preCal();
    int MMax( int a, int b );
    int Query( int lx, int ly, int rx, int ry );
}R;

int RMQ:: MMax( int a, int b ) {
    return a > b ? a : b;
}

void RMQ::preCal() {
    int i, j, row, col;
    f[0] = 1;

    for( i = 1; i <= 10; i++ )
        f[i] = f[i-1] * 2;

    for(i = 1; i <= 300; i++ )
        Log[i] = log( i * 1.0 ) / log( 2.0 ) + 1e-6;

    for( row = 1; row <= n; row++) {
        for(col = 1; col <= m; col++) {
            Max[row][col][0][0] = map[row][col];
        }
    }

    for( i = 0; f[i] <= n ; i++) {
        for(j = 0; f[j] <= m ; j++) {
            if( i == 0 && j == 0 )
                continue;
            for(row = 1; row + f[i] - 1 <= n; row++ ) {
                for(col = 1; col + f[j] - 1 <= m; col++) {

                    if( i == 0 ) {
                        Max[row][col][i][j] = MMax(Max[row][col][i][j-1],Max[row][ col+f[j-1] ][i][j-1]);
                    }else if( j == 0 ){
                        Max[row][col][i][j] = MMax(Max[row][col][i-1][j],Max[ row+f[i-1] ][col][i-1][j]);
                    }else {
                        int a, b;
                        a = MMax(Max[row][col][i][j-1],Max[row][ col+f[j-1] ][i][j-1]);
                        b = MMax(Max[row][col][i-1][j],Max[ row+f[i-1] ][col][i-1][j]);
                        Max[row][col][i][j] = MMax( a, b );
                    }
                }
            }
        }
    }
}

int RMQ::Query( int lx, int ly, int rx, int ry ) {

    int drow = Log[ rx - lx + 1 ];
    int dcol = Log[ ry - ly + 1 ];
    return MMax( MMax( Max[lx][ly][drow][dcol], Max[rx-f[drow]+1][ry-f[dcol]+1][drow][dcol]), MMax( Max[lx][ry-f[dcol]+1][drow][dcol], Max[rx-f[drow]+1][ly][drow][dcol] ) );
}


int main() {
    int i, j;
    int Q;
    int lx, ly, rx, ry;



    while( scanf( "%d %d", &n, &m ) != EOF ) {
        for( i = 1; i <= n; i++) {
            for( j = 1; j <= m; j++) {
                scanf("%d", &map[i][j]);
            }
        }
        R.preCal();
        scanf("%d", &Q);
        while( Q -- ) {
            scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
            int p = R.Query( lx, ly, rx, ry );
            printf("%d ", p);
            if( map[lx][ly] == p || map[rx][ry] == p || map[lx][ry] == p || map[rx][ly] == p )
                printf("yes\n");
            else
                printf("no\n");
        }
    }
}


