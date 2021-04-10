#include <iostream>
#include <cstring>
using namespace std;

#define maxn 1010
#define inf -1
int a[maxn][maxn], dp[maxn][maxn];

int Min(int x, int y) {
	if(x == inf) {
		return y;
	}
	if(y == inf) {
		return x;
	}
	return x < y ? x : y;
}

int dpval(int r, int c) {
	if(r == 0 && c < 0) {
		return 0;
	}
	if(c == 0 && r < 0) {
		return 0;
	}
	if(r < 0 || c < 0) {
		return inf;
	}
	return dp[r][c];
}


//适用于正整数
template <class T>
inline void scan_d(T &ret) {
	char c; ret=0;
	while((c=getchar())<'0'||c>'9');
	while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
}

int main() {
	int n, m;
	int i, j;
	while(scanf("%d %d", &n, &m) != EOF) {
		for(i = 0; i < n; ++i) {
			for(j = 0; j < m; ++j) {
				scan_d(a[i][j]);
			}
		}
		memset(dp, -1, sizeof(dp));
		for(i = 0; i < n; ++i) {
			for(j = 0; j < m; ++j) {
				if((i+j) & 1) {
					if(i == 0) {
						dp[i][j] = a[i][j] * a[i][j-1] + dpval(i, j-2);
					}else if(j == 0) {
						dp[i][j] = a[i][j] * a[i-1][j] + dpval(i-2, j);
					}else {
						int &p = dp[i][j];
						
						int dp02 = dpval(i, j-2);
						int dp11 = dpval(i-1, j-1);
						int dp20 = dpval(i-2, j);
						
						if(dp02 != inf) {
							p = Min(p, dp02 + a[i][j] * a[i][j-1]);
						}
						if(dp20 != inf) {
							p = Min(p, dp20 + a[i][j] * a[i-1][j]);
						}
						if(dp11 != inf) {
							p = Min(p, dp11 + a[i][j] * a[i-1][j]);
							p = Min(p, dp11 + a[i][j] * a[i][j-1]);
						}
					}
				}
			}
		}
		printf("%d\n", dp[n-1][m-1]);
		
	}
	
	
	return 0;
} 
