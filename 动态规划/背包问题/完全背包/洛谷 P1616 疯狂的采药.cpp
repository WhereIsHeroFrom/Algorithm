#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 10010;            // 物品数量 
const int MAXC = 10000010;         // 背包容量 
typedef long long ValueType;       // 背包价值的类型 
const ValueType inf = -1e9;        // 求最大值则最小，求最小值则最大 
const ValueType init = 0;          // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

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

void completeKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    }
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    completeKnapsackInit(maxCapacity);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = knap[i].capacity; j <= maxCapacity; ++j) {
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

//************************************ 完全背包 模板 ************************************

int main() {
    int cap, n;
    while (scanf("%d %d", &cap, &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            int cap, wei;
            scanf("%d %d", &cap, &wei);
            Knap[i] = Knapsack(cap, wei);
        }
        completeKnapsack(n, Knap, cap);
        int ans = inf;
        for (int i = 0; i <= cap; ++i) {
            ans = opt(ans, dp[i]);
        }
        printf("%lld\n", ans);
    }
}