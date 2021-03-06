#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 18
#define LL long long
int n, m;

LL dp[MAXN][1<<MAXN];
int mat[MAXN][MAXN];

LL dfs(int u, int state) {
    LL &v = dp[u][state];
    if(v != -1) {
        return v;
    }
    int nextstate = (state ^ (1<<u));
    if(nextstate == (1<<0)) {
        return mat[u][0];
    }
    v = 0;
    int i;
    for(i = 1; i < n; ++i) {
        if(mat[i][u] && ((1<<i)&nextstate)) {
            v += dfs(i, nextstate);
        }
    }
    return v;
}

int main() {
    int i, j;
    while(scanf("%d %d", &n, &m) != EOF) {
        memset(dp, -1, sizeof(dp));
        for(i = 0; i < n; ++i) {
            for(j = 0; j < n; ++j) {
                mat[i][j] = 0;
            }
        }
        for(i = 0; i < m; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            --a, --b;
            mat[a][b] = mat[b][a] = 1;
        }
        if(n == 1) {
            printf("%d\n", mat[0][0]);
            continue;
        }

        LL ans = 0;
        for(i = 1; i < n; ++i) {
            if(mat[i][0]) {
                ans += dfs(i, ((1<<n)-1));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
