#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 树上分组背包 模板 ************************************
const int MAXN = 3010;            // 物品数量 
const int MAXC = 3010;            // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = 1e9;       // 求最大值则最小，求最小值则最大 
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
    if (x == inf) return y;
    if (y == inf) return x;
    return x < y ? x : y;
}

vector <int> edges[MAXN];
int ssize[MAXN];
int c[MAXN], w[MAXN];

void calcSon(int father, int u) {
    ssize[u] = 1;
    for (int idx = 0; idx < edges[u].size(); ++idx) {
        int v = edges[u][idx];
        if (v == father) continue;                     // 4、无向树的处理
        calcSon(u, v);
        ssize[u] += ssize[v];
    }
}

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;

    int maxCapacity = m;                               // 1、需要计算的最大容量
    for (i = 0; i <= m; ++i)                           // 2、分组背包容量初始化
        dp[u][i] = inf;
    if (ssize[u] == 1) {
        dp[u][1] = w[u];
    }
    dp[u][0] = 0;

    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3、分组背包枚举组（1个子树1个组）
        int v = edges[u][idx];
        if (v == father) continue;                     // 4、无向树的处理
        treeGroupKnapsack(u, v, maxCapacity);          // 5、递归求解子结点所有组的状态 dp[v][0 ... capacity]

        for (i = ssize[u]; i >= 0; --i) {              // 6、分组背包逆序枚举容量
            for (j = 0; j <= i; ++j) {                 // 7、(容量为k, 价值为dp[v][k]) 的物品进行决策
                dp[u][i] = opt(
                    dp[u][i],
                    dp[u][i - j] + dp[v][j] + Knap[v].weight);
            }
        }
    }
}

//************************************ 树上分组背包 模板 ************************************

int n, m;

int main() {
    int i;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (i = 1; i <= n; ++i) {
            edges[i].clear();
            ssize[i] = 0;
        }
        Knap[1].capacity = 0;
        Knap[1].weight = 0;
        for (i = 0; i < n - m; ++i) {
            int k;
            scanf("%d", &k);
            while (k--) {
                int c, w;
                scanf("%d %d", &c, &w);
                Knap[c].capacity = 0;
                Knap[c].weight = w;
                edges[i + 1].push_back(c);
            }
        }
        for (i = n - m + 1; i <= n; ++i) {
            int wv;
            scanf("%d", &wv);
            w[i] = -wv;
        }
        calcSon(-1, 1);
        treeGroupKnapsack(-1, 1, n);
        int ans = inf;
        for (i = m; i >= 0; --i) {
            if (dp[1][i] <= 0) {
                break;
            }
        }
        printf("%d\n", i);
    }
    return 0;
}