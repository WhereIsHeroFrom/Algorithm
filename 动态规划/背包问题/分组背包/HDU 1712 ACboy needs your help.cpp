#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 10010;           // 物品数量 
const int MAXC = 10010;           // 背包容量 
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

int main() {
    int n, m;
    int i, j;
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        int tp = 0;
        for (i = 0; i < n; ++i) {
            for (j = 1; j <= m; ++j) {
                int v;
                scanf("%d", &v);
                Knap[tp++] = Knapsack(i, j, v);
            }
        }
        groupKnapsack(tp, Knap, m);
        int ans = inf;
        for (i = 0; i <= m; ++i) {
            ans = opt(ans, dp[i]);
        }

        printf("%d\n", ans);
    }


    return 0;
}