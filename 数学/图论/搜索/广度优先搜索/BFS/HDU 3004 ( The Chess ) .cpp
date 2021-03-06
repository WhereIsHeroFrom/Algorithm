/*
16:18 ~ 16:52
*/
#include <iostream>
#include <queue>
using namespace std;

int n, m;

struct point {
    int x, y;
    bool active;
    point() {
        x = 0;
        y = 0;
    }
    point( int _x, int _y ) {
        x = _x;
        y = _y;
        active = true;
    }
};

struct node {
    point C, M, P;
    int step;
}temp, tt;

int hash[11][11][11][11][11][11];
int cas;
char map[12][12];
int X[12][12], A;

int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
int M[8][2] = { {-1, 2}, {1, 2}, {-1, -2}, {1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };

queue < node > q;

bool Bound( int x, int y ) {
    return (x < 0 || y < 0 || x >= n || y >= m);
}

bool BieJiao( int x, int y ) {
    if( X[x][y] == A )
        return true;
    if( map[x][y] == 'D' || map[x][y] == 'S' )
        return true;
    return false;
}

bool Block( int x, int y ) {
    if( X[x][y] == A )
        return true;
    if( map[x][y] == 'D' )
        return true;
    return false;
}


int BFS() {

    int i;
    temp.step = 0;
    while( !q.empty() )
        q.pop();

    q.push( temp );

    while( !q.empty() ) {
        temp = q.front();
        q.pop();
        A ++;

        X[ temp.M.x ][ temp.M.y ] = A;
        X[ temp.C.x ][ temp.C.y ] = A;
        X[ temp.P.x ][ temp.P.y ] = A;

        if( map[ temp.C.x ][ temp.C.y ] == 'S' ||
            map[ temp.M.x ][ temp.M.y ] == 'S' ||
            map[ temp.P.x ][ temp.P.y ] == 'S'    
            ) {
            return temp.step;
        }

        if( temp.C.active ) {
            for( i = 0; i < 4; i ++ ) {
                tt = temp;
                tt.step ++;
                
                int Count = 1;
                while(1) {
                    tt.C.x = temp.C.x + Count * dir[i][0];
                    tt.C.y = temp.C.y + Count * dir[i][1];
                    if( Bound( tt.C.x, tt.C.y ) )
                        break;
                    if( Block( tt.C.x, tt.C.y ) )
                        break;
                    if( hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] != cas ) {
                        hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] = cas;
                        q.push( tt );
                    }
                    Count ++;
                }
            }
        }

        if( temp.M.active ) {
            for( i = 0; i < 8; i ++ ) {
                tt = temp;
                tt.step ++;
                tt.M.x = temp.M.x + dir[ i/2 ][0];
                tt.M.y = temp.M.y + dir[ i/2 ][1];
                if( Bound( tt.M.x, tt.M.y ) )
                    continue;
                if( BieJiao( tt.M.x, tt.M.y ) )
                    continue;

                tt.M.x = temp.M.x + M[i][0];
                tt.M.y = temp.M.y + M[i][1];
                if( Bound( tt.M.x, tt.M.y ) )
                    continue;
                if( Block( tt.M.x, tt.M.y ) )
                    continue;
                if( hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] != cas ) {
                    hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] = cas;
                    q.push( tt );
                }
            }
        }

        if( temp.P.active ) {
            // 走炮
            for( i = 0; i < 4; i ++ ) {
                tt = temp;
                tt.step ++;
                
                int Count = 1;
                while(1) {
                    tt.P.x = temp.P.x + Count * dir[i][0];
                    tt.P.y = temp.P.y + Count * dir[i][1];
                    if( Bound( tt.P.x, tt.P.y ) )
                        break;
                    if( BieJiao( tt.P.x, tt.P.y ) )
                        break;
                    if( hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] != cas ) {
                        hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] = cas;
                        q.push( tt );
                    }
                    Count ++;
                }
            }

            for( i = 0; i < 4; i ++ ) {
                tt = temp;
                tt.step ++;
                
                int flag = -1;
                int Count = 1;
                while(1) {
                    tt.P.x = temp.P.x + Count * dir[i][0];
                    tt.P.y = temp.P.y + Count * dir[i][1];
                    if( Bound( tt.P.x, tt.P.y ) )
                        break;
                    Count ++;
                    if( BieJiao( tt.P.x, tt.P.y ) ) {
                        flag = 0;
                        break;
                    }
                }

                if( flag != -1 ) {
                    while(1) {
                        tt.P.x += dir[i][0];
                        tt.P.y += dir[i][1];
                        if( Bound( tt.P.x, tt.P.y ) )
                            break;
                        if( map[tt.P.x][tt.P.y] == 'S' ) {
                            if( hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] != cas ) {
                                hash[tt.C.x][tt.C.y][tt.M.x][tt.M.y][tt.P.x][tt.P.y] = cas;
                                q.push( tt );
                            }
                            break;
                        }
                        if( Block( tt.P.x, tt.P.y ) )
                            break;
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    int i, j;
    while( scanf( "%d %d", &n, &m ) != EOF ) {
        cas ++;
        temp.C.active = temp.M.active = temp.P.active = false;
        for( i = 0; i < n; i ++ ) {
            scanf("%s", map[i] );
            for( j = 0; j < m; j ++ ) {
                if( map[i][j] == 'C' ) {
                    temp.C = point( i, j );
                    map[i][j] = '.';
                }else if( map[i][j] == 'M' ) {
                    temp.M = point( i, j );
                    map[i][j] = '.';
                }else if( map[i][j] == 'P' ) {
                    temp.P = point( i, j );
                    map[i][j] = '.';
                }
            }
        }
        printf("Scenario #%d\n", cas );
        int u = BFS();
        if( u == -1 )
            printf("OH!That's impossible!\n");
        else
            printf("%d\n", u );
        puts("");
    }
}

