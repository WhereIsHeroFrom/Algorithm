#include <iostream>

using namespace std;

#define MAXN 1010

char name[2][5] = { "girl", "cat" };

int n, m;
char mat[MAXN][MAXN];
int cnt[2];

int dir[4][2] = {
	{ 1, 0 },
	{ -1, 0 },
	{ 0, 1 },
	{ 0, -1 }
};

void dfs(int k, int r, int c, int now) {
	if (name[k][now] == '\0') {
		++cnt[k];
		return;
	}

	int i;
	for (i = 0; i < 4; ++i) {
		int tr = r + dir[i][0];
		int tc = c + dir[i][1];
		if (tr < 0 || tr >= n || tc < 0 || tc >= m) continue;
		if (name[k][now] == mat[tr][tc]) {
			dfs(k, tr, tc, now + 1);
		}
	}
}


int main() {
	int t;
	int i, j, k;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		for (i = 0; i < n; ++i) {
			scanf("%s", mat[i]);
		}
		cnt[0] = cnt[1] = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				for (k = 0; k < 2; ++k) {
					if (name[k][0] == mat[i][j])
						dfs(k, i, j, 1);
				}
			}
		}
		printf("%d %d\n", cnt[0], cnt[1]);
	}
	return 0;
}