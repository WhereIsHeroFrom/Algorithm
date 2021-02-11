/*
	题意：卡上的剩余金额大于或等于5元，就一定可以购买成功（即使购买后卡上余额为负），
	否则无法购买（即使金额足够）。所以大家都希望尽量使卡上的余额最少。
	某天，食堂中有n种菜出售，每种菜可购买一次。已知每种菜的价格以及卡上的余额，
	问最少可使卡上的余额为多少。
	
	
	dp[m] 作为初始状态 为 1
	利用 0/1 背包 进行状态转移

	dp[j] = dp[j] || dp[j + c[i]];
	
	并且只有 j + c[i] >= 5 才能进行状态转移
	 
	 
*/ 
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 1010;            // 物品数量 
const int MAXC = 2010;            // 背包容量 
const int BASE = 45;              // 负数容量的偏移 
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
	
	bool operator < (const Knapsack& k) const {
		return capacity < k.capacity;
	} 
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x || y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = -45; i <= maxCapacity; ++i) {
		dp[i + BASE] = (i == maxCapacity) ? init : inf;
	}
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = -45; j + knap[i].capacity <= maxCapacity; ++j) {
			if(j + knap[i].capacity >= 5)
				dp[j + BASE] = opt(dp[j + BASE], dp[j + knap[i].capacity + BASE] + knap[i].weight);
		}
	}
}

//************************************ 01背包 模板 ************************************


int main() {
	int n, m; 
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 0; i < n; ++i) {
			int v;
			scanf("%d", &v);
			Knap[i] = Knapsack(v, 0);
		}
		scanf("%d", &m);
		sort(Knap, Knap + n);
		zeroOneKnapsack(n, Knap, m);
		int ans = -1;
		for(int j = -45; j <= m; ++j) {
			if(dp[j+BASE]) {
				ans = j;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
/*


2 2
1 2 5
1 1 6
0 -10000000 -9999995
0 6 -9999994
-9999994

2 2
1 1 6
1 2 5
0 6 -9999994
0 6 11
11


2 3
1 2 6
2 2 7
0 -10000000 -9999994 -9999994
0 -10000000 7 -9999993
-9999993

2 3
2 2 7
1 2 6
0 -10000000 7 -9999993
0 -10000000 7 13
13




2 2 
1 2 5
1 1 6

2 2
1 1 6
1 2 5


2 3
1 2 6
2 2 7

2 3
2 2 7
1 2 6


*/


