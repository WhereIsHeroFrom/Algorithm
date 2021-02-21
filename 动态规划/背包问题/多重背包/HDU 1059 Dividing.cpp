#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 多重背包 模板 ************************************
const int MAXN = 200;             // 物品数量 
const int MAXC = 420010;          // 背包容量 
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

ValueType opt(ValueType x, ValueType y) {
	return x || y;
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


int a[6];
int main() {
	int i;
	int cas = 0;
	while(scanf("%d", &a[0]) != EOF) {
		int s = a[0];
		for(i = 1; i < 6; ++i) {
			scanf("%d", &a[i]);
			s += (i+1) * a[i];
		}
		if(!s) break;
		for(i = 0; i < 6; ++i) {
			MKnap[i] = MultiKnapsack(a[i], i+1, 0);
		}
		printf("Collection #%d:\n", ++cas);
		
		bool ans;
		
		if(s & 1) {
			ans = false;
		}else {
			multiKnapsack(6, MKnap, Knap, s/2);
			ans = dp[s/2];
		}
		
		if(ans) {
			printf("Can be divided.\n");
		}else {
			printf("Can't be divided.\n");
		}
		
		puts("");
	}
	
	return 0;
} 




