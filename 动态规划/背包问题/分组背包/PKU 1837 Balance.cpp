#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 410;             // 物品数量 
const int MAXC = 15010;           // 背包容量
const int CBASE = 7500;           // 负容量偏移值
typedef long long ValueType;      // 背包价值的类型 
const ValueType inf = 0;          // 求最大值则最小，求最小值则最大 
const ValueType init = 1;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[2][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, ValueType w) : groupId(g), capacity(c),  weight(w) {
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

void groupKnapsackInit(int minCapacity, int maxCapacity) {
    for (int i = minCapacity; i <= maxCapacity; ++i) {
        dp[0][i + CBASE] = (!i) ? init : inf;
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

int groupKnapsack(int knapsackSize, Knapsack *knap, int minCapacity, int maxCapacity) {
    groupKnapsackInit(minCapacity, maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    int last = 0, cur = 1;
    for (int k = 0; k < groupSize; ++k) {
        for (int j = minCapacity; j <= maxCapacity; ++j) {
            dp[cur][j + CBASE] = 0;
            for (int i = 0, s = GKnap[k].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k].get(i);

                if (j - item.capacity < minCapacity) continue;
                if (j - item.capacity > maxCapacity) continue;

                dp[cur][j + CBASE] += dp[last][j - item.capacity + CBASE];
            }
        }
        last ^= 1;
        cur ^= 1;
    }
    return last;
}

//************************************ 分组背包 模板 ************************************

/*
    题意：
    一架天平，C(C <= 20)个钩子，G(G <= 20)个砝码
    每个钩子的范围 -15 ~ 15
    每个砝码的范围 1 ~ 25

    问将每个砝码放上对应的钩子，最后使得天平平衡的方案数

    分组背包

    1）天平平衡条件：  力矩 = 力臂 * 重量   保持两边绝对值相等
    2）每个砝码 * 每个位置 得到一个 力矩（注意有正负），所以对于每个砝码组，有 C 种选择
    3）假设 20 个砝码值均为 25，都放在最边缘，得到最大力矩为 15*20*25 = 7500，负力矩就是 -7500
    所以可以设定一个 7500 的偏移量，背包最大容量设为 15010 （10为容错值）
    4）然后就是对每个砝码组进行最多取1个的分组背包了。
    5) 容量有正负，所以无论顺序还是逆序枚举都有问题，最好的解决办法就是滚动数组
*/

int pos[25], items[25];

int main() {
    int C, G;
    int i, j;
    while (scanf ("%d %d", &C, &G) != EOF) {
        for (i = 0; i < C; ++i) {
            scanf("%d", &pos[i]);
        }
        for (i = 0; i < G; ++i) {
            scanf("%d", &items[i]);
        }
        int tp = 0;
        int minCap = 0, maxCap = 0;
        for (i = 0; i < G; ++i) {
            for (j = 0; j < C; ++j) {
                Knap[tp++] = Knapsack(i, pos[j] * items[i], 0);
            }
            minCap += items[i] * pos[0];
            maxCap += items[i] * pos[C - 1];
        }

        int last = groupKnapsack(tp, Knap, minCap, maxCap);

        ValueType ans = dp[last][0 + CBASE];

        printf("%lld\n", ans);
    }
    return 0;
}

/*
2 8
-15 15
1 2 3 4 5 6 7 8

2 6
-1 1
1 2 3 4 5 6

2 2
-15 15
25 25

2 3
-1 1
1 2 3

2 20
-15 15
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/