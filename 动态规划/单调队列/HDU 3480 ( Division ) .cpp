#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 10010
#define MAXM 5010
#define LL long long
int N, M;
LL a[MAXN];
LL dp[MAXN][2];
int p;

LL X(int k) {
    return a[k+1];
}

LL Y(int k) {
    return dp[k][p] + a[k+1]*a[k+1];
}

LL K(int i) {
    return 2*a[i];
}

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
    for(i = 0; i <= N; ++i) {
        dp[i][0] = dp[i][1] = STATE_INVALID;
    }
    p = 0;
    // 2.定义初始化状态
    dp[0][p] = 0;
    // 3.枚举j
    // 4.枚举i
     for(j = 1; j <= M; ++j) {

        for(int zz = 0; zz <= N; ++zz) 
            dp[zz][p^1] = STATE_INVALID;

        head = tail = 0;
        for(i = 1; i <= N; ++i) {
            // 5.如果dp[i-1][p]这个状态合法，那么可以加入单调队列
            if(dp[i-1][p] != STATE_INVALID) {
                // 5.1 维护“下凸”折线
                while(head + 1 < tail && isBigger(deq[tail-2], deq[tail-1], i-1))
                    --tail;
                // 5.2 插入单调队列尾部
                deq[tail++] = i-1;    
            }

            // 6.删除所有“永不录用”点
            while(head + 1 < tail && isSmaller(deq[head], deq[head+1], K(i)))
                ++head;

            // 7. 更新dp[i] = y - kx + a[i]*a[i]
            if(head != tail)
                dp[i][p^1] = Y(deq[head]) - K(i)*X(deq[head]) + a[i]*a[i];
            //printf("%lld ", dp[i][p^1]);
        }
        //puts("");
        p ^= 1;
    }
    return dp[N][p];
}

int main() {
    int i;
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &N, &M);
        for(i = 1; i <= N; i++) {
            int x;
            scanf("%d", &x);
            a[i] = x;
        }
        sort(a + 1, a + N + 1);
        printf("Case %d: %lld\n", ++cases, solve());
    }
    return 0;
}

/*
11000
12 4
1 2 3 4 5 6 6 7 8 9 10 12

0   1  4 9 16 25 25 36 49 64 81 121
-1  0  1 2 5 8 8 13 18 25 32 50
-1 -1  0 1 2 3 3 6 9 12 17 27
-1 -1 -1 0 1 2 2 3 4 7 10 16

11000
20 5
1 2 3 4 5 6 6 7 8 9 10 11 13 15 16 17 18 19 20 21
*/
