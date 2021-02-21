#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 多重背包 模板 ************************************
const int MAXN = 200;             // 物品数量 
const int MAXC = 1000010;         // 背包容量 
typedef int ValueType;            // 背包价值的类型 
const ValueType mininf = -1e9;    // 求最大值则最小，求最小值则最大 
const ValueType maxinf = 1e9;
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

struct MultiKnapsack : public Knapsack {
	int count;
	MultiKnapsack() {
	}
	MultiKnapsack(int cnt, int cap, ValueType w): count(cnt) {
		capacity = cap;
		weight = w;
	}
}MKnap[MAXN];

ValueType Max(ValueType x, ValueType y) {
	return x > y ? x : y;
}

ValueType Min(ValueType x, ValueType y) {
	return x < y ? x : y;
}


void zeroOneKnapsackInit(int type, int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : (type==0?maxinf:mininf);
	} 
}

void zeroOneKnapsack(int type, int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(type, maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			if(type == 0)
				dp[j] = Min(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
			else
				dp[j] = Max(dp[j], dp[j - knap[i].capacity] + knap[i].weight); 
		}
	}
}

void multiKnapsack(int type, int knapsackSize, MultiKnapsack *mknap, Knapsack *knap, int maxCapacity) {
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
			//printf("[%d, %d]\n", cap*k, val*k);
			cnt -= k;
			k <<= 1;
		}
	}

	zeroOneKnapsack(type, nknapSize, knap, maxCapacity);
}

//************************************ 多重背包 模板 ************************************

int a[5] = {1, 5, 10, 50, 100};
int c[5] = {100, 20, 10, 2, 10000000};
int b[5];

int dfs(int index, int cap, int ans) {
	//printf("%d %d %d\n", index, cap, ans);
	if(cap < 0) {
		return -1;
	}
	if(cap == 0) {
		return ans;
	}
	if(index == 4) {
		if(cap % a[index] == 0) {
			if(cap / a[index] <= b[index]) {
				return ans + cap / a[index];
			}
		}
		return -1;
	}
	int s = Min(b[index], cap / a[index]);
	
	for(int i = s, cnt = 0; i >= 0 && cnt <= c[index]; ++cnt, --i) {
		int nowans = dfs( index+1, cap - i * a[index], ans + i);
		if(nowans != -1) {
			return nowans;
		}
	}
	return -1;
} 

int main() {
	int i;
	int n, cap;
	int t;
	scanf("%d", &t);
	while( t-- ) {
		scanf("%d", &cap);
		
		for( i = 0; i < 5; ++i) {
			int cnt;
			scanf("%d", &b[i]);
			MKnap[i] = MultiKnapsack(b[i], a[i], 1); 
		}
		int min, max;
		
		//multiKnapsack(0, 5, MKnap, Knap, cap);
		//min = dp[cap]; if(min > maxinf/2) min = -1;
		
		int nowcap = cap;
		int minans = 0;
		for(i = 4; i >= 0; --i) {
			if( cap >= b[i] * a[i] ) {
				cap -= b[i] * a[i];
				minans += b[i];
			}else {
				int cnt = cap/a[i];
				cap -= cnt * a[i];
				minans += cnt;
			}
		} 
		if(cap == 0) min = minans;
		else min = -1;
		
		cap = nowcap;
		
		if(min == -1) {
			max = -1;
		}else {
			max = dfs(0, cap, 0);
			
			// multiKnapsack(1, 5, MKnap, Knap, cap);
			// max = dp[cap]; if(max < mininf/2) max = -1;			
		}
		
		printf("%d %d\n", min, max);
		
	}
	
	return 0;
} 

/*
10000
0  10 1000000 1000000 1000000 1000000
99999  10 1000000 1000000 1000000 1000000
999999 1000000 1000000 1000000 1000000 1000000

213 8 0 1 0 2 
13 8 0 1 0 2

*/




