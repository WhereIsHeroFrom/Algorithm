#include <iostream>
#include <algorithm>

using namespace std;

int n;
int a[110], b[110];
int as, bs;

void process(int insize, int *a, int& outsize) {
	sort(a, a + insize);
	outsize = 0;
	for(int i = 0; i < insize; ++i) {
		if(!i || a[i] != a[i-1]) {
			a[outsize++] = a[i];
		}
	}
}

bool cmp(int asize, int *a, int bsize, int *b) {
	if(asize != bsize) {
		return false;
	}
	for(int i = 0; i < asize; ++i) {
		if(a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	int i, j;
	
	while(scanf("%d", &n) != EOF) {
		for(i = 0 ;i < n; ++i) {
			scanf("%d", &a[i]);		
		}	
		process(n, a, as);
		
		for(i = 0; i < n; ++i) {
			scanf("%d", &b[i]);
		}
		process(n, b, bs);
		printf("%s\n", cmp(as, a, bs, b) ? "YES": "NO" );
	}
	
	return 0;
} 
