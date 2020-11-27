/*
    题意：N个学生，学生i想去的地方为P[i]（0 <= P[i] <= 10^5）, 初始时所有学生都在学校里，由一辆公交车带出来选K个站停靠，停靠点一定是在P[i]里选出来的，有需要的同学下车，为了使所有学生的总距离最小，求这个最小值（K<=N<=3000）。
    题解：决策单调性。
        状态表示：dp[i][j]表示在第i个站点放置第j个位置时的最小耗费
        状态转移：dp[i][j] = min{dp[i'][j-1] + cost(i', i)| i'<i}
        
        cost(i', i)的计算cost(i', i) = sum{ min{ dist(k,i'), dist(k,i) } | i'<k<i}
        那么这是一个2D/1D问题，时间复杂度O(n^3)。

        观察cost(i', i)函数，很容易想到，可以在i'和i之间找到一个k，使得[i', k]之间的点到i'的距离小于到i的距离；[k+1, i]之间的点则正好相反。
        那么k成为一个转折点。

        再来看状态转移方程，dp[i][j] = min{dp[i'][j-1] + cost(i', i)| i'<i} 
        i'称为i的决策，由于问题的特殊性，当i增大，决策i'势必也会同样增大。也就是说决策满足单调性，即：
        当j相同时，当a<b时，有dp[a][j]和dp[b][j]，其中a'为a的决策，b'为b的决策，那么a'<b'。于是在枚举决策的时候，我们可以简化内部的一个O(n)变成O(1)。

        同时dp[i][j]只和dp[i][j-1]有关，所有第二维可以采用滚动数组。

        这题有个坑点，就是坐标为0的玩家不参与计算，需要特殊处理。
*/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 3010
#define MAXV 611111111

int P[MAXN], Sum[MAXN];
int n, k;
int dp[MAXN][2];
int cost[MAXN][MAXN];

void calcSum() {
    int i;
    sort(P+1, P+n+1);
    for(i = 1; i <= n; i++) {
        if(P[i]) {
            break;
        }
    }
    if(i < n+1) {
        int p = i;
        for(i = 1; i+p-1 <= n; i++) {
            P[i] = P[i+p-1];
        }
        n -= (p-1);
    }
    for(i = 1; i <= n; ++i) {
        Sum[i] = Sum[i-1] + P[i];
    }
}

void getCost() {
    int i, j;
    for(i = 1; i <= n; ++i) {
        cost[i][i] = cost[i][i+1] = 0;
        int p = i;
        for(j = i + 2; j <= n; ++j) {
            cost[i][j] = cost[i][j-1] + (j-1-p)*(P[j] - P[j-1]);
            while(p < j) {
                ++p;
                if(2*P[p] < P[i] + P[j]) {
                    cost[i][j] += (P[p] - P[i]) - (P[j] - P[p]);
                }else {
                    --p;
                    break;
                }
            }
            //printf("%d ", cost[i][j]);
        }
        //puts("");
    }
}

int main() {
    int t;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        for(i = 1; i <= n; i++) {
            scanf("%d", &P[i]);
            //P[i] = P[i-1] + i*i%12;
        }

        calcSum();
        if(0 == Sum[n] || k >= n) {
            printf("0\n");
            continue;
        }

        getCost();
        int p = 0;
        for(i = 1; i <= n; i++) {
            dp[i][0] = i*P[i] - Sum[i];
        }
        for(j = 2; j <= k; ++j) {
            int pos = j-1;
            for(i = 2; i <= n; i++) {
                dp[i][p^1] = MAXV;
                for(int ii = pos; ii <= i; ++ii) {
                    int v = dp[ii][p] + cost[ii][i];
                    if(v < dp[i][p^1]) {
                        dp[i][p^1] = v;
                        pos = ii;
                    }
                }
            }
            p ^= 1;
        }
        int ans = INT_MAX;
        for(i = k; i <= n; i++) {
            int v = dp[i][p] + (Sum[n]-Sum[i]) - (n-i)*P[i];
            if(v < ans) ans = v;
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
243
6 2
1 2 4 11 12 14

101
10 3
1 2 4 5 6 8 11 13 18 21

100
3000 198
3000 192
3000 111
3000 134
3000 1111
3000 432
3000 231
700 281
571 123
331 111
999 321
1211 791

35209
36127
63784
52942
2948
11783
30666
585
1004
384
1231
219

*/
