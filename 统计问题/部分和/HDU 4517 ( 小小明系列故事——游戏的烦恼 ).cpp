#include <iostream>
 
using namespace std;

#define MAXN 2010

int n, m, x, y;
int sum[MAXN][MAXN];
char str[MAXN];
int ans;

void calc(int x, int y, int s) {
    int i, j;
    for(i = x; i <= n; ++i) {
        for(j = y; j <= m; ++j) {
            if(sum[i][j] - sum[i-x][j] - sum[i][j-y] + sum[i-x][j-y] == s) {
                ans ++;
            }
        }
    }
}
int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF) {
        if(!n && !m) break; 
        scanf("%d %d", &x, &y);
        for(i = 1; i <= n; ++i) {
            scanf("%s", &str[1]);
            for(j = 1; j <= m; ++j) {
                sum[i][j] = (str[j]=='*')?1:0;
                sum[i][j] += (sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1]);
            }
        }
        ans = 0; 
        calc(x, y, x*y);
        if(x != y) {
            calc(y, x, x*y); 
        }
        printf("%d\n", ans);
    }    
    return 0;
}
