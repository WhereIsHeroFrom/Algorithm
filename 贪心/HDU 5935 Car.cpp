// HDU 5935
// 贪心 
// 所有的时间要求整数，所有的速度是实数； 
// 要求速度不降，即:   (a[1]-a[0])/t1 <=  (a[2]-a[1])/t2 <= ... <= (a[N]-a[N-1])/tN
// 求 sum  {ti | 1<=i<=N} 
// 根据贪心法则，tN 肯定取越小越好，即1，然后从后往前一次求出整数 ti 累加；
 
#include <iostream>

using namespace std;

#define MAXN 100010
#define ll __int64

ll a[MAXN], T[MAXN];
int n;

int main() {
	int i, t, cas = 0;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		ll ans = 0; 
		for(i = n; i >= 1; i--) {
			a[i] -= a[i-1];
			if(i == n) {
				T[i] = 1;
			}else {
				ll s = a[i] * T[i+1];
				if(s % a[i+1]) {
					T[i] = s / a[i+1] + 1;
				}else {
					T[i] = s / a[i+1];
				}
			}
			
			ans += T[i];
		}
		
		printf("Case #%d: %I64d\n", ++cas, ans);
	}
	
	
	return 0;
} 
