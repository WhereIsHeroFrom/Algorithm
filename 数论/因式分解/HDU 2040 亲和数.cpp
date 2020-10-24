// HDU 2040
// 数论：一个数   p1^e1 p2^e2 ... 的因子和等于   p1^(e1+1)/(p1 - 1) *  p2^(e2+1)/(p2 - 1) ...  
// 预处理
// 1. 素数筛选
// 2. 因式分解

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 600010

struct Fact {
	int pri;
	int cnt;
};

bool p[MAXN];
int pri[MAXN];
__int64 X[MAXN];

__int64 doFact(int val) {
	__int64 ans = 1;
	for (int i = 1; i <= pri[0]; ++i) {
		if (val % pri[i] == 0) {
			int nowp = pri[i] * pri[i];
			val /= pri[i];
			while (val % pri[i] == 0) {
				nowp *= pri[i];
				val /= pri[i];
			}
			ans *= (nowp - 1) / (pri[i] - 1);
		}
		if (val == 1) break;
		if (!p[val]) break;
	}
	if (val > 1) {
		ans *= (val + 1);
	}
	return ans;
}

int main() {
	int t, i;

	p[1] = 1;
	pri[0] = 0;
	for (i = 2; i < MAXN; ++i) {
		if (!p[i]) {
			pri[++pri[0]] = i;
			for (__int64 j = (__int64)i*(__int64)i; j < MAXN; j += i) {
				p[j] = 1;
			}
		}
	}

	X[0] = 0;
	for (i = 1; i < MAXN; ++i) {
		X[i] = doFact(i) - i;
	}

	scanf("%d", &t);
	while (t--) {
		int x, y;
		scanf("%d %d", &x, &y);
		//printf("%I64d %I64d\n", X[x], X[y] );

		if (X[x] == y && X[y] == x) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}
