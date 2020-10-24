// HDU 2063
// 图论：二分图最大匹配

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1010

int pre[MAXN];
int visit[MAXN];
bool umap[MAXN][MAXN];

int n, m;

int dfs(int v) {
	int i;
	if (v == -1) {
		return 1;
	}

	if (visit[v]) {
		return 0;
	}
	else {
		visit[v] = 1;
	}

	for (i = 1; i <= m; ++i) {
		if (!umap[v][i]) continue;
		int k = pre[i];
		pre[i] = v;
		if (dfs(k)) {
			return 1;
		}
		pre[i] = k;
	}
	return 0;
}



int main() {
	int k, i;
	while (scanf("%d", &k) != EOF && k) {
		memset(umap, 0, sizeof(umap));
		memset(pre, -1, sizeof(pre));

		scanf("%d %d", &n, &m);
		while (k--) {
			int x, y;
			scanf("%d %d", &x, &y);
			umap[x][y] = 1;
		}
		int cnt = 0;
		for (i = 1; i <= n; ++i) {
			memset(visit, 0, sizeof(visit));
			if (dfs(i)) {
				++cnt;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}