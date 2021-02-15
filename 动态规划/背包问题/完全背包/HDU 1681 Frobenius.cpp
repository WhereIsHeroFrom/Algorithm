/*
	题意：3种物品，分别价格为 1,2,3，现在给出一个价格 n (n <= 32767);
	问有多少组合方案；
	 
	题解：完全背包
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 4;               // 物品数量 
const int MAXC = 2000010;         // 背包容量 
typedef bool ValueType;           // 背包价值的类型 
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
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 完全背包 模板 ************************************

int main() {
	int t;
	scanf("%d\n", &t);
	while(t--) {
		for(int i = 0; i < 4; ++i) {
			int x;
			scanf("%d", &x);
			Knap[i] = Knapsack(x, 0);
		}
		zeroOneKnapsack(4, Knap, 2000000);
		
		int ans = 0;
		int val = -1;
		for(int i = 1; i <= 2000000; ++i) {
			if(!dp[i] && i <= 1000000) {
				ans ++;
				val = i;
			}
			if( i > 1000000 && !dp[i]) {
				val = -1;
				break;
			}
		}
		printf("%d\n%d\n", ans, val);
		
	}
	
	return 0;
} 





