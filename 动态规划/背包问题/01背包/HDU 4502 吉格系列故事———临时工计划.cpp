/*
	题意：
	1) 一共有m(m <= 100)天的假期，每天的编号从1到m;
	2) 一共有n(n <= 1000)份可以做的工作，每份工作都知道起始时间s，终止时间e和对应的工资c，
	3) 每份工作的起始和终止时间以天为单位(即天数编号)，每份工作必须从起始时间
	做到终止时间才能得到总工资c，且不能存在时间重叠的工作。
	
	比如，第1天起始第2天结束的工作不能和第2天起始，第4天结束的工作一起被选定，
	因为第2天只能在一个地方工作。
　　现在，想知道怎么安排才能在假期的m天内获得最大的工资数。 

	
	题解：有依赖关系的 01 背包 
	某个选了，某几个就不能选 
	
	dp[i][j] 代表前i个工作中截止到时间j的最大工资 
	工作按结束时间排个序 
	
	[ 不是恰好的情况 ]
	if( j >= p[i].e )
		dp[i][j] = max( dp[i-1][j], dp[i-1][p[i].s - 1] + p[i].c);
	注意：  如果不是恰好的情况，那么初始值的设定是不一样的 
	 
*/


#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 1010;              // 物品数量 
const int MAXC = 1010;              // 背包容量 
typedef int ValueType;              // 背包价值的类型 
const ValueType inf = -100000000;   // 求最大值则最小，求最小值则最大 
const ValueType init = 0;           // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

struct Knapsack {
	int start;
	int end;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int s, int e, ValueType w) : start(s), end(e), weight(w) {
	}
	
	bool operator < (const Knapsack& knap) const {
		return end < knap.end;
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
		for(int j = maxCapacity; j >= knap[i].end; --j) {
			dp[j] = opt(dp[j], dp[knap[i].start-1] + knap[i].weight);
		}
	}
}

//************************************ 01背包 模板 ************************************

int main() {
	int t, i;
	int n, m;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &m, &n);
		for(i = 0; i < n; ++i) {
			int s, e, c;
			scanf("%d %d %d", &s, &e, &c);
			Knap[i] = Knapsack(s, e, c);
		}
		sort(Knap, Knap + n);
		zeroOneKnapsack(n, Knap, m);
		
		int Max = 0;
		for(i = 0; i <= m; ++i) {
			// printf("%d %d\n", i, dp[i]);
			if(dp[i] > Max) Max = dp[i];
		}
		printf("%d\n", Max); 
	}
	
	return 0;
}

/*
100
10 3
1 3 3
2 4 3
3 5 34
*/
