/*
	题意：升级需要 n(n <= 100) 点经验值， 还剩余 m(m <= 100) 点忍耐度，当忍耐度降到 <= 0 后
	游戏结束，总共有 k (k <= 100) 种怪，每种怪杀掉后得到 a[i] 的经验值，减去 b[i] 的忍耐度； 
	最多再杀 s (s <= 100) 只怪，问能否升级？，并且输出能保留的最大忍耐度。 
	 
	题解：二维完全背包
	
	要求选择小于等于 s 只怪，使得它们的 经验值加和 >= n，并且忍耐度加和 <= m，且尽量小；
	
	则可以把【经验值】看成是【容量】，【忍耐度】看成是【价值】，进行完全背包；
	由于这里怪的数量有限制，需要小于等于s，所以需要增加一个 怪的数量 维度。
	
	dp[i][j][k]  代表 "前i种怪中选择j只怪来杀得到经验值为k的最小消耗忍耐度"
	
	dp[i][j][k] = 
		min( dp[i][j - 1][ k - a[i] ] + b[i],    // 第 i 种怪中选择1，2, 3, 4 ...个来杀 
	                           dp[i-1][j][k],    // 第 i 种怪不选择 
	    )
	    
	转换成  dp[j][k] = min( dp[j-1][k-a[i]] + b[i], dp[j][k]); 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 110;             // 物品数量 
const int MAXC = 1000;            // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = 1e9;        // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

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
	return x < y ? x : y;
}

void completeKnapsackInit(int nCnt, int maxCapacity) {
	for(int i = 0; i <= nCnt; ++i) {
		for(int j = 0; j <= maxCapacity; ++j) {
			dp[i][j] = (!i && !j) ? init : inf;
		}
	}
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int nCnt, int maxCapacity) {
	completeKnapsackInit(nCnt, maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = 1; j <= nCnt; ++j) {
			for(int k = knap[i].capacity; k <= maxCapacity; ++k) {
				dp[j][k] = opt(dp[j][k], dp[j-1][k - knap[i].capacity] + knap[i].weight);
			}
		}

	}
}

//************************************ 完全背包 模板 ************************************

int n, m, k, s;

int main() {
	int i, j;
	while(scanf("%d %d %d %d", &n, &m, &k, &s) != EOF) {
		for(i = 0; i < k; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			Knap[i] = Knapsack(a, b);
		}
		completeKnapsack(k, Knap, s, n + 100);
		int need = inf;
		for(j = 0; j <= s; ++j)
			for(i = n; i <= n + 100; ++i) {
				need = opt(need, dp[j][i]);
			}
		
		if(need > m) {
			need = -1;
		}else {
			need = m - need;
		}
		printf("%d\n", need);
	}
	return 0;
} 





