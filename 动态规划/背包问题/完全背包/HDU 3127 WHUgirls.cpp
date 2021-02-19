#include <iostream>
#include <cstring>
using namespace std;

struct Rect {
	int x, y, c;
	void read() {
		scanf("%d %d %d", &x, &y, &c);
	}
}R[20];

const int MAXN = 1010;

int X, Y, dp[MAXN][MAXN];
int n;

int Max(int a, int b) {
	return a > b ? a : b;
}
int dfs(int X, int Y) {
	if(dp[X][Y] != -1) {
		return dp[X][Y];
	}
	if(X == 0 || Y == 0) {
		return 0;
	}
	
	int Maxv = 0;
	
	for(int i = 0; i < 2*n; ++i) {
		if(R[i].x <= X && R[i].y <= Y) {
			
			Maxv = Max(Maxv, dfs(R[i].x, Y - R[i].y) + dfs(X - R[i].x, Y) + R[i].c);
			Maxv = Max(Maxv, dfs(X - R[i].x, R[i].y) + dfs(X, Y - R[i].y) + R[i].c);

		}
		
	}	
	
	return dp[X][Y] = Maxv;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d", &n, &X, &Y);
		for(int i = 0; i < n; ++i) {
			R[i].read();
			R[n+i].x = R[i].y;
			R[n+i].y = R[i].x;
			R[n+i].c = R[i].c;
		}
		memset(dp, -1, sizeof(dp));
		dfs(X, Y);
		printf("%d\n", dp[X][Y]);
	}
	return 0;
} 

/*
10

10 1000 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000
1 1 1000

*/
