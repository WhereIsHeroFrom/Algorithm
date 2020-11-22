#include <iostream>

using namespace std;

#define MAXN 22
#define INF 100000000

int dp[MAXN][MAXN][MAXN][MAXN];
int tot;
int n;
int A[MAXN], B[MAXN];
int sumA[MAXN], sumB[MAXN];

int Min(int a, int b) {
    return a < b ? a : b;
}

int dfs(int la, int ra, int lb, int rb) {
    int &ret = dp[la][ra][lb][rb];
    if( ret != -1 ) {
        return ret;
    }
    int fMin = INF;
    
    if(la <= ra) {
        fMin = Min(fMin, dfs(la+1, ra, lb, rb));
        fMin = Min(fMin, dfs(la, ra-1, lb, rb));
    }
    if(lb <= rb) {
        fMin = Min(fMin, dfs(la, ra, lb+1, rb));
        fMin = Min(fMin, dfs(la, ra, lb, rb-1));
    }
    if(fMin == INF) {
        return ret = 0;
    }
    return ret = (sumA[ra]-sumA[la-1]) + (sumB[rb]-sumB[lb-1]) - fMin;
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d", &n);
        memset(dp, -1, sizeof(dp));
        for(i = 1; i <= n; i++) scanf("%d", &A[i]);
        for(i = 1; i <= n; i++) scanf("%d", &B[i]);
        tot = 0;
        for(i = 1; i <= n; i++) {
            tot += A[i] + B[i];
            sumA[i] = sumA[i-1] + A[i];
            sumB[i] = sumB[i-1] + B[i];
        }
        printf( "%d\n", dfs(1, n, 1, n) );    
    }
    return 0;
}
