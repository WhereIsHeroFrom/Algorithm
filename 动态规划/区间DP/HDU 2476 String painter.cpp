#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int maxn = 110;
const int inf = -1;
const int maxv = 1e9;
const int ALL = 26;

int dp[maxn][maxn][27];
char A[maxn], B[maxn];

void init() {
	memset(dp, inf, sizeof(dp));
}

int cost(char a, char b) {
	return a == b ? 0 : 1;	
}

char getChar(char ch, int c) {
	if(c == ALL) {
		return ch;
	}
	return c + 'a';
}

int dfs(int l, int r, int c) {
	if(l == r) {
		return cost( getChar(A[l], c) , B[l] );
	}
	if(l > r) {
		return 0;
	}
	int &val = dp[l][r][c];
	if(val != inf) {
		return val;
	} 
	val = maxv;
	
	val = min(val, cost( getChar(A[l], c), B[l]) + dfs(l+1, r, c) );
	val = min(val, cost( getChar(A[r], c), B[r]) + dfs(l, r-1, c) );
	if(B[l] == B[r]) {
		char cl = getChar(A[l], c);
		char cr = getChar(A[r], c);
		
		if(cl == cr && cl == B[l]) {
			val = min(val, dfs(l+1, r-1, c) );
		}else {
			val = min(val, 1 + dfs(l+1, r-1, B[l] - 'a') );
		}
		
	}
	for(int k = l; k <= r; ++k) {
		val = min(val,  dfs(l, k, c) + dfs(k+1, r, c) );
	}
	return val;
}

int main() {
	int n;
	while(scanf("%s %s", A, B) != EOF) {
		init();
		printf("%d\n", dfs(0, strlen(A)-1, ALL) );	
	}
	return 0;
} 
