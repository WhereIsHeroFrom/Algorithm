#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 10010
#define eps 1e-9

int di[MAXN];
int dCount[MAXN][10];

int main() {
	int i, j;
	double log2_10 = log(2.0) / log(10.0);
	double nlog2_10 = 0;

	for (i = 0; i < MAXN; ++i) {
		di[i] = int(pow(10.0, nlog2_10 - int(nlog2_10 + eps)) + eps);
		nlog2_10 += log2_10;
		if (i) {
			for (j = 0; j < 10; ++j) {
				dCount[i][j] = dCount[i - 1][j];
			}
		}
		++dCount[i][di[i]];

	}

	int n;
	while (scanf("%d", &n) != EOF && n >= 0) {
		for (i = 1; i < 10; ++i) {
			if (i - 1) printf(" ");
			printf("%d", dCount[n][i]);
		}
		puts("");
	}
	return 0;
}