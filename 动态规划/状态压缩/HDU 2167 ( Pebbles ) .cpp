#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 16

int mat[MAXN][MAXN];
char str[1000];
int N;

void fillMat(char *str, int idx) {
    int i = 0,  s = 0;
    int n = 0;
    while(str[i]) {
        if(str[i] >= '0' && str[i] <= '9') {
            s = s * 10 + (str[i] - '0');
        }else {
            if(s) {
                mat[idx][n++] = s;
                s = 0;
            }
        }
        ++i;
    }
    if(s) {
        mat[idx][n++] = s;
        s = 0;
    }
    if(!idx) N = n;
}

void output() {
    int i, j;
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            printf("%d ", mat[i][j]);
        }
        puts("");
    }
}

int dp[2][1<<MAXN];
int p, ans;
int row;
#define INF -1
int pre, now;

void dfs(int pres, int nows, int addv, int row, int col) {
    // todo check
    if(col > 1) {
        if(pres & 1) {
            if(pres & 2) {
                return;
            }
            if(nows & 2) {
                return;
            }
        }

        if(nows & 1) {
            if(pres & 2) {
                return;
            }
            if(nows & 2) {
                return;
            }
        }
    }

    if(col == N) {
        if(dp[p][pres] == INF) {
            return;
        }
        if(dp[p][pres] + addv > dp[p^1][nows]) {
            dp[p^1][nows] = dp[p][pres] + addv;
        }
        if(dp[p^1][nows] > ans) {
            ans = dp[p^1][nows];
            pre = pres;
            now = nows;
        }
        return ;
    }
    dfs(pres<<1,     nows<<1, addv, row, col+1);
    dfs(pres<<1|1,   nows<<1, addv, row, col+1);
    dfs(pres<<1,   nows<<1|1, addv + mat[row][col], row, col+1);
}

void output_s(int s) {
    while(s) {
        printf("%d", s&1);
        s >>= 1;
    } 
    puts("");
}

int main() {
    int i, j;

    while(gets(str)) {
        fillMat(str, 0);
        for(i = 1; i < N; ++i) {
            gets(str);
            fillMat(str, i);
        }
        gets(str);
        memset(dp, INF, sizeof(dp));
        dp[0][0] = 0;
        p = 0;
        ans = 0;
        for(i = 0; i < N; i++) {
            for(j = 0; j < (1<<N); ++j) {
                dp[p^1][j] = INF;
            }
            dfs(0, 0, 0, i, 0);
            p ^= 1;
        }
        //output_s(pre), output_s(now);
        printf("%d\n", ans);
    }
    return 0;
}
