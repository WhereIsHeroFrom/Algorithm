/*
题意：给定N个数a[i](0 <= a[i] <= 1000)，允许任意组合加和，求任意组合加和排列后第m小的数（N,m<=10000）。
题解：01背包
    dp[i][j]表示前i个数组合加和后值为j的方案数。
    dp[i][j] = dp[i-1][j] + dp[i-1][j-a[i]]; (第i个数 选/不选 的情况之和)
    边界条件是dp[0][0] = 1; (一个数都不取的情况种数为1)
    然后枚举满足 dp[n][j] = sum{ dp[n][k] | 0 <= k <= j} >= m 最小的j就是答案了。

    由于数据量比较大，求解dp[i][j]时第一维i可以采用滚动数组；第二维j可以设定一个可预见的最大值；
*/
#include <iostream>
#include <algorithm> 
#include <set>
using namespace std;

#define MAXN 10010 
#define MAXV 100010
int n, m;
int a[MAXN];
int dp[2][MAXV];

int solve() {
    memset(dp, 0, sizeof(dp));
    int i, j, p = 0;
    int maxv = 0, flag = false;
    dp[0][0] = 1;
    for(i = 0; i < n; i++) {
        if(!flag)
            maxv += a[i];
        
        int sum = 0;
        for(j = 0; j <= maxv; j++) {
            dp[p^1][j] = dp[p][j];
            if (j >= a[i]) {
                dp[p^1][j] += dp[p][j-a[i]];
            }
            if(!flag) {
                sum += dp[p^1][j];
                if(sum > m + 1) {
                    flag = true;
                    maxv = j;
                    break;
                }
            }
        }
        p ^= 1;
    }

    int x = 0;
    dp[p][0] --;
    for(i = 0; i <= maxv; i++) {
        x += dp[p][i];
        if(x >= m) {
            break;
        }
    }

    return i;
}

int main() {
    int i, t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            //a[i] = i+1;
        }
        sort(a, a + n);
        printf("Case #%d: %d\n", ++cases, solve()); 
    }
    return 0;
} 
