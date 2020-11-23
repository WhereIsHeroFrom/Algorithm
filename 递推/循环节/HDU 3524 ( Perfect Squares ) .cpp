#include <iostream>

using namespace std;

#define MOD 10007
int has[2][2 * MOD + 10];
int f[MOD + 10];
int end;

int getAns(int idx) {
	if (idx <= 2) {
		return 2;
	}
	return f[(idx - 2) % end];
}

int main() {
	int i, j;
	int n;

	/*for(i = 1; i < 13 ; i++) {
	memset(has, 0, sizeof(has));
	for(j = 0; j < 10000; j++) {
	has[0][j*j % (1<<i)] = 1;
	}
	int c = 0;
	for(j = 0; j < (1<<i); j++) {
	if(has[0][j]) c++;
	}
	printf("%d %d\n", i, c);
	}*/

	memset(has, -1, sizeof(has));
	f[0] = 2;
	has[0][f[0]] = 0;
	for (i = 1;; i++) {
		if (i & 1) {
			f[i] = (2 * f[i - 1] + MOD - 1) % MOD;
		}
		else {
			f[i] = (2 * f[i - 1] + MOD - 2) % MOD;
		}
		//printf("%d\n", f[i]);
		if (has[i & 1][f[i]] != -1) break;
		has[i & 1][f[i]] = i;
	}
	end = i;
	//printf( "%d %d\n", end, f[end] );

	int cases = 1;
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		printf("Case #%d: %d\n", cases++, getAns(n));
	}

	return 0;
}