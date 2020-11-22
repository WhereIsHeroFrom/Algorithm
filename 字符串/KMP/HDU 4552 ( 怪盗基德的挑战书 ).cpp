/*
题意：
    给定一个长度为L的字符串，它的L个前缀为C[1:1], C[1:2], ..., C[1:L]。第i个前缀（C[1:i]字符串）在原串中出现的次数记为K[i]。求sum{K[i]| 1<=i<=L} % 256。
题解：KMP + DP
    首先利用KMP计算next数组。
    dp[i]表示以第i个元素结尾的子串是“原串前缀”的字符串的个数。
    很明显，如果 next[i] == 0, dp[i] = 0;
            如果 next[i] > 0, dp[i] = dp[next[i]] + 1；
    注：
        这里需要追溯到next[i]的含义：          S[1 : next[i]] == S[i-next[i]+1 : i]     ("==" 代表完全匹配）。 
    令j = next[i], 则next[j]就可以表示如下：   S[1 : next[j]] == S[j-next[j]+1 : j] == S[next[i]-next[j]+1 : next[i]] == S[i-next[j]+1 : i]
    更加通俗的表示：
        当i, j, k, l...满足 j=next[i], k=next[j], l = next[k]...时，
            有 S[i-next[i]+1 : i]
               S[i-next[j]+1 : i]
               S[i-next[k]+1 : i]
               S[i-next[l]+1 : i]...
            均为以i结尾的字符串并且满足是“原串前缀”。
    那么以i结尾的字符串中是原串S的前缀的字符串一定是   S[i-next[i]+1 : i]、S[i-next[next[i]]+1 : i]、S[i-next[next[next[i]]]+1 : i]...
    这就是状态转移方程 dp[i] = dp[next[i]] + 1； 的由来。
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100010
#define MOD 256

int pre[MAXN];
int dp[MAXN];    // dp[i] 表示第i个元素为末尾的子串是前缀的个数
char str[MAXN];

void get_next(char *str, int len) {
    int i, j;
    pre[1] = 0;
    for(i = 2; i <= len; i++) {
        j = pre[i-1];
        while(j > 0 && str[i] != str[j+1] ) j = pre[j];
        if(str[i] == str[j+1]) j++;
        pre[i] = j;
    }
}

int main() {
    int i;
    while(scanf("%s", &str[1]) != EOF) {
        int n = strlen(&str[1]);
        get_next(str, n);
        for(i = 0; i <= n; i++) {
            dp[i] = 0;
        }
        int sum = n % MOD;
        for(i = 1; i <= n; i++) {
            if(pre[i]) {
                dp[i] = (dp[pre[i]] + 1) % MOD;
            }else {
                dp[i] = 0;
            }
            sum = (sum + dp[i]) % MOD;
        }
        printf("%d\n", sum);
    }
    return 0;
}

