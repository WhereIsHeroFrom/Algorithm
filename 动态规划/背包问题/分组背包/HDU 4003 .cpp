#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 210;             // 物品数量 
const int MAXC = 40010;           // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

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

struct GroupKnapsack {
    vector <Knapsack> items;
    void clear() {
        items.clear();
    }
    void add(const Knapsack& knap) {
        items.push_back(knap);
    }
    int size() const {
        return items.size();
    }
    int getGroupId() {
        if (size()) {
            return items[0].groupId;
        }
        return -1;
    }
    const Knapsack& get(int idx) const {
        return items[idx];
    }
}GKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    }
}

int groupKnapsackRegroup(int knapsackSize, Knapsack *knap) {
    sort(knap, knap + knapsackSize);
    int groupId = -1;
    for (int i = 0; i < knapsackSize; ++i) {
        if (groupId == -1 || knap[i].groupId != GKnap[groupId].getGroupId())
            GKnap[++groupId].clear();

        GKnap[groupId].add(knap[i]);
    }
    return ++groupId;
}

void groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int i = 0; i < groupSize; ++i) {
        for (int j = maxCapacity; j >= 0; --j) {
            for (int k = 0, s = GKnap[i].size(); k < s; ++k) {
                const Knapsack &item = GKnap[i].get(k);
                if (j >= item.capacity)
                    dp[j] = opt(dp[j], dp[j - item.capacity] + item.weight);
            }
        }
    }
}

//************************************ 分组背包 模板 ************************************

/*
    题意：一个 n(n <= 10000) 个结点的树，从 S 点出发，最多 K 个分身，要求访问完所有结点，求最小耗费；
    耗费发生在边上。

    题解：考虑 K 为 1 的情况，
    dp[u][0] 表示从 u 出发，访问完子树的最小消耗；
    dp[u][1] 表示从 u 出发，访问完子树再回到 u 的最小消耗；

    dp[u][1] = sum( dp[v][1] + 2 * cost(u, v) );
    dp[u][0] = min( x 表示从x下去后不回来了 | dp[u][1] - (dp[x][1] + 2 * cost(u, x)) + dp[x][0] + cost(u, x))
    

    对于叶子结点：  dp[u][0] = dp[u][1] = 0;
*/