/*
	裸 0/1 背包 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 3500;              // 物品数量 
const int MAXC = 13000;             // 背包容量 
typedef int ValueType;              // 背包价值的类型 
const ValueType inf = -1000000000;  // 求最大值则最小，求最小值则最大 
const ValueType init = 0;            // 一般无论求最大值还是最小值，都固定为 0 

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

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	int maxC = 0;
	for(int i = 0; i < knapsackSize; ++i) {
		maxC += knap[i].capacity;
		if(maxC > maxCapacity) {
			maxC = maxCapacity;
		}
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
		
		for(int j = 0; j <= maxCapacity; ++j) {
			printf("%d ", dp[j]);
		} 
		puts("");
	}
}

//************************************ 01背包 模板 ************************************

int main() {
	int n, w;
	int i, j;
	int p, k;
	
	while(scanf("%d %d", &n, &w) != EOF) {
		for(i = 0; i < n; ++i) {
			int c, w;
			scanf("%d %d", &c, &w);
			Knap[i] = Knapsack(c, w);
		}
		zeroOneKnapsack(n, Knap, w);
		int Max = 0;
		for(i = 0; i <= w; ++i) {
			Max = opt(dp[i], Max);
		}
		printf("%d\n", Max);
	} 
	
	return 0; 
} 

/*
4 7
2 2
4 3
1 1
2 5

*/





