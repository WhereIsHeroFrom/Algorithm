/*
    dp[i][j] 表示两端分别为a[i]和a[j]的最大回文长度
        如果a[i] != a[j]，则dp[i][j] = INVALID;
           否则， dp[i][j] = max{ 2 + dp[x][k] | i<x<j, k = ext[x][j-1] }  
        其中 ext[i][j] 表示a[i:j]中，和a[i]相等的最大小标
*/
#include <iostream> 
#include <cstring>

using namespace std;

#define MAXN 210
#define inf -1000000
 
int dp[MAXN][MAXN];
int n, a[MAXN];
int maxLen;

// ext[i][j] 表示a[i:j]中，和a[i]相等的最大小标 
int ext[MAXN][MAXN];

int dfs(int x, int y) {
    if(x == y) {
        return dp[x][y] = 1;
    }
    if(a[x] != a[y]) {
        return dp[x][y] = inf;
    }
    if(dp[x][y] != -1) {
        return dp[x][y];
    }
    if(x + 1 == y) {
        return dp[x][y] = 2;
    }
    
    int i;
    int ans = 2; 
    for(i = x+1; i < y; ++i) {
        if(a[i] <= a[x]) {
            continue;
        }
        int v = dfs(i, ext[i][y-1]);
        if(v+2 > ans) {
            ans = v+2;
        }
    }
    return dp[x][y] = ans;
}

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(i = 0; i < n; ++i) {
            int idx = i;
            for(j = i; j < n; j++) {
                if(a[j] == a[i]){
                    idx = j;
                }
                ext[i][j] = idx;
                //printf("%d %d %d\n", i, j, idx);
            }
        }
        maxLen = 1;
        memset(dp, -1, sizeof(dp));
        for(i = 1; i <= n; i++) {
            for(j = 0; j+i-1 < n; j++) {
                dp[j][j+i-1] = dfs(j, j+i-1);
                int &v = dp[j][j+i-1];
                if(v > maxLen) maxLen = v;
            }
        }
        printf("%d\n", maxLen);
    }    
    return 0;
}
