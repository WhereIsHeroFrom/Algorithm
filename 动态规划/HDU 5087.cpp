#include <iostream> 
#include <algorithm>
using namespace std;

#define maxn 1010

int n, a[maxn], b[2*maxn];
int dp[maxn][2];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		
		dp[1][0] = 1;
		dp[1][1] = 0;
		
		for(int i = 2; i <= n; ++i) {
			int bs = 0;
			for(int j = 1; j < i; ++j) {
				if(a[j] < a[i]) {
					b[bs++] = dp[j][0] + 1;
					b[bs++] = dp[j][1] + 1;
					
					if(bs > 2) {
						sort(b, b + bs, greater<int>());
						bs = 2;
					}
				}
			}
			//sort(b, b + bs, greater<int>());
			if(bs == 0) {
				dp[i][0] = 1;
				dp[i][1] = 0;
			}else  {
				dp[i][0] = b[0];
				dp[i][1] = b[1];
			}
		}
		int bs = 0;
		for(int i = 1; i <= n; ++i) {
			b[bs++] = dp[i][0];
			b[bs++] = dp[i][1];
		}
		sort(b, b + bs, greater<int>());
		printf("%d\n", b[1]);
		
	}
	
	return 0;
}
