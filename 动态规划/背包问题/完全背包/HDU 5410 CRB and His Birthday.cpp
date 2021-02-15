/*
	题意：商店有 N(N <= 1000) 种物品： 
	对于第 i 种物品有三个权值 w[i], a[i], b[i]，
	如果购买 x 个第 i 种物品，花费 w[i]*x, 得到 a[i]*x+b[i] 个糖果 
	问求利用 M (M <= 2000)的花费 ， 最多可以获得多少糖果； 
	 
	题解：完全背包
	
	dp[i][j] 表示 前 i 个物品组成容量为 j 的最大糖果
	 
	dp[i][j] = max( dp[i-1][j],                 // 第 i 种不选 
		dp[i-1][j - w[i]] + a[i] + b[i],        // 第 i 种 选 1 个 
		dp[i-1][j - w[i]*2] + a[i]*2 + b[i],    // 第 i 种 选 2 个
		...
		dp[i-1][j - w[i]*k] + a[i]*k + b[i]     // 第 i 种 选 k 个
	) 
	这样实际复杂度为 O(ijk) 
	
	
	令 xdp[i][j] = max( dp[i-1][j - w[i]*k] + a[i]*k );
	// 表示第 i 种物品选择 k 个时，a[i] 部分糖果的最大值，注意 k 不能等于 0 
	
	
	
	
	
	 
	原式转换成：
		dp[i][j] = max( dp[i-1][j], xdp[i][j] + b[i]); 
	
	问题转换成求 xdp[i][j] 
	这个有点类似完全背包的 选择1个，2个，3个 ... 的情况
	可以利用顺序的一次循环求出
	
    用一个一维数组 xdp[0...M] = dp[i-1][0...M]
    顺序循环求一次完全背包 xdp[0...M]
	然后再 xdp[0...M] += b[i];
	这里的 xdp[0...M] 就是 opt[0...M] 供下一次计算用
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 1010;           // 物品数量 
const int MAXC = 2010;            // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC], xdp[MAXC];

struct Knapsack {
	int capacity;
	ValueType weighta;
	ValueType weightb;
	Knapsack(){
	} 
	Knapsack(int c, ValueType a, ValueType b) : capacity(c), weighta(a), weightb(b) {
	}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

void completeKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
		xdp[i] = inf;
	}
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			xdp[j] = dp[j - knap[i].capacity] + knap[i].weighta;
			xdp[j] = opt(xdp[j], xdp[j - knap[i].capacity] + knap[i].weighta);
		}
		
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], xdp[j] + knap[i].weightb);
		}
	}
}

//************************************ 完全背包 模板 ************************************

int M, N;
 
int main() {
	int t;
	int i, j;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &M, &N);
		int n = 0;
		for(i = 0; i < N; ++i) {
			int w, a, b;
			scanf("%d %d %d", &w, &a, &b);
			Knap[n++] = Knapsack(w, a, b);
		}
		
		completeKnapsack(n, Knap, M);
		
		int ans = inf;
		for(i = 0; i <= M; ++i) {
			ans = opt(ans, dp[i]);
		}
		printf("%d\n", ans);
	} 
	 
	return 0;
} 

/*
10

100 1
10 2 1

1 1
10 10 10

100 2
50 1 1
50 1 1

100 2
10 2 1
20 1 1

*/



