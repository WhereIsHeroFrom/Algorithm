#pragma comment(linker,"/STACK:102400000,1024000")

#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100010
#define MOD 1000000007

vector <int> vec[MAXN];
vector <int> newv[MAXN];    // 新构建的树
int soncnt[MAXN];
int gsoncnt[MAXN];
bool has[MAXN];
int n;

__int64 fac[MAXN];

void build(int pt) {
	int i;
	int son;

	gsoncnt[pt] = 1;
	for (i = vec[pt].size() - 1; i >= 0; i--) {
		son = vec[pt][i];
		if (has[son]) {
			continue;
		}
		has[son] = 1;
		newv[pt].push_back(son);
		soncnt[pt] ++;
		build(son);
		gsoncnt[pt] += gsoncnt[son];
	}
}

// now == l or r
int dfs(int pt, int l, int r, int now) {
	if (l == r) {
		return 1;
	}
	int i;
	int gson[5], gsonsize = 0;
	// gson[] 保存了儿子中结点数大于1的儿子的编号

	for (i = newv[pt].size() - 1; i >= 0; i--) {
		int son = newv[pt][i];
		if (gsoncnt[son] > 1) {
			gson[gsonsize++] = son;
			if (gsonsize > 2) {
				return 0;
			}
		}
	}

	int nl = l, nr = r;
	if (now == l) {
		nl = l + 1;
	}
	else if (now == r) {
		nr = r - 1;
	}

	int onesoncnt = soncnt[pt] - gsonsize;

	if (gsonsize == 0) {
		return fac[onesoncnt];
	}
	else if (gsonsize == 1) {
		// 从小到大，给多个结点的儿子先分配 [nl, nl + gsoncnt[ gson[0] ] - 1]
		__int64 ans = (__int64)dfs(gson[0], nl, nl + gsoncnt[gson[0]] - 1, nl + gsoncnt[gson[0]] - 1) * fac[onesoncnt] % MOD;
		return ans * 2 % MOD;
	}
	else if (gsonsize == 2) {
		__int64 ans = (__int64)dfs(gson[0], nl, nl + gsoncnt[gson[0]] - 1, nl + gsoncnt[gson[0]] - 1) * fac[onesoncnt] % MOD * \
			(__int64)dfs(gson[1], nr - gsoncnt[gson[1]] + 1, nr, nr - gsoncnt[gson[1]] + 1) % MOD;
		return ans * 2 % MOD;
	}
	return 0;
}

int main() {
	int t;
	int i;
	int x, y;
	int cases = 1;
	fac[0] = 1;
	for (i = 1; i < MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
	}
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 1; i <= n; i++) {
			vec[i].clear();
			newv[i].clear();
			has[i] = 0;
			soncnt[i] = 0;
			gsoncnt[i] = 0;
		}

		for (i = 0; i < n - 1; i++) {
			scanf("%d %d", &x, &y);
			vec[x].push_back(y);
			vec[y].push_back(x);
		}
		has[1] = 1;
		build(1);

		/*for(i = 1; i <= n; i++) {
		printf("%d %d %d...\n", i, soncnt[i], gsoncnt[i]);
		}*/
		int ans = 2 * dfs(1, 1, n, n) % MOD;
		if (n == 1) ans = 1;
		printf("Case #%d: %d\n", cases++, ans);
	}
	return 0;
}

/*
10
9
2 1
3 1
4 3
5 3
6 2
7 4
8 7
9 3
8
2 1
3 1
4 3
5 1
6 4
7 5
8 4
*/