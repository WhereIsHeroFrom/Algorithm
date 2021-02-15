/*
	题意：n( n <= 100 ) 种原料， m (m <= 100000) 块钱， 每种原料用 6 个数字描述：
	x (x <= 100)：每个人需要这种原料的数量 
	y (y <= 100)：厨房目前有的数量    
	s1，p1 (s1,p1 <= 100)：小包装的原料数量 + 价格 
	s2，p2 (s2,p2 <= 100)：大包装的原料数量 + 价格
	
	题解：二分答案 + 完全背包
	
	假设邀请 L 个人，某种原料给每个人需要 100 个，厨房没有， 
	那么最大个数就是 100L，
	用最少的价钱买最多原料 ： p1 = 10 -> s1 = 100, 则最多可以买到原料为 100000/p1*s1 = 10^6
	所以邀请人的上限就是  10^6 = 10L， L = 100000 ，再加上 y/x 的最大值，即 10 
	
	二分邀请的人 L ->  [0, 100010]
	对每种原料求出需要的购买足够原料需要的最少价格，如果所有原料价格加起来小于等于 m 则满足要求
	L 增加；否则，L减少； 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 完全背包 模板 ************************************
const int MAXN = 2;               // 物品数量 
const int MAXC = 1100000;         // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType inf = 1e9;        // 求最大值则最小，求最小值则最大 
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

struct Item {
	int x, y, s1, p1, s2, p2;
	void read() {
		scanf("%d %d %d %d %d %d", &x, &y, &s1, &p1, &s2, &p2);
	}
}I[110];

int n, m;

bool fit(int L) {
	int needm = 0; 
	for(int i = 0; i < n; ++i) {
		int need = I[i].x * L - I[i].y;
		
		if(need <= 0) {
			continue;
		}else if( need > 1010000) {
			return false;
		}
		
		Knap[0] = Knapsack(I[i].s1, I[i].p1);
		Knap[1] = Knapsack(I[i].s2, I[i].p2);
		completeKnapsack(2, Knap, need + 210);
		
		int ans = inf;
		for(int j = need; j <= need + 210; ++j) {
			ans = opt(ans, dp[j]);
		}
		needm += ans;
		
		if(needm > m) {
			return false;
		}
	}
	return true;
}

int main() {
	while(scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for(int i = 0; i < n; ++i) {
			I[i].read();
		}
		int l = 0, r = 100100;
		int ans = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(fit(mid)) {
				ans = mid;
				l = mid + 1;
			}else {
				r = mid - 1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
} 

/*
1 100000
100 100 100 10 100 10

1 100000
10 100 100 10 100 10

*/



