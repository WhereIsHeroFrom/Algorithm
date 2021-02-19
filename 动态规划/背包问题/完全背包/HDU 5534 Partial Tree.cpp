/*
	核心：无向图度数总和 = 边数 * 2，树的度数总和 = 2*n-2
	
	每个度看成是背包的容量，值看成是背包的价值，进行完全背包 
	
	注意背包物品的个数正好为 n 个，所以需要加上一维代表 物品个数  
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 2020;              // 物品数量 
const int MAXC = 4040;              // 背包容量 
typedef int ValueType;              // 背包价值的类型 
const ValueType inf = -1e9;         // 求最大值则最小，求最小值则最大 
const ValueType init = 0;           // 一般无论求最大值还是最小值，都固定为 0 

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
		for(int k = knap[i].capacity; k <= maxCapacity; ++k) {
			dp[k] = opt(dp[k], dp[k - knap[i].capacity] + knap[i].weight);			
		}
	}
}

//************************************ 完全背包 模板 ************************************

int main() {
	int t;
	int n, i, j;
	
	scanf ("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		int d0 = 0;
		for(i = 0; i < n - 1; ++i) {
			int d;
			scanf("%d", &d);
			if(i == 0) {
				d0 = d;
			}
			if(i > 0)
				Knap[i-1] = Knapsack(i, d - d0);
		}
		completeKnapsack(n - 2, Knap, n-2);
		printf("%d\n", dp[n - 2] + n*d0);
		
	} 
	return 0;
} 





