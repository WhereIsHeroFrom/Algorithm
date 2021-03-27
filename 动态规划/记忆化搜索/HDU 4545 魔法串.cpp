#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 1010 

char tar[MAXN], src[MAXN];
int dp[MAXN][MAXN], cases=1;
int n, m;
bool mat[300][300];

// x - target
// y - source
bool can_convert(int x, int y) {
    if(x < 0) {
        return 1;
    }
    if(x > y) {
        return 0;
    }
    if(dp[x][y] != -1) {
        return dp[x][y];
    }
    int v = 0; 
    if(mat[src[y]][tar[x]] || src[y] == tar[x]) {
        v |= can_convert(x-1, y-1); 
    }
    v |= can_convert(x, y-1);
    //printf("dp[%d][%d] = %d\n", x, y, v);
    return dp[x][y] = v;
}

int main() {
    int t;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", tar, src);
        n = strlen(tar);
        m = strlen(src);
        memset(mat, 0, sizeof(mat));
        
        scanf("%d", &k);
        while(k--) {
            char x[10], y[10];
            scanf("%s %s", x, y);
            mat[x[0]][y[0]] = 1;
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                dp[i][j] = -1;
            }
        }
        dp[n-1][m-1] = can_convert(n-1, m-1);
        printf("Case #%d: %shappy\n", cases++, dp[n-1][m-1]?"":"un");
    }
    return 0;
} 
