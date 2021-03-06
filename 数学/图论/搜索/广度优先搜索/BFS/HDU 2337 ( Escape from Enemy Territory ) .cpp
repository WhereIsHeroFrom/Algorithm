#include <iostream>
using namespace std;

int dir[ 4 ][ 2 ] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct point {
    int x;
    int y;
    int step;
}temp, tt, RP[ 10010 ];
int t;
int n, X, Y;
int step[ 1010 ][ 1010 ];
int hash[ 1010 ][ 1010 ];

int dx, dy;
int T;

point q[ 1500100 ];

int front, rear;

void bfs() {

    int i;
    point temp;
    while ( front < rear ) {
        temp = q[ front ++ ];

        for(i = 0; i < 4; i++) {
            tt.x = temp.x + dir[i][0];
            tt.y = temp.y + dir[i][1];

            if( tt.x < 0 || tt.y < 0 || tt.x >= X || tt.y >= Y )
                continue;

            tt.step = temp.step + 1;

            if( tt.step < step[ tt.x ][ tt.y ] ) {
                step[ tt.x ][ tt.y ] = tt.step;
                q[ rear ++ ] = tt;
            }
        }
    }
}

int BFS( int x, int y, int mid ) {
    int i;

    point temp;

    temp.x = x;
    temp.y = y;
    temp.step = 0;

    if( step[ temp.x ][ temp.y ] < mid )
        return -1;

    front = rear = 0;

    q[ rear ++ ] = temp;

    while( front < rear ) {
        temp = q[ front ++ ] ;

        if( temp.x == dx && temp.y == dy )
            return temp.step;

        for(i = 0; i < 4; i++) {
            tt.x = temp.x + dir[i][0];
            tt.y = temp.y + dir[i][1];
            tt.step = temp.step + 1;

            if( tt.x < 0 || tt.y < 0 || tt.x >= X || tt.y >= Y )
                continue;

            if( hash[ tt.x ][ tt.y ] == T ) {
                continue;
            }

            if( step[ tt.x ][ tt.y ] >= mid ) {
                hash[ tt.x ][ tt.y ] = T;
                q[ rear ++ ] = tt;
            }
        }
    }

    return -1;
}

int main() {

    point temp;
    int low, high, mid;
    int i, j;
    T = 1;
    scanf("%d", &t);

    while( t-- ) {
        scanf("%d %d %d", &n, &X, &Y);
        scanf("%d %d", &temp.x, &temp.y);
        scanf("%d %d", &dx, &dy);

        for(i = 0; i < X; i++ ) {
            for(j = 0; j < Y; j++) {
                step[i][j] = 1000000000;
            }
        }

        for(i = 0; i < n; i++) {
            scanf( "%d %d", &RP[i].x, &RP[i].y );
        }


        front = rear = 0;

        for(i = 0; i < n; i++) {
            step[ RP[i].x ][ RP[i].y ] = 0;
            point tt;
            tt.x = RP[i].x;
            tt.y = RP[i].y;
            tt.step = 0;
            q[ rear ++ ] = tt;
        }
        bfs();

        low = 0;
        high = X + Y;    
        int buf = 0;

        while( low < high ) {
            mid = ( low + high ) / 2;
            T++;
            if( BFS( temp.x, temp.y, mid ) != -1 ) {
                low = mid + 1;
            }else
                high = mid - 1;
        }

        int op = mid + 3;

        for(i = op; i >= op - 6 && i >= 0; i-- ) {
            T++;
            buf = BFS( temp.x, temp.y, i );
            if( buf != -1 ) {
                break;
            }
        }
        printf("%d %d\n", i, buf);
    }

    return 0;
}

