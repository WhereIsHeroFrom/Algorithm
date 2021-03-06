#include <iostream>
#include <queue>

using namespace std;

int n, E;
int map[ 20 ][ 20 ];
int V[ 20 ], C[ 20 ];
int Max;

struct point {
    int state;
    int RemE;
    int Val;
}temp, tt;

queue < point > q;

void bfs() {
    int i, j;
    while( !q.empty() ) {
        temp = q.front();
        q.pop();

        if( temp.Val > Max ) Max = temp.Val;

        for( i = 0; i < n; i ++ ) {
            if( temp.state & (1<<i) )
                continue;
            for( j = 1; j <= map[i][0]; j ++ ) {
                if( temp.state & (1<<map[i][j]) ) 
                    continue;
                else
                    break;
            }

            if( j == map[i][0] + 1 ) {
                if( temp.RemE >= C[i] ) {
                    tt.RemE = temp.RemE - C[i];
                    tt.state = temp.state | (1<<i);
                    tt.Val = temp.Val + V[i];
                    q.push( tt );
                }
            }
        }
    }
}

int main() {
    int t;
    int i, j;
    scanf("%d", &t);

    while( t-- ) {
        scanf("%d %d", &n, &E );
        for( i = 0; i < n; i ++ ) {
            scanf("%d", &V[i] );
        }
        for( i = 0; i < n; i ++ ) {
            scanf("%d", &C[i] );
        }

        Max = 0;

        while(!q.empty()) q.pop();
        for( i = 0; i < n; i ++ ) {
            scanf("%d", &map[i][0] );
            for( j = 1; j <= map[i][0]; j ++ ) {
                scanf("%d", &map[i][j] );
                map[i][j] --;
            }
            if( map[i][0] == 0 ) {
                if( E >= C[i] ) {
                    temp.RemE = E - C[i];
                    temp.state = (1<<i);
                    temp.Val = V[i];
                    q.push( temp );
                }
            }
        }
        bfs();
        printf("%d\n", Max );
    }
    return 0;
}

