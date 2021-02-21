#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 200;             // 物品数量 
const int MAXC = 300;             // 背包容量 
typedef long long ValueType;      // 背包价值的类型 
const ValueType inf = 0;          // 求最大值则最小，求最小值则最大 
const ValueType init = 1;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
	int capacity;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int c, ValueType w) : capacity(c), weight(w) {
	}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x + y;
}

void completeKnapsackInit(int maxCapacity) {
	for(int num = 0; num < MAXN; ++num)
		for(int i = 0; i <= maxCapacity; ++i)
			dp[num][i] = (!num && !i) ? init : inf;
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int num = 1; num < MAXN; ++num)
			for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
				dp[num][j] = opt(dp[num][j], dp[num-1][j - knap[i].capacity] + knap[i].weight);
			}
	}
}

//************************************ 完全背包 模板 ************************************


int a[5] = {1, 5, 10, 25, 50};

int main() {
	int i, n;
	int cas = 0;
	
	for(i = 0; i < 5; ++i) {
		Knap[i] = Knapsack(a[i], 0);
	}
	completeKnapsack(5, Knap, MAXC - 1);
	
	while(scanf("%d", &n) != EOF) {
		if(n < 0) {
			printf("0\n");
			continue;
		}
		long long ans = 0;
		for(i = 0; i <= 100; ++i) ans += dp[i][n]; 
		printf("%lld\n", ans);
	}
	
	return 0;
} 




