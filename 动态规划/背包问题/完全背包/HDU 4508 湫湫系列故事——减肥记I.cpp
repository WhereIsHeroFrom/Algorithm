/*
	题意：每组数据以一个整数n开始，表示每天的食物清单有n种食物。 
　　接下来n行，每行两个整数a和b，其中a表示这种食物可以带给湫湫的幸福值（数值越大，越幸福），
	b表示湫湫吃这种食物会吸收的卡路里量。
　　最后是一个整数m，表示湫湫一天吸收的卡路里不能超过m。
	 
	题解：完全背包
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 110;             // 物品数量 
const int MAXC = 100010;          // 背包容量 
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

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void completeKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 完全背包 模板 ************************************

int main() {
	int i;
	int n, m;
	
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; ++i) {
			int c, w;
			scanf("%d %d", &w, &c);
			Knap[i] = Knapsack(c, w);
		}
		scanf("%d", &m);
		completeKnapsack(n, Knap, m);
		int ans = inf;
		for(i = 0; i <= m; ++i) ans = opt(ans, dp[i]);
		printf("%d\n", ans);
	}
	return 0;
} 





