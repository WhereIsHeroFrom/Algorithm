/*
	题意：给定一堆物品，每个物品都有一个价格， 
	要求将这些物品组合起来，不超过某个价格的情况；
	求 能够购买最多物品的数量，以及方案数； 
	
	题解： 
		dp[i][j] = max(dp[i-1][j], dp[i-1][j-c[i]] + 1); 
		方案数用另一个数组记录，根据 dp 数组的状态转移来进行方案的记录 
*/ 

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 40;              // 物品数量 
const int MAXC = 510;             // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -10000000;  // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];
ValueType sel[MAXC];

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
		dp[i] = (!i) ? init : inf;
		sel[i] = (!i) ? 1 : 0;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			
			int x = dp[j];
			int y = dp[j - knap[i].capacity] + knap[i].weight; 
			if(x > y) {
				dp[j] = x;
			}else if(x < y) {
				dp[j] = y;
				sel[j] = sel[ j - knap[i].capacity ];
			}else {
				sel[j] = sel[j] + sel[ j - knap[i].capacity ]; 
			}
		}
	}
}

//************************************ 01背包 模板 ************************************



int main() {
	int t, i;
	int n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; ++i) {
			scanf("%d", &Knap[i].capacity);
			Knap[i].weight = 1;
		}
		zeroOneKnapsack(n, Knap, m);
		int ans, Max = 0;
		for(i = m; i >= 1; --i) {
			if(dp[i] > Max) {
				Max = dp[i];
				ans = sel[i];
			}else if(dp[i] == Max) {
				ans += sel[i];
			}
		}
		if(!Max) {
			printf("Sorry, you can't buy anything.\n");
		}else {
			printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n", ans, Max);
		}
		
	}
	
	return 0;
}




