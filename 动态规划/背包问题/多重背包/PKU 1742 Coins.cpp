#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 多重背包 模板 ************************************
const int MAXN = 3000;            // 物品数量 
const int MAXC = 100010;          // 背包容量 
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
	
	bool operator < (const Knapsack & k) const {
		return capacity < k.capacity;
	}
}Knap[MAXN];

struct MultiKnapsack : public Knapsack {
	int count;
	MultiKnapsack() {
	}
	MultiKnapsack(int cnt, int cap, ValueType w): count(cnt) {
		capacity = cap;
		weight = w;
	}
}MKnap[MAXN];

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	int s = 0; 
	sort(knap, knap + knapsackSize);
	
	for(int i = 0; i < knapsackSize; ++i) {
		s += knap[i].capacity;
		if(s > maxCapacity) {
			s = maxCapacity;
		}
		for(int j = s; j >= knap[i].capacity; --j) {
			dp[j] |= dp[j - knap[i].capacity];
		}
	}
}

void multiKnapsack(int knapsackSize, MultiKnapsack *mknap, Knapsack *knap, int maxCapacity) {
	int nknapSize = 0;
	for(int i = 0; i < knapsackSize; ++i) {
		int cnt = mknap[i].count;
		int cap = mknap[i].capacity;
		int val = mknap[i].weight;
		int k = 1;
		// 二进制拆分 
		while( cnt ) {
			if(k > cnt) {
				k = cnt;
			}
			knap[nknapSize++] = Knapsack( cap*k, val*k );
			cnt -= k;
			k <<= 1;
		}
	}
	zeroOneKnapsack(nknapSize, knap, maxCapacity);
}

//************************************ 多重背包 模板 ************************************



int main() {
	int i;
	int n, cap;
	while( scanf("%d %d", &n, &cap) != EOF && (n||cap)) {
		
		for( i = 0; i < n; ++i) {
			int capa;
			scanf("%d", &capa);
			MKnap[i].capacity = capa;
			MKnap[i].weight = 0;
		}
		for( i = 0; i < n; ++i) {
			int cnt;
			scanf("%d", &cnt);
			MKnap[i].count = cnt;
		}
		
		multiKnapsack(n, MKnap, Knap, cap);
		int ans = 0;
		for( i = 1; i <= cap; ++i ) if(dp[i]) ++ ans;
		printf("%d\n", ans);
		
	}
	
	return 0;
} 



