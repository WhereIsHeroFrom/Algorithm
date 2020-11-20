#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 2

char mat[MAXN*MAXN + 1][MAXN*MAXN + 1];
int st[20];
int v[5];

bool check(int x, int y) {
	int sx = x / MAXN;
	int sy = y / MAXN;
	int i, j;
	memset(v, 0, sizeof(v));
	for (i = MAXN*sx; i < MAXN*sx + MAXN; i++) {
		for (j = MAXN*sy; j < MAXN*sy + MAXN; j++) {
			if (mat[i][j] != '*') {
				if (v[mat[i][j] - '0']) {
					return false;
				}
				v[mat[i][j] - '0'] = 1;
			}
		}
	}
	memset(v, 0, sizeof(v));
	for (i = 0; i < 4; i++) {
		if (mat[i][y] == '*') continue;
		if (v[mat[i][y] - '0']) {
			return false;
		}
		v[mat[i][y] - '0'] = 1;
	}

	memset(v, 0, sizeof(v));
	for (i = 0; i < 4; i++) {
		if (mat[x][i] == '*') continue;
		if (v[mat[x][i] - '0']) {
			return false;
		}
		v[mat[x][i] - '0'] = 1;
	}

	return true;
}

bool dfs(int depth) {
	int i;
	if (depth == st[0] + 1) {
		for (i = 0; i < MAXN*MAXN; i++) {
			puts(mat[i]);
		}
		return true;
	}

	int x = st[depth] / (MAXN*MAXN);
	int y = st[depth] % (MAXN*MAXN);

	for (i = 1; i <= 4; i++) {
		mat[x][y] = i + '0';
		if (check(x, y)) {
			if (dfs(depth + 1)) {
				return true;
			}
		}
		mat[x][y] = '*';
	}
	return false;
}

int main() {
	int i, j;
	int cases = 0, t;
	scanf("%d", &t);
	while (t--) {
		st[0] = 0;
		for (i = 0; i < MAXN*MAXN; i++) {
			scanf("%s", mat[i]);
			for (j = 0; j < MAXN*MAXN; j++) {
				if (mat[i][j] == '*') {
					st[++st[0]] = i * (MAXN*MAXN) + j;
				}
			}
		}
		printf("Case #%d:\n", ++cases);
		dfs(1);

	}
	return 0;
}