#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 9
int dir[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

char mat[100][100];
int vis[MAXN][MAXN];

bool dfs(int x, int y, int tag) {
	int i;
	if (x < 0 || y < 0 || x >= MAXN || y >= MAXN) {
		return false;
	}
	if (tag == 0) {
		if (mat[x][y] != 'o') {
			return false;
		}
	}
	else {
		if (mat[x][y] == 'x') {
			return false;
		}
		else if (mat[x][y] == '.') {
			return true;
		}
	}

	if (vis[x][y] == tag) {
		return false;
	}
	vis[x][y] = tag;

	for (i = 0; i < 4; i++) {
		if (dfs(x + dir[i][0], y + dir[i][1], tag)) {
			return true;
		}
	}
	return false;
}

bool check() {
	int i, j;
	memset(vis, -1, sizeof(vis));


	for (i = 0; i < MAXN; i++) {
		for (j = 0; j < MAXN; j++) {
			if ((vis[i][j] == -1) && (mat[i][j] == 'o')) {
				dfs(i, j, 0);
				if (!dfs(i, j, 1)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool solve() {
	int i, j;
	for (i = 0; i < MAXN; i++) {
		for (j = 0; j < MAXN; j++) {
			if (mat[i][j] == '.') {
				mat[i][j] = 'x';
				if (check()) {
					//printf("%d %d\n", i, j);
					return true;
				}
				mat[i][j] = '.';
			}
		}
	}
	return false;
}

int main() {
	int i;
	int cases = 0, t;
	scanf("%d", &t);
	while (t--) {
		for (i = 0; i < MAXN; i++) {
			scanf("%s", mat[i]);
		}

		printf("Case #%d: ", ++cases);
		if (solve()) {
			printf("Can kill in one move!!!\n");
		}
		else {
			printf("Can not kill in one move!!!\n");
		}
	}
	return 0;
}

/*
10
.......xo
.........
.........
..x......
.xox....x
.o.o...xo
..o......
.....xxxo
....xooo.

......ox.
.......o.
...o.....
..o.o....
...o.....
.........
.......o.
...x.....
........o
*/
