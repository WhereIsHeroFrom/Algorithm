/*
	题意：3种物品，分别价格为 150，200，350，现在给出一个价格 n (n <= 10000);
	
	题解：完全背包
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 3;               // 物品数量 
const int MAXC = 10010;           // 背包容量 
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
	Knap[0] = Knapsack(150, 0);
	Knap[1] = Knapsack(200, 0);
	Knap[2] = Knapsack(350, 0);
	zeroOneKnapsack(3, Knap, 10000);
	
	int t, n, ans;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = n; i >= 0; --i) {
			if(dp[i]) {
				ans = n - i;
				break;
			}
		}
		printf("%d\n", ans);
	}

	
	return 0;
} 





