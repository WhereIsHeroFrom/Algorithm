/*
	题意：给定 n (n <= 500) 种硬币的 价值 p 和 重量 w，用硬币填满一个给定储蓄罐，
	求最少的硬币价值。
	
	题解：完全背包
	硬币可以选 0、1、2、3... 所以是个完全背包问题； 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 510;             // 物品数量 
const int MAXC = 10010;           // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = 1e9;        // 求最大值则最小，求最小值则最大 
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
	return x < y ? x : y;
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
	int t, n;
	int E, F;
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &E, &F);
		F -= E;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			int p, w;
			scanf("%d %d",&p, &w);
			Knap[i] = Knapsack(w, p);
		}
		zeroOneKnapsack(n, Knap, F);
		if(dp[F] > inf/2+10) {
			printf("This is impossible.\n");
		}else {
			printf("The minimum amount of money in the piggy-bank is %d.\n", dp[F]);
		}
	}
	
	return 0;
} 





