/*
     题意：总共 n(n <= 1000) 件设备，每件设备有个权值 v(0 < v <= 50)，要求
     把所有设备分成两部分，并且这两部分权值和尽量相等，求最终的分成方案。
     
     题解：01背包
     因为每件设备只有两种选择，所以可以认为 选 和 不选 两种方案，所有选的设备
     的权值和为 X， 那么不选设备的权值和就应该等于 总权值和 - X。
     要求的就是 | 总权值和 - 2X | 尽量小。
     
     令 dp[i][j] 表示选了第 i 件设备后，权值和为 j 的方案是否存在；
     
     dp[i][j] = (dp[i-1][j] || dp[i-1][j - v[i] ]);   (i <= 5000, j <= 250000)
      
     
*/ 

#include <iostream>
#include <cstring>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 5010;     // 物品数量 
const int MAXC = 250010;   // 背包容量 
typedef bool ValueType;

ValueType dp[MAXC];

struct Knapsack {
    int capacity;
    int weight;
    Knapsack(){
    } 
    Knapsack(int c, int w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x || y;
}

void zeroOneKnapsackInit() {
    memset(dp, false, sizeof(dp));
    dp[0] = true;
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap) {
    zeroOneKnapsackInit();
    int maxCapacity = 0;
    for(int i = 0; i < knapsackSize; ++i) {
        maxCapacity += knap[i].capacity;
        for(int j = maxCapacity; j >= knap[i].capacity; --j) {
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

//************************************ 01背包 模板 ************************************




int main() {
    int n, i;
    while(scanf("%d", &n) != EOF && n >= 0) {
        int kp = 0;
        int tot = 0;
        for(i = 0; i < n; ++i) {
            int cap, num;
            scanf("%d %d", &cap, &num);
            for(int j = 0; j < num; ++j) {
                Knap[kp++] = Knapsack(cap, 0);
            }
            tot += cap * num;
        }
        zeroOneKnapsack(kp, Knap);
        int a = 0, b = 0;
        for(i = 0; i * 2 <= tot; ++i) {
            if( dp[tot - i] ) {
                a = i;
                b = tot - i;
                if(a < b) swap(a, b);
            }
        }
        printf("%d %d\n", a, b);
    }
    
    return 0;
}
