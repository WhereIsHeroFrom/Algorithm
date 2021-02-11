/*
	题意：一个强盗想要抢劫银行，给出一个被抓概率 P，如果小于这个概率，则认为可以被接受；
	总共 (n <= 100) 家银行，第 i 家银行包含 m[i] 的钱，并且被抓的概率为 p[i]，求在小于给定
	概率 P 的情况下，能够强盗的最多的钱；
	
	题解： 0/1 背包
	把 概率认为是 容量， 钱认为是价值，这样求 0/1 背包存在的个问题就是 容量不是整数，无法进行
	状态映射 和 状态转移。
	所以我们可以反过来思考，将 钱认为是容量，概率认为是价值，这样就变成了求：
	
	要求：至少被抓一次的最小概率 < P
	转换：一次都不被抓的最大概率 >= 1 - P 
	 
	对于某个钱数 x，一次都不被抓的最小概率 >= 1 - P，这个钱 x 就是可以到手的，求最大的 x；  
*/ 


#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 1010;            // 物品数量 
const int MAXC = 10010;           // 背包容量 
typedef double ValueType;         // 背包价值的类型 
const ValueType inf = -10000000;   // 求最大值则最小，求最小值则最大 
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
	return x > y ? x : y;
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

int n, i;
double P;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lf %d", &P, &n);
		int s = 0;
		for( i = 0; i < n; ++i ) {
			double p;
			int cap;
			scanf("%d %lf", &cap, &p);  // 被抓的概率 
			p = log10(1 - p);           // 不被抓的概率 
			Knap[i] = Knapsack(cap, p);
			s += cap;
		}
		zeroOneKnapsack(n, Knap, s);
		for(i = s; i >= 0; --i) {
			double ans = pow(10, dp[i]);
			// printf("%d %lf\n", i, ans);
			if(ans >= 1 - P) {
				break;
			}
		}
		printf("%d\n", i);
	}
	
	return 0;
} 
