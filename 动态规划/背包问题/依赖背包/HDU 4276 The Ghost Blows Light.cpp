#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 树上分组背包 模板 ************************************
const int MAXN = 110;             // 物品数量 
const int MAXC = 505;             // 背包容量 
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
int mat[MAXN][MAXN];

void treeGroupKnapsack(int father, int u, int maxCapacity) {
    int i, j, k;
    int cap[2][MAXC], pre = 0;

    for (i = 0; i <= maxCapacity; ++i)              // 1、分组背包容量初始化
        cap[0][i] = 0;
    for (i = 0; i < edges[u].size(); ++i) {         // 2、分组背包枚举组（1个子树1个组）
        int v = edges[u][i];
        if (v == father) continue;
        treeGroupKnapsack(u, v, maxCapacity);      // 3、递归求解子结点所有组的状态 dp[v][0 ... maxCapacity - mat[u][v]]
        for (j = maxCapacity; j >= 0; --j) {       // 4、分组背包逆序枚举容量
            cap[pre ^ 1][j] = cap[pre][j];
            for (k = 0; k <= j - mat[u][v]; ++k) {
                                                    // 5、(容量为k, 价值为dp[v][k]) 的物品进行决策
                                                    // 注意一定要考虑容量为 0 的情况
                cap[pre ^ 1][j] = opt(
                    cap[pre ^ 1][j],
                    cap[pre][j - mat[u][v] - k] + dp[v][k]
                    );
            }
        }
        pre ^= 1;
    }
    for (i = maxCapacity; i >= 0; --i)         // 6、父结点必选
        dp[u][i] = cap[pre][i] + Knap[u].weight;
    
    // 如果某个子结点为 0 的情况，不能走，则打开注释
    // dp[u][0] = 0;
}

//************************************ 树上分组背包 模板 ************************************

int fat[MAXN];

void dfs(int father, int u) {
    int i;
    for (i = 0; i < edges[u].size(); ++i) {
        int v = edges[u][i];
        if (v == father) continue;
        fat[v] = u;
        dfs(u, v);
    }
}

void elimitEdge(int root, int exitn, int& t) {
    fat[root] = 0;
    dfs(fat[root], root);

    while (exitn != root) {
        t -= mat[exitn][fat[exitn]];
        if (t < 0) return;
        mat[exitn][fat[exitn]] = mat[fat[exitn]][exitn] = 0;
        exitn = fat[exitn];
    }
    t >>= 1;
}

int main() {
    int n, t;
    int i;
    while (scanf("%d %d", &n, &t) != EOF) {
        for (i = 1; i <= n; ++i) {
            edges[i].clear();
        }
        for (i = 0; i < n - 1; ++i) {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            mat[x][y] = mat[y][x] = w;
            edges[x].push_back(y);
            edges[y].push_back(x);
        }
        for (i = 1; i <= n; ++i) {
            scanf("%d", &Knap[i].weight);
        }
        elimitEdge(1, n, t);
        if (t < 0) {
            printf("Human beings die in pursuit of wealth, and birds die in pursuit of food!\n");
        }
        else {
            treeGroupKnapsack(0, 1, t);
            printf("%d\n", dp[1][t]);
        }
    }
    return 0;
}

/*
7 500
1 2 1
1 3 2
2 4 2
2 5 1
3 6 2
3 7 2
7 6 7 6 7 6 7

4 0
1 2 0
1 3 0
3 4 0
1 2 3 4

4 0
1 2 0
1 3 0
3 4 1
1 2 3 4

4 0
1 2 0
1 3 1
2 4 0
9 8 7 6

4 5
1 2 1
1 3 1
1 4 1
1 2 3 4

9 7
1 2 1
1 3 1
1 4 1
1 5 2
3 6 1
3 7 1
7 9 1
7 8 1
1 1 1 1 10 1 1 1 1

9 500
1 2 100
1 3 100
1 4 100
1 5 200
3 6 100
3 7 100
7 9 100
7 8 100
1 6 1 7 10 5 1 8 1

9 500
1 2 0
1 3 0
1 4 0
1 5 0
3 6 0
3 7 0
7 9 0
7 8 0
1 6 1 7 10 5 1 8 1
*/
