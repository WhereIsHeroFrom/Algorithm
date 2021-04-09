#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
#define maxn 155
int dp[maxn][maxn][maxn];
int cc = 0, cas[maxn][maxn][maxn];

char ch[maxn];
int n;
int color[maxn], num[maxn];

void init() {
	memset(cas, -1, sizeof(cas));
}

int dfs(int l, int r, int k) {
	if(l > r) {
		// dp[i][i-1][0] Ò»¶¨ÊÇ true 
		return true;
	}
	if(l == r) {
		return num[r] + k > 1;
	}
	int &val = dp[l][r][k];
	if(cc == cas[l][r][k]) {
		return val;
	}
	cas[l][r][k] = cc;
	val = (num[r] + k > 1) && dfs(l, r-1, 0);
	if(val) {
		return true;
	}
	for(int i = l; i < r; ++i) {
		if(color[i] == color[r]) {
			if( dfs(i+1, r-1, 0) ) {
				val |= dfs(l, i, num[r] + k);
				if(val) {
					return true;
				}	
			}
		}
	}
	return val;
}


int main() {
	init();
	while(scanf("%s", ch) != EOF) {
		cc ++;
		n = 0;
		for(int i = 0; ch[i]; ++i) {
			if(!n) {
				color[n] = ch[i];
				num[n] = 1;
				++n;
			}else if(ch[i] == color[n-1]) {
				++ num[n-1];
			}else {
				color[n] = ch[i];
				num[n] = 1;
				++n;
			}
		}
		//for(int i = 0; i < n; ++i) printf(" [%d,%d] \n", color[i], num[i]);
		printf("%s\n", dfs(0, n-1, 0) ? "solvable" : "unsolvable");
	}
	return 0;
} 
/*
SSSSSSSSSSQQQQQQQQQQQQQQQQQQQQQJQQQQQQQQQQQQQQQQQQQQQQQQQQQJQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAAABABABABABABABABABABABABABABABABABABABABABABABABABABABABA

ABABABABBBABABABAB
*/
