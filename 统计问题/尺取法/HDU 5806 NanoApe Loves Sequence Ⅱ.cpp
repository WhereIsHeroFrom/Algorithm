#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#define ll long long
const int maxn = 200010;
int sum[maxn];

ll solve(int n, int k) {
	int i = 0, j = 0;
	ll ans = 0;
	while(j < n) {
		++j;
		while(sum[j] - sum[i] >= k) {
			ans += n - j + 1;
			++i;
		}
	}
	return ans;
}

int main() {
	int t;
	int n, m, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d", &n, &m, &k);
		for(int i = 1; i <= n; ++i ) {
			int x;
			scanf("%d", &x);
			sum[i] = sum[i-1];
			if(x >= m) {
				++sum[i];
			}
		}
		ll ans = solve(n, k);
		printf("%lld\n", ans);
	}
	
	return 0;
} 
