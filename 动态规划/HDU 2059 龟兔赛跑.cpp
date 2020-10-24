// HDU 2059
// 简单动态规划
// dp[i] 表示 截止到第i个充电站（或者终点）乌龟花费的最少时间；
// 由于每次进行充电后，乌龟的可行驶距离和之前剩余可行驶距离无关，所以每个充电站是一个新的状态开始，
// 以每个充电站为小状态进行状态转移即可

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define LL __int64

LL N, C, T;
LL L;
LL Vr, Vt1, Vt2;
LL p[200];
double dp[200];

int main() {
	int t;
	int i, j;
	while (scanf("%I64d", &L) != EOF) {
		dp[0] = 0;
		scanf("%I64d %I64d %I64d", &N, &C, &T);
		scanf("%I64d %I64d %I64d", &Vr, &Vt1, &Vt2);
		for (i = 1; i <= N; ++i) {
			scanf("%I64d", &p[i]);
		}
		p[N + 1] = L;

		for (i = 1; i <= N + 1; ++i) {
			dp[i] = -1;
			for (j = 0; j < i; ++j) {
				double t;
				if (p[i] - p[j] <= C) {
					t = (p[i] - p[j]) * 1.0 / Vt1 + (j ? T : 0);
				}
				else {
					t = C * 1.0 / Vt1 + (j ? T : 0) + (p[i] - p[j] - C) * 1.0 / Vt2;
				}

				if (dp[i] < 0 || dp[j] + t < dp[i]) {
					dp[i] = dp[j] + t;
				}
			}
			//printf("%lf\n", dp[i]);
		}

		if (dp[N + 1] * Vr <= L) {
			printf("What a pity rabbit!\n");
		}
		else {
			printf("Good job,rabbit!\n");
		}
	}


	return 0;
}