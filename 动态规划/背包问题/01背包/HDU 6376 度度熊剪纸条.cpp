/*
	题意：一个长度为 n (n <= 10000) 的 01 串，要求切 K 刀以后重新组合；
	问重组后的最大前缀1的长度。
	
	题解：
	切出来的串有以下四种情况：
	1、11111  最好的情况，权值为5的贡献； 
	2、11100  可以作为结尾串，权值为3的贡献；
	3、01111  零贡献，垃圾；
	4、00000  零贡献，垃圾；
	
	不考虑 K 的情况的切割方案：
	00 | 1 | 000 | 1 | 0 | 11111 | 0 | 11111 | 000
	考虑以下几种情况： 
	
	1）前后都是 0；        0001110101001000 
	每一段1都需要2刀才能切割出来，则对所有的1按照个数从大到小排序
	取前 (K+1)/2 个对 1的数量 加和就是答案了。
	
	2）前0，后1：          0001110101010001
	除了最后一段只需要1刀切割出来，其它的所有都需要2刀才能切割出来；
	再分情况：
	   1. 最后一段选择：K--， 回归情况 1）； 
	   2. 最后一段不选；回归情况 1）； 
	
	3）前1，后0：          1001110101010000
	除了第一段只需要1刀切割出来，其它的所有都需要2刀才能切割出来；
	再分情况：
		1. 第一段选：K--；
			1.a 第一段放最后，紧邻第一段的权值为1，其它都为2，进行 01背包；
			1.b 第一段放中间，回归情况 1）； 
		2. 第一段不选：回归情况 1）； 
	
	4）前1，后1：          1001110101010001
	除了第一段和最后一段只需要1刀切割出来，其它的所有都需要2刀才能切割出来；
	再分情况：
	    1. 第一段选：K--；
			1.a 第一段放最后，紧邻第一段权值为 1， 其它都为2，进行 01 背包；
			1.b 第一段放中间，从第一个0开始按照 2）情况来算； 
		2. 第一段不选：从第一个0开始按照 2）情况来算； 
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;


//************************************ 01背包 模板 ************************************
const int MAXN = 10010;             // 物品数量 
const int MAXC = 10010;             // 背包容量 
typedef int ValueType;              // 背包价值的类型 
const ValueType inf = -100000000;   // 求最大值则最小，求最小值则最大 
const ValueType init = 0;           // 一般无论求最大值还是最小值，都固定为 0 

ValueType dp[MAXC];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }

    bool operator < (const Knapsack& knap) const {
        return weight > knap.weight;
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    }
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    zeroOneKnapsackInit(maxCapacity);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = maxCapacity; j >= knap[i].capacity; --j) {
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

//************************************ 01背包 模板 ************************************


char str[10010];

int getKnapsack(int s, int e, char *str, bool we) {
    int i;
    int cnt = 0;
    int tp = 0;
    for (i = s; i <= e; ++i) {
        if (str[i] == '1') {
            ++cnt;
        }
        else {
        	if(cnt) {
	            Knap[tp] = Knapsack((we&&!tp) ? 1 : 2, cnt);
	            cnt = 0;
	            ++tp;       		
			}

        }
    }
    if (cnt) {
        Knap[tp] = Knapsack(tp == 0 ? 0 : 1, cnt);
        ++tp;
    }
    return tp;
}

int solve(int s, int e, int K, char *str) {
    if (s > e) {
        return inf;
    }
    if (K < 0) {
        return inf;
    }
    if (K == 0) {
    	int start = s, cnt = 0;
		while(start <= e) {
			if(str[start++] == '0') break;
			cnt ++;
		} 
        return cnt;
    }
    int i;

    if (str[s] == '0' && str[e] == '0') {
        // 1）前后都是 0；        0001110101001000 
        // 每一段1都需要2刀才能切割出来，则对所有的1按照个数从大到小排序
        // 取前 (K+1)/2 个对 1的数量 加和就是答案了。

        int tp = getKnapsack(s, e, str, false);

        sort(Knap, Knap + tp);
        int ans = 0;
        int times = (K + 1) / 2;
        for (i = 0; i < tp; ++i) {
            ans += Knap[i].weight;
            if (--times == 0) {
                break;
            }
        }
        return ans;
    }
    else if (str[s] == '0' && str[e] == '1') {
        // 2）前0，后1：          0001110101010001
        // 除了最后一段只需要1刀切割出来，其它的所有都需要2刀才能切割出来；
        // 再分情况：
        //	 1. 最后一段选择：K--， 回归情况 1）； 
        //	 2. 最后一段不选；回归情况 1）； 		
        int cnt = 1;
        while (1) {
            if (str[--e] != '1') {
                break;
            }
            ++cnt;
        }
        return opt(solve(s, e, K - 1, str) + cnt, solve(s, e, K, str));
    }
    else if (str[s] == '1') {
        // 3）前1，后0：          1001110101010000
        // 除了第一段只需要1刀切割出来，其它的所有都需要2刀才能切割出来；
        // 再分情况：
        //1. 第一段选：K--；
        //1.a 第一段放最后，紧邻第一段的权值为1，其它都为2，进行 01背包；
        //1.b 第一段放中间，回归情况 1） 或 2）； 
        //2. 第一段不选：回归情况 1）或 2）； 	
        
        // 3. 把尾部的1切一刀放到头部 
		int ans = 0;
		if(str[e] == '1') {
			int ss = s;
			int ee = e;
			ans = 1;
			while(ss <= ee) {
				if(str[++ss] != '1') {
					break;
				}
				++ans;
			}
			if(ss > ee) {
				return ans;
			}
			++ans;
			while(ee >= ss) {
				if(str[--ee] != '1') {
					break;
				}
				++ans;
			}
		}
		
			
        int cnt = 1;
        while (s <= e) {
            if (str[++s] != '1') {
                break;
            }
            ++cnt;
        }
        ans = opt(ans, cnt + solve(s, e, K - 1, str));  // 1.b
        ans = opt(ans, solve(s, e, K, str));      // 2

        int tp = getKnapsack(s, e, str, true);

        zeroOneKnapsack(tp, Knap, K - 1);
        for (i = 0; i <= K - 1; ++i) {
            if (cnt + dp[i] > ans) 
				ans = cnt + dp[i];	    // 1.a
        }
        return ans;
    }
}


int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) != EOF) {
        scanf("%s", str);
        //for(int i =0; i< n; ++i) str[i] = rand()%2 + '0';
        //str[n] = '\0';
        //puts(str);
		printf("%d\n", solve(0, n - 1, k, str));
    }
    return 0;
}

/*

1111001101
5

11101101
4


10000 2100 10000 30 10000 10 10000 28 10000 119 10000 12 10000 3 10000 6 10000 2100 10000 30 10000 10 10000 28 10000 119 10000 12 10000 3 10000 6 10000 2100 10000 30 10000 10 10000 28 10000 119 10000 12 10000 3 10000 6 10000 2100 10000 30 10000 10 10000 28 10000 119 10000 12 10000 3 10000 6

10 0 10 1 10 2 10 3 10 4 10 5 10 6 10 7 10 8 10 9 8 0 8 1 8 2 8 3 8 4 8 5 8 6 8 7 6 0 6 1 6 2 6 3 6 4 6 5 4 0 4 1 4 2 4 3 2 0 2 1 1 0

16 0
0100110111101110
16 1
0100110111101110
16 2
0100110111101110
16 3
0100110111101110
16 4
0100110111101110
16 5
0100110111101110
16 6
0100110111101110
16 7
0100110111101110
16 8
0100110111101110



15 0
010011011110111
15 1
010011011110111
15 2
010011011110111
15 3
010011011110111
15 4
010011011110111
15 5
010011011110111
15 6
010011011110111



18 0
110100110111101110
18 1
110100110111101110
18 2
110100110111101110
18 3
110100110111101110
18 4
110100110111101110
18 5
110100110111101110
18 6
110100110111101110



20 0
11010011011110111011
20 1
11010011011110111011
20 2
11010011011110111011
20 3
11010011011110111011
20 4
11010011011110111011
20 5
11010011011110111011
20 6
11010011011110111011
20 7
11010011011110111011

10 1
1111111111

10 1
1111101111

10 1
1000011111

14 4
11011101110111


11 3
11011101110
*/
