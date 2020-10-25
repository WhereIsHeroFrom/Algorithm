// 稀疏状态的双向DP + 滚动数组

// 几个注意点 
// 1. 起始状态 0，终止状态x，可以采用双向广搜，但是广搜是求最短可行解，这里要求所有可行解, 所以采用双向DP；
// 2. 枚举一个长度，然后前向从0开始DP，后向从x开始反向DP；
// 3. 由于 x <= 10^9 的限制，两边的状态数不会超过 10^5 * 2 < 2^18；
// 4. 所有状态都有可能很大，所以采用 hash 来映射状态，状态总数 2^18；
// 5. 能够预处理的都预处理掉，比如最大最小剪枝； 
 // When y's len is S; 
// Y[i] = Power[ digit[i] ][K] - Power[10][S-i] * digit[i];   (1<=i<=S)



#include <iostream>
#include <cstring>
using namespace std;

#define LL __int64
#define MAXL 11
#define MANN 100010

// 哈希的取模数 
const int MAXS = (1<<18)-1;
bool HashKey[MAXS+1];
LL HashValue[MAXS+1];

int HASH(LL v) {
	int hashkey = (v & MAXS);
	while(1) {
		if(!HashKey[hashkey]) {
			HashKey[hashkey] = 1;
			HashValue[hashkey] = v;
			return hashkey;
		}else {
			if(v == HashValue[hashkey]) {
				return hashkey;
			}
			hashkey = (hashkey + 1) & MAXS;
		}
	}
} 



LL Power[11][18];   // Power[i][j] = i^j
int state[2][MAXS+1];
int dp[2][MAXS+1];         // 对应 hashkey 实际数值的方案数； 
LL d[MAXL+1][10];
LL MinD[MAXL+1], MaxD[MAXL+1];
LL SumMinD[2][MAXL+2], SumMaxD[2][MAXL+2];

int Q[2][2*MAXS+1], front[2], tail[2];

void DP(int flag, LL start, int len, int totalStep, int stateIdx, LL sum) {
	int i;
	memset(dp, 0, sizeof(dp));
	int pre = 0;
	dp[0][ HASH(start) ] = 1;
	front[0] = tail[0] = front[1] = tail[1] = 0;
	
	Q[0][ tail[0]++ ] = HASH(start);
	
	for(i = 1; i <= totalStep; ++i) {
		int s = (i==1 && flag==0) ? 1 : 0;  // 如果是正向DP，那么最高位不能为0 
		int checkidx = flag? len-i+1 : i;
		
		for(int j = 0; j < MAXS; ++j) {
			dp[pre^1][j] = 0;
		}
		
		while ( front[pre] < tail[pre] ) {
			int prestate = Q[pre][ front[pre] ++ ];
			LL preval = HashValue[prestate];

			int optidx = flag==0? i: len-i+1;
			if(flag==0) {
				if( preval + SumMinD[0][i] > sum ) continue;
				if( preval + SumMaxD[0][i] < sum ) continue;
			}else {
				if( preval - SumMinD[1][len-i+1] < 0 ) continue;
				if( preval - SumMaxD[1][len-i+1] > 0 ) continue;
			}
				
			//if( preval + SumMaxD[ flag ][ optidx ] < 0 ) continue;

			for( int digit = s; digit <= 9; ++digit ) {
				LL v = preval;
				if(flag==0) v += d[checkidx][digit];
				else v -= d[checkidx][digit];
				
				// while(checkidx == 1 && digit == 0) ;
				
				int nowstate = HASH(v);

				if( !dp[ pre^1 ][ nowstate ] ) {
					Q[pre^1][ tail[pre^1]++ ] = nowstate;
				}
				dp[ pre^1 ][ nowstate ] += dp[pre][prestate];
			} 
		}
		pre ^= 1;
	}
	for(i = 0; i < MAXS; ++i) {
		state[ stateIdx ][i] = dp[pre][i];
	}
} 

int bin_dp(int S, LL sum) {
	memset(HashKey, 0, sizeof(HashKey));
	DP(0, 0, S, (S+1)/2, 0, sum);
	DP(1, sum, S, S - (S+1)/2, 1, sum);
	
	int ans = 0;
	for(int i = 0; i < MAXS; ++i) {
		ans += state[0][i] * state[1][i];
	} 
	return ans;
}

int main () {

	int i, j;
	for( i = 0; i <= 10; ++i ) {
		Power[i][0] = 1;
		for(j = 1; j <= 16; ++j) {
			Power[i][j] = Power[i][j-1] * i;
		}
	}
	int t, cas = 0;
	scanf("%d", &t);
	
	while(t--) {
		int x, K, ans;
		scanf("%d %d", &x, &K);
		ans = 0;
		for( int S = 1; S < MAXL; ++S) {
			for(int y = 1; y <= S; ++y) {
				int ss = (y==1) ? 1 : 0;
				d[y][0] = (LL)-23242343 * (LL)234324324;
				for(int digit = ss; digit <= 9; ++digit) {
					d[y][digit] = Power[digit][K] - Power[10][S-y]*digit;
					if (digit == ss) {
						MinD[y] = MaxD[y] = d[y][digit];
					}else {
						if(d[y][digit] < MinD[y]) MinD[y] = d[y][digit];
						if(d[y][digit] > MaxD[y]) MaxD[y] = d[y][digit];
					}
				}
			}
			SumMinD[0][S+1] = SumMaxD[0][S+1] = 0;
			for(int y = S; y >= 1; --y) {
				SumMinD[0][y] = SumMinD[0][y+1] + MinD[y];
				SumMaxD[0][y] = SumMaxD[0][y+1] + MaxD[y];
			}

			SumMinD[1][0] = SumMaxD[1][0] = 0;
			for(int y = 1; y <= S; ++y) {
				SumMinD[1][y] = SumMinD[1][y-1] + MinD[y];
				
				SumMaxD[1][y] = SumMaxD[1][y-1] + MaxD[y];
			}
			ans += bin_dp(S, x);
		}
		printf("Case #%d: %d\n", ++cas, ans); 
	}	
	return 0;
} 

/*
40
0 9 1 9 2 9 3 9 4 9 5 9 6 9 7 9 8 9 9 9
0 8 1 8 2 8 3 8 4 8 5 8 6 8 7 8 8 8 9 8
0 7 1 7 2 7 3 7 4 7 5 7 6 7 7 7 8 7 9 7
110 9 111 9 112 9 113 9 114 9 115 9 116 9 117 9 118 9 119 9

9: 5 0 0 4 0 0 0 0 0 4
8: 4 4 1 0 1 1 0 0 1 0
7: 6 0 0 3 0 0 3 0 0 9
 : 0 7 0 0 3 0 0 3 0 0



40
0 9 1 9 2 9 3 9 4 9 5 9 6 9 7 9 8 9 9 9 10 9 11 9 12 9 13 9 14 9 15 9 16 9 17 9 18 9 19 9 20 9
0 1 
1 1 
2 1 
3 1 
4 1 
5 1 
6 1 
7 1 
8 1 
9 1 
10 1 
11 1 
12 1 
13 1 
14 1
15 1 
16 1 
17 1 
18 1 
19 1 
20 1

5 0 0 4 0 0 0 0 0 4 0 0 3 0 0 1 0 0 10 0 0 
9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 


40
0 2
1 2
2 2
3 2 
4 2
5 2
6 2
7 2
8 2
9 2
10 2
11 2
12 2
13 2
14 2
15 2
16 2
17 2
18 2
19 2
20 2

1 0 1 2 2 1 3 0 0 2 0 2 1 0 2 0 0 1 2 0 1

100
100000002 9
100000005 9
100000008 9
4 2 2

*/
