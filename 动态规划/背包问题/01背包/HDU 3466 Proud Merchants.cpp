/*
	题意：给定 n(n <= 500) 个物品，每个物品有个价格 p[i], 价值 v[i]，
	当你的钱少于 q[i] 时就不能买这个物品了， 问给定 M 元，能够买到的最大价值是多少？
	
	题解：
	
	dp[i][j] 表示前i个物品，选择后加起来的价格为j的最大价值；
	
	1) 第 i 个物品选择不买，则 dp[i][j] = dp[i-1][j];
	2) 第 i 个物品选择买，则  dp[i][j] =  dp[i-1][j-p[i]] + v[i]   |  (j >= q[i])  
	
	
	
	2 2
	1 2 5
	1 1 6
	这样一组数据，用 优化后的 01 背包求出来的状态关系图为；
	0 inf inf
	0   6 inf 
    
    而下面的数据
	2 2
	1 1 5
	1 2 6 
	0 5 inf
	0 5 11 
*/ 
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 510;             // 物品数量 
const int MAXC = 5010;            // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -10000000;  // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

struct Knapsack {
	int capacity;
	int maxcap;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int c, int mc, ValueType w) : capacity(c), maxcap(mc), weight(w) {
	}
	
	bool operator < (const Knapsack& k) const {
		return maxcap-capacity < k.maxcap - k.capacity;
	} 
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = init;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].maxcap; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
		
		/*for(int j = 0; j <= maxCapacity; ++j) {
			printf("%d ", dp[j]);
		}
		puts("");*/ 
	}
}

//************************************ 01背包 模板 ************************************


int main() {
	int n, m; 
	while(scanf("%d %d", &n, &m) != EOF) {
		for(int i = 0; i < n; ++i) {
			int c, mc, v;
			scanf("%d %d %d", &c, &mc, &v);
			Knap[i] = Knapsack(c, mc, v);
		}
		sort(Knap, Knap + n);
		zeroOneKnapsack(n, Knap, m);
		printf("%d\n", dp[m]);
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


