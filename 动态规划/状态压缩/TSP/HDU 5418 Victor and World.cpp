/*
	题意：n(n <= 16)个城市，从1号城市出发，访问每个城市至少一次再回到 1号城市的最短路径。
	
	题解：dp[i][j] 代表状态，0 < i < n， 1 <= j < 2^n  
	i 代表当前所在城市
	j 代表已经访问过的城市的位组，例如 (10011)2 代表0、1、4号城市已经被访问过。 
	 
	dp[i][j] = min( k != i | dp[k][j] + w(k,i), dp[k][j ^ (1<<i)]  + w(k,i) );
	
	dp[0][1] = 0 为初始状态
	 
	dp[k][j] + w(k,i)  代表从 k 到 i，并且之前已经来过 i 的最短路径；
	dp[k][ j ^ (1<<i)) ] + w(k, i) 代表从 k 到 i，并且之前还没有来过 i 的最短路径；
	 
*/
#include <iostream>
#include <cstring>
using namespace std;

#define maxn 17
#define inf 1000000000

int dp[maxn][1<<maxn];
int mat[maxn][maxn];
int id[1<<maxn+1];

bool hascity(int v, int state) {
	return (1<<v) & state;
}

int lowbit(int x) {
	return x & -x;
}

int Min(int a, int b) {
	return a < b ? a : b;
}

int dfs(int v, int state) {
	if( !hascity(v, state) ) {
		return inf;
	}	
	if(dp[v][state] != -1) {
		return dp[v][state]; 
	}
	 
	if( v == 0 && state == 1 ) {
		return 0;
	}
	
	dp[v][state] = inf;
	
	int x = state;
	while(x) {
		int k = lowbit(x);
		int u = id[k];
		// u -> v
		
		if( (1<<v) != k ) {
			dp[v][state] = Min( dp[v][state], dfs(u, state) + mat[u][v] );
			dp[v][state] = Min( dp[v][state], dfs(u, ( state ^ (1<<v) ) ) + mat[u][v] );
		}
		
		x ^= k;
	}
	return dp[v][state];
}

int main() {
	int t, i, j, n, m;
	for(i = 0; i < maxn; ++i) {
		id[1<<i] = i;
	}
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				mat[i][j] = (i==j) ? 0 : inf;
			}
		}
		while(m--) {
			int u, v, w;
			
			scanf("%d %d %d", &u, &v, &w);
			--u, --v; 
			if(w < mat[u][v]) {
				mat[u][v] = mat[v][u] = w;
			}
		}
		memset(dp, -1, sizeof(dp));
		printf("%d\n", dfs(0, (1<<n)-1));
	}	
	
	return 0;
} 
