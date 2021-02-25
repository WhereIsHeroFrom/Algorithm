#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 多重背包 模板 ************************************
const int MAXN = 200100;          // 物品数量 
const int MAXC = 1010;            // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

struct MultiKnapsack : public Knapsack {
    int count;
    MultiKnapsack() {
    }
    MultiKnapsack(int cnt, int cap, ValueType w) : count(cnt) {
        capacity = cap;
        weight = w;
    }
}MKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
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
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

void multiKnapsack(int knapsackSize, MultiKnapsack *mknap, Knapsack *knap, int maxCapacity) {
    int nknapSize = 0;
    for (int i = 0; i < knapsackSize; ++i) {
        int cnt = mknap[i].count;
        int cap = mknap[i].capacity;
        int val = mknap[i].weight;
        int k = 1;
        // 二进制拆分 
        while (cnt) {
            if (k > cnt) {
                k = cnt;
            }
            knap[nknapSize++] = Knapsack(cap*k, val*k);
            cnt -= k;
            k <<= 1;
        }
    }
    zeroOneKnapsack(nknapSize, knap, maxCapacity);
}

//************************************ 多重背包 模板 ************************************

char s[20], e[20];
int n;

int main() {
    while (scanf("%s %s %d", s, e, &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            int t, c, p;
            scanf("%d %d %d", &t, &c, &p);
            if (p == 0) {
                p = 1000;
            }
            MKnap[i] = MultiKnapsack(p, t, c);
        }
        int sh, sm, start, end;
        sscanf(s, "%d:%d", &sh, &sm);
        start = sh * 60 + sm;
        sscanf(e, "%d:%d", &sh, &sm);
        end = sh * 60 + sm;
        int cap = end - start;
        if (cap < 0) cap = 0;
        multiKnapsack(n, MKnap, Knap, cap);
        int ans = inf;
        for (int i = 0; i <= cap; ++i) {
            ans = opt(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}