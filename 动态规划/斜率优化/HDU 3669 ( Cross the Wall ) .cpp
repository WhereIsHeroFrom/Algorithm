#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define MAXK 110
#define LL __int64
#define STATE_INVALID -1234567

int N, K;

LL dp[MAXN][MAXK];

char str[100];
struct Rect {
    int W, H;
    void read() {
        gets(str);
        int i, v[2];
        int s = 0, tot = 0;
        for(i = 0; str[i]; ++i) {
            if(str[i] >= '0' && str[i] <= '9') {
                s = s * 10 + (str[i] - '0');
            }else {
                if(s) {
                    v[tot++] = s;
                    s = 0;
                }
            }
        }
        if(s) {
            v[tot++] = s;
            s = 0;
        }
        W = v[0];
        H = v[1];
    }
    bool operator<(const Rect& other) {
        if(W == other.W) {
            return H > other.H;
        }
        return W < other.W;
    }
    void print() {
        printf("%d %d\n", W, H);
    }
}R[MAXN];
int tmpN;


LL X(int idx) {
    return - R[idx+1].H;
}

int nowj;
LL Y(int idx) {
    return dp[idx][nowj];
}

LL k(int idx) {
    return R[idx].W;
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

LL solve() {
    int i, j;
    // 1.定义初始状态
    dp[0][0] = 0;
    // 2.定义非法状态
    for(i = 1; i <= N; ++i) {
        dp[i][0] = STATE_INVALID;
    }
    // 3.枚举j, i，计算dp[i][j]
     for(j = 1; j <= K; ++j) {
        // 4.单调队列置空
        head = tail = 0;
        nowj = j-1;
        for(i = 1; i <= N; ++i) {
            // 5.状态是否合法，合法的话加入单调队列
            if(dp[i-1][j-1] != STATE_INVALID) {
                // 5.1 维护“下凸”折线
                while(head + 1 < tail && isBigger(deq[tail-2], deq[tail-1], i-1))
                    --tail;
                // 5.2 插入单调队列尾部
                deq[tail++] = i-1;    
            }

            // 6.删除所有“永不录用”点
            while(head + 1 < tail && isSmaller(deq[head], deq[head+1], k(i)))
                ++head;

            // 7. 更新dp[i][j] = y - kx
            dp[i][j] = Y(deq[head]) - k(i)*X(deq[head]);
            //printf("%d %d, %I64d\n", i, j, dp[i][j]);
        }
    }
    return dp[N][K];
}

int main() {
    int i;
    while(scanf("%d %d", &N, &K) != EOF) {
        getchar();
        for(i = 0; i < N; ++i) {
            R[i].read();
        }
        sort(R, R + N);
        tmpN = 1;
        for(i = 1; i < N; ++i) {
            if(R[i].W == R[tmpN-1].W) {
                continue;
            }
            while(tmpN && R[i].H >= R[tmpN-1].H)
                --tmpN;
            R[ tmpN++ ] = R[i];
        }
        N = tmpN;
        for(i = N; i >= 1; --i) {
            R[i] = R[i-1];
        }
        printf("%I64d\n", solve());
    }
    return 0;
}

/*
10 3
1 9
2 4
3 7
5 6
5 5
6 4 
7 3
8 2
10 2
10 1
*/
