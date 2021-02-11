/*
	题意：给定 n 张发票，每张发票有 x 个价格，如果单价超过 600 不能报销；总价超过 1000 也不能报销；
	问给定一个价格上界，最多能报销多少钱，精确的小数点后 2 位；
	
	题解： 价格乘上100，然后筛选掉不满足条件的 0/1 背包 
*/ 

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 40;              // 物品数量 
const int MAXC = 1000*100*32;     // 背包容量 
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

//************************************ 01背包 模板 ************************************

#define eps 1e-8


int main() {
	double v;
	int intV, i;
	char ch[100];
	int n;
	double g[3];
	while(scanf("%lf %d", &v, &n) != EOF && n) {
		intV = int(v * 100 + eps);
		int tp = 0;
		int needCap;
		while(n--) {
			int k;
			
			scanf("%d", &k);
			
			g[0] = g[1] = g[2] = 0;
			
			double tot = 0;
			double ans;
			bool flag = 1;
			while(k--) {
				scanf("%s", ch);
				char tmp;
				sscanf(ch, "%c:%lf", &tmp, &ans);
				tot += ans;
				if(tot > 1000 + eps) {
					flag = 0;
				}
				if(tmp != 'A' && tmp != 'B' && tmp != 'C') {
					flag = 0;
				}else {
					g[ tmp - 'A' ] += ans;
					if( g[ tmp - 'A' ] > 600 + eps ) {
						flag = 0;
					}
					
				}
			}
			if(flag) {
				int cap = int(tot * 100 + eps);
				Knap[tp++] = Knapsack( cap, 0 );
				needCap += cap;
			}
		}
		if(needCap < intV) intV = needCap;
		
		zeroOneKnapsack(tp, Knap, intV);
		for(i = intV; i >= 0; --i) {
			if(dp[i]) {
				break;
			}
		}
		printf("%d.%02d\n", i/100, i%100);
	}
	
	
	return 0;
}




