#include <iostream>

using namespace std;

#define MAXN 510

char mat[MAXN][MAXN];
char mattmp[MAXN][MAXN];
int dp[MAXN][MAXN];
int N, M;

int Min(int a, int b) {
    return a < b ? a : b;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

bool isDiff(int r1, int c1, int r2, int c2) {
    if(r1 == N || r2 == N) return true;
    if(c1 == M || c2 == M) return true;
    return (mat[r1][c1] != mat[r2][c2]);
}

int solve() {
    int i, j, k;
    int ans = 0;
    for(i = N-1; i >= 0; i--) {
        for(j = M-1; j >= 0; j--) {
            if(i == N-1 || j == M-1) {
                dp[i][j] = 1;
            }else {
                int maxk = dp[i+1][j+1] + 1;
                for(k = 1; k <= maxk + 1; k++) {
                    if( isDiff(i,j+k, i+k, j) ) {
                        break;
                    }
                }
                dp[i][j] = Min(k - 1, maxk) + 1;
            }

            ans = Max(dp[i][j], ans);
        }
    }        
    /*for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            printf("%d", dp[i][j]);
        }
        puts("");
    }*/
    return ans;
}

void rotate() {
    int i, j;
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            mattmp[i][j] = mat[N-1-j][i];
        }
    }
    int tmp = N; N = M; M = tmp;
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            mat[i][j] = mattmp[i][j];
            //printf("%c", mat[i][j]);
        }
        //puts("");
    }
    //puts("");
}

int main() {
    int T, i;
    scanf("%d", &T);
    while( T-- ) {
        scanf("%d %d", &N, &M);
        for(i = 0; i < N; i++) {
            scanf("%s", mat[i]);
        }
        int ans = 0;
        for(i = 0; i < 4; i++) {
            ans = Max(ans, solve());
            rotate();
        }
        printf( "%d\n", ans * (ans + 1) / 2 );

    }
    return 0;
}

/*
10
4 4 
abab 
dacb 
adab 
cabb

10
3 4
abcd
efgh
ckal
*/
[ Copy to Clipboard ]    [ Save to File]

