/*
斜率优化的DP 
  题意：给定N(N <= 400000)个数a[N]，现在需要将它们归类，每类至少T(1 < T <= N)个数。归在
  同一类的花费为每个数字减去最小那个数字之和。希望所有数归类后的总花费最小，求这个最小花费。
  题解：dp[i] = {dp[j] + sum[i]-sum[j] - (i-j)a[j+1] | 0<=j<i}
        
        b = dp[i] - sum[i]
        y = dp[j] - sum[j] + j*a[j+1]
        k = i
        x = a[j+1]
        y = kx + b
        单调队列维护 “下凸” 折线，单调队列内存储的点为可转移到状态i的状态j。
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 1010
#define LL int
int n, m;
int a[MAXN], b[MAXN];
int sa[MAXN], sb[MAXN];
int dpIdx;
LL dp[MAXN][MAXN];

// 自变量x，和决策k相关 
LL X(int k) {
    return sa[k];
}

// 应变量y，和决策k以及上一层状态相关 
LL Y(int k) {
    return sb[k] + dp[dpIdx-1][k];
}

// 斜率K，只取决于j，且单调递增 
LL K(int j) {
    return sa[j];
}

// y = Kx + b，其中b = dp[i][j] + B; 
// y = Kx + dp[i][j] + B
LL B(int j) {
    return sb[j-1] - sa[j-1]*sa[j];
}

// 于是 dp[i][j] =  y - Kx - B

// 斜率判定：K(A, B) >= K(B, C)
bool isBigger(int A, int B, int C) {
    // K(A, B) = (Y(B)-Y(A)) / (X(B)-X(A))
    // K(C, B) = (Y(C)-Y(B)) / (X(C)-X(B))
    LL XB = X(B);
    LL YB = Y(B);
    return (YB-Y(A))*(X(C)-XB) >= (Y(C)-YB)*(XB-X(A));
}

// 斜率判定：K(A, B) <= slope
bool isSmaller(int A, int B, LL slope) {
    // K(A, B) = (Y(B)-Y(A)) / (X(B)-X(A))
    return (Y(B)-Y(A)) <= slope*(X(B)-X(A));
}

int deq[MAXN];
int head, tail;
#define STATE_INVALID -1

LL solve() {
    int i, j; 
    // 1.定义非法状态
    memset(dp, -1, sizeof(dp));
    // 2.定义初始状态
    dp[0][0] = 0;
    // 3.枚举i，j, 计算dp[i][j]
    // 状态转移如下： dp[i][j] <- dp[i-1][k]
    // i放置在外层，这样可以保证 K(j) 始终单调递增 
     for(i =    1; i <= m; ++i) {
         head = tail = 0;
         dpIdx = i;
         for(j = 1; j <= n; ++j) {
            // 4.如果dp[i-1][j-1]这个状态合法，那么可以加入单调队列
            if(dp[i-1][j-1] != STATE_INVALID) {
                // 4.1 维护“下凸”折线
                while(head + 1 < tail && isBigger(deq[tail-2], deq[tail-1], j-1))
                    --tail;
                // 4.2 插入单调队列尾部
                deq[tail++] = j-1;
            }
            // 5.删除所有“永不录用”点
            while(head + 1 < tail && isSmaller(deq[head], deq[head+1], K(j)))
                ++head;
    
            // 6. 更新y = kx + b
            dp[i][j] = Y(deq[head]) - K(j)*X(deq[head]) - B(j);         
        }
    }
    return dp[m][n];
}

int main() {
    int i;
    while(scanf("%d %d", &n, &m) != EOF) {
        if(!n && !m) {
            break;
        }
        for(i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            sa[i] = sa[i-1] + a[i];
            b[i] = a[i] * sa[i];
            sb[i] = sb[i-1] + b[i];
        }
        ++m;
        printf("%d\n", solve());
    }
    return 0;
}
