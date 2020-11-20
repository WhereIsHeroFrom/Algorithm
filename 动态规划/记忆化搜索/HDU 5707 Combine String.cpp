#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 2020

char a[MAXN], b[MAXN], c[MAXN];
int dp[MAXN][MAXN];
int la, lb, lc;

bool dfs(int ai, int bi, int ci) {
	bool ans = false;
	if (ai == la && bi == lb) {
		return true;
	}
	if (dp[ai][bi] != -1) {
		return dp[ai][bi];
	}

	if (a[ai] == c[ci]) {
		ans = ans || dfs(ai + 1, bi, ci + 1);
	}
	if (b[bi] == c[ci]) {
		ans = ans || dfs(ai, bi + 1, ci + 1);
	}
	return dp[ai][bi] = (ans ? 1 : 0);
}

bool solve() {
	la = strlen(a), lb = strlen(b), lc = strlen(c);
	if (la + lb != lc)
		return false;
	memset(dp, -1, sizeof(dp));
	return dfs(0, 0, 0);
}

int main() {
	while (scanf("%s %s %s", a, b, c) != EOF) {
		printf("%s\n", solve() ? "Yes" : "No");
	}
	return 0;
}