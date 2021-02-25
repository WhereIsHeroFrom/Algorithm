#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 5010;            // 物品数量 
const int MAXC = 50010;           // 背包容量 
typedef bool ValueType;            // 背包价值的类型 
const ValueType inf = 0;          // 求最大值则最小，求最小值则最大 
const ValueType init = 1;         // 一般无论求最大值还是最小值，都固定为 0 

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
    return x || y;
}

void zeroOneKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    }
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    zeroOneKnapsackInit(maxCapacity);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = maxCapacity; j >= knap[i].capacity; --j) {
            dp[j] |= dp[j - knap[i].capacity];
        }
    }
}

//************************************ 01背包 模板 ************************************

int main() {
    int C, H;
    while (scanf("%d %d", &C, &H) != EOF) {
        for (int i = 0; i < H; ++i) {
            int a;
            scanf("%d", &a);
            Knap[i] = Knapsack(a, 0);
        }
        zeroOneKnapsack(H, Knap, C);
        int ans;
        for (int i = C; i >= 0; --i) {
            if (dp[i]) {
                ans = i;
                break;
            }
        }
        printf("%d\n");
    }
    return 0;
}