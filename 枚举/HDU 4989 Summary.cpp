#include <iostream>
#include <algorithm> 

using namespace std;

#define ll long long

int a[110];
int b[11000];

int main() {
	int n, i, j;
	 
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		int tp = 0;
		for(i = 0; i < n; ++i) {
			for(j = i +1; j < n; ++j) {
				b[tp++]  =a[i] + a[j];
			} 
		}
		sort(b, b + tp);
		ll s = b[0];
		for(i = 1; i < tp; ++i) {
			if(b[i] != b[i-1]) {
				s += b[i];
			}
		}
		printf("%lld\n", s);
	}
	return 0;
} 
