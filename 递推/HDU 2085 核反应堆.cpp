// HDU 2085
// ¼òÒ×µÝÍÆ
//		dp[i][0] = dp[i - 1][0] * 3 + dp[i - 1][1] * 2;
//		dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
//

#include <iostream>
#include <cstring>
#include <cmath>
#include <cstring>
using namespace std;

#define LL __int64

LL dp[110][100];

int main() {
	int i, j;
	dp[0][0] = 1;
	dp[0][1] = 0;

	for (i = 1; i < 40; ++i) {
		dp[i][0] = dp[i - 1][0] * 3 + dp[i - 1][1] * 2;
		dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
	}
	int n;
	while (scanf("%d", &n) != EOF && n != -1) {
		printf("%I64d, %I64d\n", dp[n][0], dp[n][1]);
	}

	return 0;
}