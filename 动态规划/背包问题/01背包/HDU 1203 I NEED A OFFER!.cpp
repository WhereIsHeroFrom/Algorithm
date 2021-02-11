/*
	题意：有 m (m <= 10000) 个学校， 第i个学校需要一笔费用 w[i]，并且获得offer的概率 p[i]；
	问在有 n (n <= 10000)万美元的预算的情况下，至少收到一封 offer 的最大概率是多少；
	
	题解：0/1 背包
	转换求成一封 offer 都收不到的最小概率，然后再用 1 去减就是答案了;
	背包的概率相乘转换成取对数后的概率相加，然后就是求 0/1 背包的价值最小值了；
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 10010;           // 物品数量 
const int MAXC = 10010;           // 背包容量 
typedef double ValueType;         // 背包价值的类型 
const ValueType inf = 10000000;   // 求最大值则最小，求最小值则最大 
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
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01背包 模板 ************************************

int main() {
	int n, m;
	
	while(scanf("%d %d", &n, &m) != EOF && (n||m)) {
		for(int i = 0; i < m; ++i) {
			int c;
			double p;
			scanf("%d %lf", &c, &p);
			Knap[i] = Knapsack(c, log10(1 - p));
		}
		zeroOneKnapsack(m, Knap, n);
		double ans = 0;
		for(int i = 0; i <= n; ++i) {
			double now = 100 - 100 * pow(10, dp[i]);
			if(now > ans) ans = now;
		}
		printf("%.1lf%%\n", ans);
	} 
	
	return 0;
}
