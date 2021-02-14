#include <iostream> 

using namespace std;

#define ll long long 
int n, m;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		ll s = 0;
		while(n--) {
			int v;
			scanf("%d", &v);
			s += v;
		}
		while(m--) {
			ll x;
			scanf("%lld", &x);
			printf("%d", x>s ? 1 : 0);	
		}
		puts("");
	}
	return 0;
}
