#include <iostream>

using namespace std;

#define ll long long

int main() {
	int t;
	scanf("%d", &t);
	
	while(t--) {
		int a, b, c;
		bool f = false;
		scanf("%d %d %d", &a, &b, &c);
		if( c == a || c == b ) {
			f = true;
		}else {
			ll prepre = a, pre = b;
			while(1) {
				ll now = prepre + pre;
				if(now == c) {
					f = true;
				}
				if(now >= c) {
					break;
				}
				prepre = pre;
				pre = now;
			}
		}
		printf("%s\n", f ? "Yes": "No");
	}
	return 0;
} 
