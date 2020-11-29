/*
    题解：奇环 or 结点数目大于1的连通块数目 超过1个 都是不合法的
*/
#include <iostream>

using namespace std;

#define MAXN 400

char mat[MAXN][MAXN];
int color[MAXN];
int n;
int cnt, cntv;

bool dfs(int u, int c) {
    int i;
    if(color[u] == -1) {
        cnt ++;
        color[u] = c;
    }else {
        return (color[u] == c);    
    }
    
    for(i = 0; i < n; i++) {
        if(mat[u][i] == '0') continue;
        if( !dfs(i, c^1) ) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    int i;
    scanf("%d", &t);

    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%s", mat[i]);
        }
        memset(color, -1, sizeof(color));
        cntv = 0;
        for(i = 0; i < n; i++) {
            if(color[i] == -1) {
                cnt = 0;
                if( !dfs(i, 0) ) {
                    break;
                }
                if( cnt > 1 ) {
                    cntv++;
                    if(cntv >= 2) break;
                }
            }
        }
        printf("%s\n", (i==n) ? "Yes" : "No");
    }
    return 0;
}
/*
30 
4 
0011 
0001 
1000 
1100 
4 
0111 
1001 
1001 
1110 
3 
000
000 
000
3
011
101
110
4
0100
1000
0001
0010
*/
