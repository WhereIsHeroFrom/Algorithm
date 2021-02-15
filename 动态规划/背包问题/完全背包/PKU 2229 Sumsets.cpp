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
const int MAXN = 30;              // 物品数量 
const int MAXC = 1000010;         // 背包容量 
typedef int ValueType;            // 背包价值的类型 
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

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] += dp[j - knap[i].capacity];
			if(dp[j] >= 1e9) dp[j] -= 1e9;
		}
	}
}

//************************************ 完全背包 模板 ************************************

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < 30; ++i) {
			Knap[i] = Knapsack(1<<i, 0);
		} 
		zeroOneKnapsack(30, Knap, n);
		printf("%d\n", dp[n]);
	}
	
	return 0;
} 





