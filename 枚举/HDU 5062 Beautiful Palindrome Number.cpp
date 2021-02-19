#include <iostream> 

using namespace std;

int a[10], c;
int ans[10];

bool check(int v) {
	c = 0;
	while(v) {
		a[c++] = v % 10;
		v /= 10;
	}
	int s = (c&1)?(c+1)/2:c/2; 
	for(int j = 0; j < s; ++j) {
		if(!a[j]) {
			return false;
		}
		if(j) {
			if( a[j] <= a[j-1] ) {
				return false;	
			}
		}
		if(a[j] != a[c-j-1]) {
			return false;
		}
	}
	return true;
}

int main() {
	int t;
	for(int i = 1; i <= 1000000; ++i) {
		if(check(i)) {
			for(int j = c; j <= 6; ++j) {
				++ ans[j];
			}
		}
	}
	ans[0] = 1;
	 
	scanf("%d", &t);

	while(t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
