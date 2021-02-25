#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ 分组背包 模板 ************************************
const int MAXN = 4010;            // 物品数量 
const int MAXC = 40010;           // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = 0;       // 求最大值则最小，求最小值则最大 
const ValueType init = 1;         // 一般无论求最大值还是最小值，都固定为 0 

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


void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? 1 : 0;
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
    for (int k = 0; k < groupSize; ++k) {
        if (GKnap[k].size() <= 0) continue;
        for (int j = GKnap[k].get(0).weight; j >= 0; --j) {
            for (int i = 0, s = GKnap[k].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k].get(i);
                if (j >= item.capacity)
                    dp[j] |= dp[j - item.capacity];
            }
        }
    }
}

//************************************ 分组背包 模板 ************************************

/*
题意：给定 K 类柱子， 用三元组 (h, a, c) 表示，h 表示高度，a 表示海拔，c 表示个数
要求将这些柱子搭起来，并且每个柱子不能超过它自身的海拔限制；求最高可以搭多高。

题解：对每类柱子生成 c 个物品，每个物品用 (组号，容量，价值) 表示总共就是
sum(c) = 4000 个物品，然后按照海拔进行排序，
相同海拔的按照组号排序，然后就是一个每个组自己的容量上限的分组背包问题了。
*/

struct Items {
    int h, a, c;

    void read() {
        scanf("%d %d %d", &h, &a, &c);
    }
    bool operator < (const Items& I) const  {
        return a < I.a;
    }
}I[410];

int main() {
    int i, j;
    int K;
    while (scanf("%d", &K) != EOF) {
        for (i = 0; i < K; i++) {
            I[i].read();
        }
        sort(I, I + K);
        int tp = 0;
        for (i = 0; i < K; ++i) {
            for (j = 0; j <= I[i].c && j * I[i].h <= I[i].a; ++j) {
                Knap[tp++] = Knapsack(i, j * I[i].h, I[i].a);
            }
        }
        groupKnapsack(tp, Knap, I[K - 1].a);
        for (i = I[K - 1].a; i >= 0; --i) {
            if (dp[i]) break;
        }
        printf("%d\n", i);

    }

    return 0;
}