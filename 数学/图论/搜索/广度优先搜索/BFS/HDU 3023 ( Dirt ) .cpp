#include <iostream>
#include <queue>
using namespace std;

struct point {
    int change;
    int step;
    short x, y;

    bool friend operator < ( point a, point b ) {
        if( a.change != b.change )
            return a.change > b.change;
        return a.step > b.step;
    }
}temp, tt;
priority_queue < point > q;

char map[1010][1010];
int hash[1010][1010];
int MinC[1010][1010];
int MinS[1010][1010];
int dir[8][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1} };
point st, en;
int cas;
int n, m;

bool BFS( int &change, int &path ) {
    temp.x = st.x;
    temp.y = st.y;
    temp.step = 0;
    temp.change = 0;
    while( !q.empty() )
        q.pop();
    q.push( temp );

    int i;
    cas ++;
    while( !q.empty() ) {
        temp = q.top();
        q.pop();

        if( temp.x == en.x && temp.y == en.y ) {
            change = temp.change;
            path = temp.step;
            return true;
        }
        //printf("%d %d\n", temp.x, temp.y );

        for( i = 0; i < 8; i ++ ) {
            tt.x = temp.x + dir[i][0];
            tt.y = temp.y + dir[i][1];
            if( tt.x < 1 || tt.y < 1 || tt.x > n || tt.y > m )
                continue;
            if( map[ tt.x ][ tt.y ] == '0' )
                continue;
            tt.step = temp.step + 1;
            tt.change = temp.change;
            if( map[ tt.x ][ tt.y ] != map[ temp.x ][ temp.y ] ) {
                tt.change ++;
            }

            if( hash[ tt.x ][ tt.y ] != cas ) {
                hash[ tt.x ][ tt.y ] = cas;
                MinC[ tt.x ][ tt.y ] = tt.change;
                MinS[ tt.x ][ tt.y ] = tt.step;
                q.push( tt );
            }else {
                if( MinC[ tt.x ][ tt.y ] > tt.change ) {
                    MinC[ tt.x ][ tt.y ] = tt.change;
                    MinS[ tt.x ][ tt.y ] = tt.step;
                    q.push( tt );
                }else if( MinC[ tt.x ][ tt.y ] == tt.change && MinS[ tt.x ][ tt.y ] > tt.step ) {
                    MinS[ tt.x ][ tt.y ] = tt.step;
                    q.push( tt );
                }
            }
        }
    }
    return false;
}

int main() {
    int i, j;
    while( scanf( "%d %d", &n, &m ) != EOF ) {
        scanf("%d %d", &st.x, &st.y );
        scanf("%d %d", &en.x, &en.y );
        for( i = 1; i <= n; i ++ ) {
            scanf("%s", &map[i][1] );
        }
        int path, change;
        if( !BFS(change, path ) ) {
            printf("0 0\n" );
        }else
            printf("%d %d\n", path + 1, change );
    }
    return 0;
}
