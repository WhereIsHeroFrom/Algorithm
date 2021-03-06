#include <iostream>
#include <cstring>

using namespace std;

int n, m;
#define MAXN 6
char M[MAXN][MAXN];

void output(char M[MAXN][MAXN]) {
    return ;
    int i, j;
    for(i = 0; i < n; ++i) {
        for(j = 0;j < m; ++j) {
            printf("%d", (int)M[i][j]);
        }
        puts("");
    }
    puts("");
}

bool isEmpty(char M[MAXN][MAXN]) {
    int i, j;
    for(i = n-1; i >= 0; --i) {
        for(j = 0; j < m; ++j) {
            if(M[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int dir[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};

void floodFill(int x, int y, char color, bool hashv[MAXN][MAXN], char M[MAXN][MAXN]) {
    if(x < 0 || y < 0 || x >= n || y >= m) return ;
    if(M[x][y] != color) return ;

    hashv[x][y] = 1;
    M[x][y] = 0;
    int i;
    for(i = 0; i < 4; ++i) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        floodFill(tx, ty, color, hashv, M);
    }
}

void down(int n, int idx, char nextM[MAXN][MAXN]) {
    int i, j;
    for(i = 0; i < n; ++i) {
        if(!nextM[i][idx]) {
            for(j = i; j > 0; --j) {
                nextM[j][idx] = nextM[j-1][idx];
            }
            nextM[0][idx] = 0;
        }
    }
}

void left(int n, int m, int start, char nextM[MAXN][MAXN]) {
    int i, j;
    for(i = start; i < m; i++) {
        for(j = 0; j < n; j++) {
            if(i == m-1) {
                nextM[j][i] = 0;
            }else
                nextM[j][i] = nextM[j][i+1];
        }
    }
}

void createNextM(int px, int py, bool hashv[MAXN][MAXN], char nowM[MAXN][MAXN], char nextM[MAXN][MAXN]) {
    int i, j;
    for(i = 0; i < n; ++i) {
        for(j = 0; j < m; ++j) {
            nextM[i][j] = nowM[i][j];
        }
    }
    floodFill(px, py, nextM[px][py], hashv, nextM);

    output(nextM);
    // 下降
    for(i = m-1; i >= 0; --i) {
        down(n, i, nextM);

        output(nextM);
        if(!nextM[n-1][i]) {
            // 左移
            left(n, m, i, nextM);
        }
    }
}

bool dfs(int depth, int maxDepth, char M[MAXN][MAXN]) {
    int i, j;
    bool hashv[MAXN][MAXN];
    memset(hashv, 0, sizeof(hashv));

    output(M);
    if(isEmpty(M)) {
        return true;
    }
    if(depth == maxDepth) {
        return false;
    }
    for(i = 0; i < n; ++i) {
        for(j = 0; j < m; ++j) {
            if(hashv[i][j]) continue;
            if(M[i][j] == 0) continue;
            char nextM[MAXN][MAXN];
            createNextM(i, j, hashv, M, nextM);
            if( dfs(depth+1, maxDepth, nextM) ) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF) {
        for(i = 0; i < n; ++i) {
            for(j = 0; j < m; ++j) {
                int v;
                scanf("%d", &v);
                M[i][j] = v;
            }
        }
        for(i = 0; ; ++i) {
            if(dfs(0, i, M)) break;
        }
        printf("%d\n", i);
    }
    return 0;
}

/*
5 5
0 0 0 0 0
0 0 0 0 0
0 2 2 0 0
0 2 1 0 0
1 2 1 1 1

5 5
1 2 3 4 5
1 2 3 4 5
0 0 0 0 0
0 0 0 0 0
1 1 1 1 1
*/
