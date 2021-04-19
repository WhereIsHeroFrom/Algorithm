#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100010;
#define ll long long 

int n, a[maxn];
ll solve(int n, int k) {
	int i = 0, j = -1;
	ll ans = 0;
	while(j < n - 1) {
		++j;
		while (a[j] - a[i] > k) {
			++i;
		}
		ans += (j - i); 
	}
	return ans;
}

int main() {
	int t;
	int n, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &k);
		for(int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);			
		}
		sort(a, a + n);
		printf("%lld\n", solve(n, k));
	}
	
	return 0;
} 
