#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 背包 模板 ************************************
const int MAXN = 110;             // 物品数量 
const int MAXC = 110;             // 背包容量
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[2][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, ValueType w) : groupId(g), capacity(c), weight(w) {
    }

    bool operator < (const Knapsack& knap) const {
        return groupId < knap.groupId;
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

ValueType opt(ValueType x, ValueType y, ValueType z) {
    return opt(opt(x, y), z);
}
//************************************ 背包 模板 ************************************

void initKnapsack(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[0][i] = 0;
    }
}

int c[MAXN], g[MAXN];

int main() {
    int n, T;
    int i, j, k;
    while (scanf("%d %d", &n, &T) != EOF) {
        initKnapsack(T);
        int last = 0, cur = 1;
        for (i = 0; i < n; ++i) {
            int m, type;
            scanf("%d %d", &m, &type);
            for (k = 0; k < m; ++k) {
                scanf("%d %d", &c[k], &g[k]);
            }

            if (type == 0) {
                // 至少1个
                for (j = T; j >= 0; --j) {
                    dp[cur][j] = inf;  // 一个物品都不选是不行的
                }
                for (k = 0; k < m; ++k) {
                    for (j = T; j >= 0; --j) {
                        if (j >= c[k]) {
                            // 这个物品选
                            dp[cur][j] = opt(dp[cur][j], dp[cur][j - c[k]] + g[k], dp[last][j - c[k]] + g[k]);
                        }
                    }
                }
                last ^= 1;
                cur ^= 1;
            }
            else if (type == 1) {
                // 至多1个
                for (j = 0; j <= T; ++j) {
                    dp[cur][j] = dp[last][j];
                    for (k = 0; k < m; ++k) {
                        if (j >= c[k]) {
                            // 这个物品选
                            dp[cur][j] = opt(dp[cur][j], dp[last][j - c[k]] + g[k]);
                        }
                    }
                }
                last ^= 1;
                cur ^= 1;
            }
            else if (type == 2) {
                // 0/1 背包
                for (k = 0; k < m; ++k) {
                    for (j = 0; j <= T; ++j) {
                        dp[cur][j] = dp[last][j];  // 这个物品不选
                        if (j >= c[k]) {
                            // 这个物品选
                            dp[cur][j] = opt(dp[cur][j], dp[last][j - c[k]] + g[k]);
                        }
                    }
                    last ^= 1;
                    cur ^= 1;
                }
            }
        }

        if (dp[last][T] < 0) {
            dp[last][T] = -1;
        }
        printf("%d\n", dp[last][T]);
    }

    return 0;
}

/*


第一组数据

3 3

2 1
2 5
3 8

2 0
1 0
2 1

3 2
4 3
2 1
1 1


第二组数据

3 4

2 1
2 5
3 8

2 0
1 1
2 8

3 2
4 4
2 1
1 1

第三组数据

1 1
1 0
2 1

第四组数据

5 3

2 0
1 0
2 1

2 0
2 2
1 1

2 0
3 2
2 1

2 1
1 5
2 8

3 2
3 8
4 9
5 10

*/