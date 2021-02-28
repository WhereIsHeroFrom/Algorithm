#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 树上分组背包 模板 ************************************
const int MAXN = 210;             // 物品数量 
const int MAXC = 210;             // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1;         // 求最大值则最小，求最小值则最大 
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

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    ssize[u] = 1;
    int maxCapacity = m;                               // 1、需要计算的最大容量
    for (i = 1; i <= m; ++i)                           // 2、分组背包容量初始化
        dp[u][i] = inf;
    dp[u][0] = 0;

    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3、分组背包枚举组（1个子树1个组）
        int v = edges[u][idx];
        if (v == father) continue;                     // 4、无向树的处理
        treeGroupKnapsack(u, v, maxCapacity);          // 5、递归求解子结点所有组的状态 dp[v][0 ... capacity]
        ssize[u] += ssize[v];
        for (i = maxCapacity; i >= 0; --i) {           // 6、分组背包逆序枚举容量
            for (j = 0; j <= i; ++j) {                 // 7、(容量为k, 价值为dp[v][k]) 的物品进行决策
                if (dp[u][i - j] == inf || dp[v][j] == inf) continue;
                dp[u][i] = opt(
                    dp[u][i],
                    dp[u][i - j] + dp[v][j]);
            }
        }
    }

    // 最后一步选择，父结点的情况
    int s = ssize[u];
    dp[u][s] = opt(dp[u][s], dp[u][0] + Knap[u].weight);

}

//************************************ 树上分组背包 模板 ************************************

const int MAXL = 110;

char name[50010];
char names[MAXN][MAXL];
char tmpname[MAXN][MAXL];
int namecnt;
int in[MAXN];

int findname(char *name) {
    for (int i = 0; i < namecnt; ++i) {
        if (strcmp(name, names[i]) == 0) {
            return i;
        }
    }
    strcpy(names[namecnt], name);
    return namecnt++;
}

int main() {
    int n, m;
    int i, j;
    while (gets(name)) {
        if (strcmp(name, "#") == 0) {
            break;
        }
        for (i = 0; i < MAXN; ++i) edges[i].clear(), ssize[i] = 0, in[i] = 0;
        namecnt = 0;
        sscanf(name, "%d %d", &n, &m);

        while (n--) {
            gets(name);
            int len = strlen(name);
            int s = 0, now = 0, idx = 0;

            for (i = 0; i <= len; ++i) {
                if (name[i] == ' ' || name[i] == '\0') {
                    if (idx) {
                        tmpname[now++][idx] = '\0';
                        idx = 0;
                    }
                }
                else {
                    tmpname[now][idx++] = name[i];
                }
            }
            int u = findname(tmpname[0]);
            int w;
            sscanf(tmpname[1], "%d", &w);
            Knap[u] = Knapsack(-100000, w);
            for (i = 2; i < now; ++i) {
                int v = findname(tmpname[i]);
                edges[u].push_back(v);
                ++in[v];
            }
        }

        for (i = 0; i < namecnt; ++i) {
            if (!in[i]) {
                edges[namecnt].push_back(i);
            }
        }

        treeGroupKnapsack(-1, namecnt, namecnt);
        int ans = inf;
        for (i = m; i <= namecnt; ++i) {
            ans = opt(ans, dp[namecnt][i]);
        }
        printf("%d\n", ans);
    }

    return 0;
}

/*
9 0
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 1
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 2
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 3
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 9
1 10000000 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000
*/