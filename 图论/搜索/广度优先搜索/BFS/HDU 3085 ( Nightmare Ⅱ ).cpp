#include <iostream>
using namespace std;

#define MAXN 810
#define INF 10000000

int ABS(int a) {
    return a < 0 ? -a : a;
}

int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

class pathInfos {
public:
    short r, c;
    int sec;
    pathInfos(){}
    pathInfos(int _r, int _c, int _s) {
        r = _r;
        c = _c;
        sec = _s;
    }
    void print() {
        printf("%d %d\n", r, c );
    }
}ghosts[2], start, end;

class Que {
public:
    pathInfos Q[1000010];
    int front, rear;
    void clear() {
        front = rear = 0;
    }
    
    void push(pathInfos p) {
        Q[rear++] = p;
    }
    pathInfos& top() {
        return Q[front];
    }
    void pop() {
        front++;
    }
    bool empty() {
        return front == rear;
    }
};

int gs;
char mat[MAXN][MAXN];
int vis[2][MAXN][MAXN];
int N, M;
Que Q[2];


bool isBlock(int r, int c, int sec) {
    if(r<0||r>=N||c<0||c>=M) return true;
    if(mat[r][c] == 'X') return true;
    for(int i = 0; i < 2; i++) {
        if( 2*sec >= ABS(ghosts[i].r - r) + ABS(ghosts[i].c - c) ) {
            return true;
        }
    }
    return false;
}

int getMove(int idx, int second) {
    int flag = 0;
    int rearTmp = Q[idx].rear;
    
    while(Q[idx].front < rearTmp) {
        pathInfos now = Q[idx].top(), nex;
        Q[idx].pop();
        
        //now.print();
        if( isBlock(now.r, now.c, second) ) {
            continue;
        }        
        
        for(int j = 0; j < 4; j++) {
            nex.r = now.r + dir[j][0];
            nex.c = now.c + dir[j][1];
            if( isBlock(nex.r, nex.c, second) ) {
                continue;
            }
            if(vis[idx^1][nex.r][nex.c]) {
                return 1;
            }
            if( !vis[idx][nex.r][nex.c] ) {
                vis[idx][nex.r][nex.c] = 1;
                Q[idx].push( nex );
                flag = 2;
            }
        }  
    }
    return flag;
}

int bfs() {
    int i, j, k;
    memset(vis, 0, sizeof(vis));
    Q[0].clear();
    Q[1].clear();
    
    int ans = -1;
    
    vis[0][ start.r ][ start.c ] = 1;
    vis[1][ end.r ][ end.c ] = 1;
    
    Q[0].push( start );
    Q[1].push( end );
    
    int second = 0;
    while(1) {
        second ++;
        int flag = 0;
        
        for(i = 1; i <= 3; i++) {
            int v = getMove(0, second);
            if( v == 1 ) {
                return second;
            }
            flag |= v;
        }
        
        int v = getMove(1, second);
        if( v == 1 ) {
            return second;
        }
        flag |= v;
        
        if(!flag) break;
    }
    return -1;
}

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d %d", &N, &M);
        gs = 0;
        for(i = 0; i < N; i++) {
            scanf("%s", mat[i]);
            for(j = 0; j < M; j++) {
                if(mat[i][j] == 'Z') {
                    ghosts[ gs++ ] = pathInfos(i, j, 0);
                }else if(mat[i][j] == 'M') {
                    start = pathInfos(i, j, 0);
                }else if(mat[i][j] == 'G') {
                    end = pathInfos(i, j, 0);
                }
            }
        }
        printf( "%d\n", bfs() );
    }    
    return 0;
}
/*
10
5 6
XXXXXX
XZ..ZX
XXXXXX
M.....
...G..
5 6
XXXXXX
XZ..ZX
XXXXXX
M...G.
......

10 10
..........
..X.......
..M.X...X.
X.........
.X..X.X.X.
.........X
..XX....X.
X....G...X
...ZX.X...
...Z..X..X
*/
