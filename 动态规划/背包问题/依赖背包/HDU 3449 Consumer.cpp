#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 55;              // 物品数量 
const int MAXC = 100010;          // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    int relyCapacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, int rc, ValueType w) : groupId(g), capacity(c), relyCapacity(rc), weight(w) {
    }

    bool operator < (const Knapsack& knap) const {
        return groupId < knap.groupId;
    }
}Knap[MAXN];

struct GroupKnapsack {
    int capacity;
    vector <Knapsack> items;
    void clear() {
        items.clear();
    }
    void add(const Knapsack& knap) {
        capacity = knap.relyCapacity;
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
        dp[0][i] = (!i) ? init : inf;
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

int groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int k = 1; k <= groupSize; ++k) {
        int groupCapacity = GKnap[k - 1].capacity;
        for (int j = 0; j <= maxCapacity; ++j) {
            dp[k][j] = inf;
        }
        for (int i = 0, s = GKnap[k - 1].size(); i < s; ++i) {
            const Knapsack &item = GKnap[k - 1].get(i);
            for (int j = maxCapacity; j >= item.capacity; --j) {
                // 1. dp[k-1][j] 第 i 个物品不选的情况
                // 2. dp[k][j - item.capacity] + item.weight 第 i 个物品选，且箱子已经选过了的情况
                // 3. dp[k-1][j - item.capacity - groupCapacity] + item.weight，第 i 个物品选，且箱子还没选过的情况

                if (j - item.capacity - groupCapacity >= 0) {
                    dp[k][j] = opt(dp[k][j], dp[k - 1][j - item.capacity - groupCapacity] + item.weight);
                }
                dp[k][j] = opt(dp[k][j], dp[k][j - item.capacity] + item.weight);
            }
        }
        for (int j = 0; j <= maxCapacity; ++j) {
            if (dp[k][j] < init)
                dp[k][j] = dp[k - 1][j];
        }
    }
    return groupSize;
}

//************************************ 分组背包 模板 ************************************

int main() {
    int n, m;
    int i, j;
    while (scanf("%d %d", &n, &m) != EOF) {
        int tp = 0;
        for (i = 0; i < n; ++i) {
            int p, cnt;
            scanf("%d %d", &p, &cnt);
            for (j = 0; j < cnt; ++j) {
                int cap, val;
                scanf("%d %d", &cap, &val);
                Knap[tp++] = Knapsack(i, cap, p, val);
            }
        }
        int gSize = groupKnapsack(tp, Knap, m);
        int ans = inf;
        for (i = 0; i <= m; ++i) {
            ans = opt(ans, dp[gSize][i]);
        }
        printf("%d\n", ans);
    }

    return 0;
}