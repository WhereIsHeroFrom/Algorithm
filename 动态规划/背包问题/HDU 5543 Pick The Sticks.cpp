#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 1010
#define MAXL 4010
#define LL __int64
int n, L;

struct Pack {
	int len, val;
	void read() {
		scanf("%d %d", &len, &val);
		len *= 2;
	}

}p[MAXN];

// f[i][j] 表示前i个物品组成 (长度 <= j) 的最大权值
LL f[MAXN][MAXL];

int cmp(Pack a, Pack b) {
	return a.len < b.len;
}

int main() {
	int t, cases = 0;
	int i, j;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &L);
		L *= 2;
		LL Max = 0;
		for (i = 1; i <= n; i++) {
			p[i].read();
			if (p[i].val > Max) Max = p[i].val;  // 一个金条肯定可以放
		}
		sort(&p[1], &p[1] + n, cmp);
		for (i = 0; i <= L; i++) f[0][i] = 0;
		// 先求一次背包
		for (i = 1; i <= n; i++) {
			int len = p[i].len;
			LL val = p[i].val;
			for (j = 0; j <= L; j++) {
				f[i][j] = f[i - 1][j];
			}
			for (j = L; j >= len; j--) {
				if (f[i - 1][j - len] + val > f[i][j]) {
					f[i][j] = f[i - 1][j - len] + val;
				}
			}
		}

		// 枚举任意两个今天放在两端的情况
		for (i = 1; i <= n; i++) {
			for (j = i + 1; j <= n; j++) {
				int len = (p[i].len + p[j].len) / 2;
				LL val = p[i].val + p[j].val;
				if (len <= L) {
					if (f[i - 1][L - len] + val > Max) {
						Max = f[i - 1][L - len] + val;
					}
				}
			}
		}


		printf("Case #%d: %I64d\n", ++cases, Max);


	}
	return 0;
}

/*
4

3 7
4 1
2 1
8 1

3 7
4 2
2 1
8 4

3 5
4 1
2 2
8 9

1 1
10 3


Case #1: 2
Case #2: 6
Case #3: 11
Case #4: 3
*/