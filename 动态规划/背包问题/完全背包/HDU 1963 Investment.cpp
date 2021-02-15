/*
	题意：用现有的钱，最多 10^6， 买理财产品，最多买 40年，问 40年后最多可以剩下多少钱； 
	注意：每件理财产品的购买价格都是 1000 的倍数；
	 
	题解：完全背包
	因为每件理财产品的价格都是 1000 的倍数，所以可以将理财产品都除上 1000 以后再进行背包； 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 20;              // 物品数量 
const int MAXC = 1000000;         // 背包容量 
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
	int t;
	int s, y;
	int n;
	
	scanf("%d", &t);
	while( t-- ) {
		scanf("%d %d", &s, &y);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			int c, w;
			scanf("%d %d", &c, &w);
			Knap[i] = Knapsack(c / 1000, w);
		}
		while(y--) {
			int v = s / 1000;
			
			completeKnapsack(n, Knap, v);
			
			int ans = inf;
			for(int i = v; i >= 0; --i) {
				ans = opt(ans, dp[i]);
			}
			s += ans;
			//printf("%d\n", ans);
		}
		printf("%d\n", s);
	}
	return 0;
} 





