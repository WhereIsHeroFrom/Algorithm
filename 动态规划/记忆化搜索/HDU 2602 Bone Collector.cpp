/*
	 题意：裸 01 背包
	 
*/ 

#include <iostream>
#include <cstring>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 1010;      // 物品数量 
const int MAXC = 1010;      // 背包容量 
const int inf = -100000000; // dp数组的非法值 
const int init = 0;         // dp数组的初始值 
typedef int ValueType;

ValueType dp[MAXN][MAXC];

struct Knapsack {
	int capacity;
	ValueType weight;
public:
	Knapsack(){} 
	Knapsack(int c, ValueType w) : capacity(c), weight(w) {}
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
	return x > y ? x : y;
}

int dfs(int n, int vol) {
	if(vol < 0) {
		return inf;
	}
	if(n == 0) {
		return 0;
	}
	ValueType &val = dp[n][vol];
	if(val != -1) {
		return val;
	}
	return val = opt( 
		dfs(n-1, vol), 
		dfs(n-1, vol - Knap[n].capacity) + Knap[n].weight 
	);
}

//************************************ 01背包 模板 ************************************


int main() {
	int n, v, i;
	int t;
	scanf("%d", &t);
	while( t-- ) {
		scanf("%d %d", &n, &v);
		int tot = 0;
		for(i = 1; i <= n; ++i) {
			int w;
			scanf("%d", &w);
			Knap[i].weight = w;
		}
		for(i = 1; i <= n; ++i) {
			int c;
			scanf("%d", &c);
			Knap[i].capacity = c;
		}
		memset(dp, -1, sizeof(dp));
		printf("%d\n", dfs(n, v) );
	}	
	return 0;
}
