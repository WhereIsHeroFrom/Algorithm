#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 18

int mat[MAXN][MAXN];

// dp[i][j] 当前以第i颗珠子结尾
int dp[MAXN][1 << MAXN];
int n, m;
int Min;

// Yin  编号：[0, n-1)
// Yang 编号：[n, 2n)
// 建立单向边 mat[][]

int dfs(int now, int state) {
	int &v = dp[now][state];
	if (v != -1) {
		return v;
	}

	int i, j;
	for (i = n; i < 2 * n; ++i) {
		if (state & (1 << i)) {
			for (j = 1; j < n; ++j) {
				if (state & (1 << j)) {
					int x = dfs(j, state ^ (1 << i) ^ (1 << j));
					if (mat[i][now] || mat[i][j]) ++x;
					if (x < v || v == -1) {
						v = x;
					}
				}
			}
		}
	}

	if (v == -1) {
		for (i = n; i < 2 * n; ++i) {
			if (state & (1 << i)) {
				v = (mat[i][now] || mat[i][0]) ? 1 : 0;
			}
		}
	}
	return v;
}

// N = 0
// N = 1

int main() {
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF) {

		memset(mat, 0, sizeof(mat));
		memset(dp, -1, sizeof(dp));
		while (m--) {
			int x, y;
			scanf("%d %d", &x, &y);
			--x;
			--y;
			// 单向
			mat[x + n][y] = 1;
		}

		if (n == 0) {
			printf("0\n");
			continue;
		}
		else if (n == 1) {
			printf("%d\n", mat[1][0]);
			continue;
		}

		// 枚举第一个Yin珠子
		// Yin - Yang - Yin - Yang - Yin - Yang - ...
		Min = -1;
		for (i = n; i < 2 * n; ++i) {
			for (j = 1; j < n; ++j) {
				int x = dfs(j, ((1 << (2 * n)) - 1) ^ (1 << i) ^ (1 << j));
				if (mat[i][0] || mat[i][j]) ++x;
				if (x < Min || Min == -1) {
					Min = x;
				}
			}
		}
		printf("%d\n", Min);
	}
	return 0;
}

/*
0 0

1 1
1 1

2 1
1 1

2 4
1 1
1 2
2 1
2 2

3 4
1 1
1 2
1 3
2 1
*/