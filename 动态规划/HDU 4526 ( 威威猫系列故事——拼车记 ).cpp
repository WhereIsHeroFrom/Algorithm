/*
    题意：
        N个人(N <= 100)，K(K <= 100)辆出租车； 
        每辆车到达时间T[i]，能够坐的人的是Z[i]; (T[i]<=S, Z[i]<=4)
        每辆车的花费为D，每个人等的时间L等于它的花费； 
         
         求能否在S时间内将所有N个人都载走，求最少花费（租车花费+等待花费）。
        如果不能，输出impossible。
       
    题解：dp[K][N]代表状态。
    dp[i][j] 表示前i辆出租车载了j个人的最小代价。
    
    dp[i][j] = min{ dp[i-1][j], min{ dp[i-1][j-k] + k*T[i] + D | 0<k<=Z[i]}}
*/


#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 110

int N, K, D, S;
int T[MAXN], Z[MAXN];
int dp[MAXN][MAXN];

int main() {
    int t;
    int i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d %d", &N, &K, &D, &S); 
        for(i = 1; i <= K; ++i) {
            scanf("%d %d", &T[i], &Z[i]);
        }
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;
        for(i = 1; i <= K; ++i) {
            for(j = 0; j <= N; ++j) {
                dp[i][j] = dp[i-1][j];
                for(k = 1; k <= Z[i]; k++) {
                    if(j-k < 0) continue;
                    int &prev = dp[i-1][j-k];
                    if(prev == -1) continue;
                    if(prev + k*T[i] + D < dp[i][j] || dp[i][j] == -1) {
                        dp[i][j] = prev + k*T[i] + D;
                    }
                } 
            }
        }
        if(dp[K][N] == -1) {
            printf("impossible\n");
        }else {
            printf("%d\n", dp[K][N]);
        }
        
    }
    return 0;
} 

