#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 多重背包 模板 ************************************
const int MAXN = 60;              // 物品数量 
const int MAXC = 10010;           // 背包容量 
typedef int ValueType;           // 背包价值的类型 
const ValueType inf = -1e9;       // 求最大值则最小，求最小值则最大 
const ValueType init = 0;         // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXN][MAXC];
int pre[MAXN][MAXC];

struct Knapsack {
	int idx;
	int capacity;
	ValueType weight;
	Knapsack(){
	} 
	Knapsack(int id, int c, ValueType w) : idx(id), capacity(c), weight(w) {
	}
	
	bool operator < (const Knapsack & k) const {
		return capacity < k.capacity;
	}
}Knap[MAXN];

struct MultiKnapsack : public Knapsack {
	int index;
	int count;
	MultiKnapsack() {
	}
	MultiKnapsack(int i, int cnt, int cap, ValueType w): index(i), count(cnt) {
		capacity = cap;
		weight = w;
	}
}MKnap[MAXN];

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[0][i] = (!i) ? init : inf;
		pre[0][i] = -1;
	}
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);

	for(int i = 1; i <= knapsackSize; ++i) {
		for(int j = 0; j <= maxCapacity; ++j) {
			dp[i][j] = dp[i-1][j];
			pre[i][j] = MAXC * (i-1) + j;
			
			if(j >= knap[i].capacity) {
				int val = dp[i-1][j - knap[i].capacity] + knap[i].weight;
				if(val > dp[i][j]) {
					dp[i][j] = val;
					pre[i][j] = MAXC * (i-1) + j - knap[i].capacity;
				}
			}
		}
	}
}

int multiKnapsack(int knapsackSize, MultiKnapsack *mknap, Knapsack *knap, int maxCapacity) {
	int nknapSize = 0;
	for(int i = 0; i < knapsackSize; ++i) {
		int cnt = mknap[i].count;
		int cap = mknap[i].capacity;
		int val = mknap[i].weight;
		int idx = mknap[i].index;
		int k = 1;
		// 二进制拆分 
		while( cnt ) {
			if(k > cnt) {
				k = cnt;
			}
			knap[++nknapSize] = Knapsack( idx, cap*k, val*k );
			cnt -= k;
			k <<= 1;
		}
	}
	zeroOneKnapsack(nknapSize, knap, maxCapacity);
	return nknapSize;
}

//************************************ 多重背包 模板 ************************************

const int n = 4;
int caps[n] = {1, 5, 10, 25};


int main() {
	int i;
	int ans, cap;
	while( scanf("%d", &cap) != EOF ) {
		ans = cap;
		for( i = 0; i < n; ++i) {
			int cnt;
			scanf("%d", &cnt);
			MKnap[i] = MultiKnapsack(i, cnt, caps[i], 1);
			ans += cnt;
		}
		if(!ans) break;

		int nSize = multiKnapsack(n, MKnap, Knap, cap);
		if( dp[nSize][cap] < 0 ) {
			printf("Charlie cannot buy coffee.\n");
		}else {
			//printf("%d\n", dp[nSize][cap]);
			int now[n] = {0, 0, 0, 0};
			int i = nSize, j = cap;
			while(1) {
				int pi = pre[i][j] / MAXC;
				int pj = pre[i][j] % MAXC;
				if(j != pj) {
					int idx = Knap[i].idx;
					now[idx] += Knap[i].weight;
				} 
				i = pi;
				j = pj;
				if(i == 0) break;
			}
			printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",
			now[0], now[1], now[2], now[3]);	
		}
		
	}
	
	return 0;
} 

/*
1 5 10 25

10000 6 0 0 0
*/


