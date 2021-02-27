#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 树上分组背包 模板 ************************************
const int MAXN = 110;             // 物品数量 
const int MAXC = 110;             // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

vector <int> edges[MAXN];

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    int maxCapacity = m - Knap[u].capacity;            // 1、需要计算的最大容量
    for (i = 0; i <= maxCapacity; ++i)                 // 2、分组背包容量初始化
        dp[u][i] = 0;
    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3、分组背包枚举组（1个子树1个组）
        int v = edges[u][idx];
        if (v == father) continue;                     // 4、无向树的处理
        treeGroupKnapsack(u, v, maxCapacity);          // 5、递归求解子结点所有组的状态 dp[v][0 ... capacity]
        for (i = maxCapacity; i >= 0; --i) {           // 6、分组背包逆序枚举容量
            for (j = 0; j <= i; ++j) {                 // 7、(容量为k, 价值为dp[v][k]) 的物品进行决策
                dp[u][i] = opt(
                    dp[u][i],
                    dp[u][i - j] + dp[v][j]);
            }
        }
    }
    for (i = m; i >= Knap[u].capacity; --i)            // 8、父结点必选
        dp[u][i] = dp[u][i - Knap[u].capacity] + Knap[u].weight;
    for (i = 0; i < Knap[u].capacity; ++i)
        dp[u][i] = 0;
}

//************************************ 树上分组背包 模板 ************************************

int main() {
    int n, m;
    int i;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (i = 1; i <= n; ++i) edges[i].clear();
        int root;
        for (i = 1; i <= n; ++i) {
            int cap, val, fat;
            scanf("%d %d %d", &cap, &val, &fat);
            Knap[i] = Knapsack(cap, val);
            if (fat == -1) {
                root = i;
            }
            else {
                edges[fat].push_back(i);
            }
        }
        treeGroupKnapsack(0, root, m);
        printf("%d\n", dp[root][m]);
    }

    return 0;
}

/*
5 0
10 10
10 10
10 20
1 30
1 35
1 2
1 3
2 4
2 5

10 10
3 4 9
1 3 3
4 5 7
5 9 1
4 4 10
2 3 1
2 6 1
2 1 1
2 1 -1
4 6 2
*/