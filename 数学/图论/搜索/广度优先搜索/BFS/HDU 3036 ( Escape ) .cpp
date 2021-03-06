#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
 
int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
int t;
int n, m;
int i, j, k;
char map[ 20 ][ 20 ];
int T, S;
 
struct point {
    int x, y;
    int step;
    int DoorID;
}temp, tt;
queue < point > q;
 
int DIS[200][200];
int Dot[20][20];
int Door[20][20];
int DotMin[200];
 
vector < int > vec[ 200 ];
int pre[ 200 ];
int visit[ 200 ];
int hash[ 200 ];
 
void bfs() {
    int i;
    while( !q.empty() ) {
        temp = q.front();
        q.pop();
 
        for( i = 0; i < 4; i++) {
            tt.x = temp.x + dir[i][0];
            tt.y = temp.y + dir[i][1];
            tt.DoorID = temp.DoorID;
            tt.step = temp.step + 1;
 
            if( tt.x < 0 || tt.y < 0 || tt.x >= n || tt.y >= m )
                continue;
 
            if( map[tt.x][tt.y] == '.' ) {
                int Step = DIS[ tt.DoorID ][ Dot[tt.x][tt.y] ];
                if( Step == -1 || tt.step < Step ) {
                    DIS[ tt.DoorID ][ Dot[tt.x][tt.y] ] = tt.step;
                    q.push( tt );
                }
            }
        }
    }
}
 
int dfs( int key ) {
    int size = vec[ key ].size();
    int i, k;
 
    for(i = 0; i < size; i++) {
        int nex = vec[key][i];
 
        if( !visit[ nex ] ) {
            visit[ nex ] = 1;
            k = pre[ nex ];
            pre[ nex ] = key;
 
            if( k == -1 || dfs( k ) )
                return 1;
            pre[ nex ] = k;
        }
    }
    return 0;
}
 
int main() {
    int Time;
    
    int TTT;
 
    while( scanf("%d %d %d", &n, &m, &TTT) != EOF ) {
        for(i = 0; i < n; i++) {
            scanf("%s", map[i] );
        }
        T = 1;
        S = 1;
        
        memset( DIS, -1, sizeof( DIS ));
 
        while( !q.empty() )
            q.pop();
 
        for(i = 0; i < n; i++) {
            for( j = 0; j < m; j++) {
                if( map[i][j] == '.' ) {
                    Dot[i][j] = T++;
                }else if( map[i][j] == 'E' ) {
                    Door[i][j] = S++;
                    temp.x = i;
                    temp.y = j;
                    temp.step = 0;
                    temp.DoorID = S-1;
                    q.push( temp );
                }
            }
        }
 
        if( T == 1 ) {
            printf("0\n");
            continue;
        }
 
        // 对D进行bfs，求出他到所有点的最短路
        bfs();
        S--;
        T--;
 
        for(i = 1; i <= T; i++) {
            DotMin[i] = INT_MAX;
            for(j = 1; j <= S; j++) {
                if( DIS[j][i] != -1 ) {
                    if( DIS[j][i] < DotMin[i] ) 
                        DotMin[i] = DIS[j][i];
                }
            }
 
            if( DotMin[i] == INT_MAX )
                break;
        }
        if( i <= T ) {
            puts("impossible");
            continue;
        }
 
        int ALL;
        int Min = INT_MAX;
        int Count = 6;
 
        
        while( Count -- ) {
 
            ALL = T;
            memset( hash, 0, sizeof( hash ));
 
            for(Time = 1; ; Time++) {
                for(i = 1; i <= S; i++) {
                    vec[i].clear();
                }
 
                memset( pre, -1, sizeof ( pre ));
 
                for(i = 1; i <= S; i++) {
                    for( j = 1; j <= T; j++) {
                        if( DIS[i][j] != -1 && !hash[ j ] ) {
                            if( DIS[i][j] <= Time ) {
                                vec[i].push_back(j);
                            }
                        }
                    }
 
                    if( vec[i].size() ) {
                        int C = 4;
                        while( C-- ) {
                            int temp1 = rand() % vec[i].size();
                            int temp2 = rand() % vec[i].size();
                            int temp3 = vec[i][temp1];
                            vec[i][temp1] = vec[i][temp2];
                            vec[i][temp2] = temp3;
                        }
                    }
 
                }
 
                for(i = 1; i <= S; i++) {
                    memset( visit, 0, sizeof( visit ));
                    if( dfs( i ) )
                        ALL --;
                }
 
                for( i = 1; i <= T; i++ ) {
                    if( !hash[i] && pre[i] != -1 ) {
                        hash[i] = 1;
                    }
                }
 
                if( ALL == 0 )
                    break;
            }
 
            if( Time < Min )
                Min = Time;
        }
 
        if( Min <= TTT ) {
            printf("%d\n", Min );
        }else
            printf("impossible\n");
    }
    return 0;
}
