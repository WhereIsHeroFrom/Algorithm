#include <iostream>
#include <cstring> 
using namespace std;

#define ll long long

/*
    dp[i][j] 第i次进攻结束后获取总分为j分的方案数 
*/
ll dp[21][250];
int a, b, t;

int main() {
    int i, j, k;
    
    while(scanf("%d %d %d", &a, &b, &t) != EOF) {
        t /= 15;
        int cnt = (t+1)/2;
        b += t/2;
        int score = (b + 1) - a;
        if(score < 0) {
            score = 0;
        }
        // 排列组合， cnt次(每次取值1,2,3)后拿到[score, 3*cnt]分的方案数
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for(i = 1; i <= cnt; ++i) {
            for(j = 0; j <= 3*cnt; ++j) {
                dp[i][j] = 0;
                for(k = 1; k <= j && k <= 3; ++k) {
                    dp[i][j] += dp[i-1][j-k];
                }
                //printf("%d %d %lld\n", i, j, dp[i][j]); 
            }
        }
        ll ans = 0;
        for(i = score; i <= 3*cnt; i++) {
            ans += dp[cnt][i];
        }
        printf("%lld\n", ans);
    }
    return 0;
} 
