/*
	题意： n (n <= 40) 类物品，每类物品要购买之前，必须先购买一个盒子，问
	购买得到的最大价值。
	
	题解： 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 50;              // 物品数量 
const int MAXC = 200010;          // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1000000000;// 求最大值则最小，求最小值则最大 
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

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = !i ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity, int base) {
	
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= base + knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - base - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01背包 模板 ************************************

int main() {
	int n, w;
	int i, j;
	int p, k;
	
	while(scanf("%d %d", &n, &w) != EOF) {
		zeroOneKnapsackInit(w);
		for(i = 0; i < n; ++i) {
			
			scanf("%d %d", &p, &k);
			for(j = 0; j < k; ++j) {
				int c, v;
				scanf("%d %d", &c, &v);
				Knap[j] = Knapsack(c, v);
			}
			zeroOneKnapsack(n, Knap, w, p);
		}
		int Max = 0;
		for(i = 0; i <= w; ++i) {
			Max = opt(dp[i], Max);
			if(dp[i] > 0) {
				printf("%d %d\n", i, dp[i]);
			}
		}
		printf("%d\n", Max);
	} 
	
	return 0; 
} 





