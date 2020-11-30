#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 40

int n, m;
int Map[MAXN][MAXN];

int dir[4][2] = {
	{ 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }
};

bool outOfBound(int r, int c){
	return r < 0 || c < 0 || r > n + 1 || c > m + 1;
}

bool outOfBoard(int r, int c){
	return r <= 0 || c <= 0 || r >= n + 1 || c >= m + 1;
}

bool canConnectByAdjcent() {
	int i, j, d;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			for (d = 0; d < 4; ++d) {
				int ni = i + dir[d][0];
				int nj = j + dir[d][1];
				if (outOfBoard(ni, nj)) {
					continue;
				}
				if (Map[i][j] == Map[ni][nj]) {
					return true;
				}
			}
		}
	}
	return false;
}

bool lineCheck(int r, int c) {
	int i, j;
	vector <int> val;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			if ((r == 0 || r == i) && (c == 0 || c == j)) {
				val.push_back(Map[i][j]);
			}
		}
	}
	sort(val.begin(), val.end());
	for (i = 1; i < val.size(); ++i) {
		if (val[i - 1] == val[i]) {
			return true;
		}
	}
	return false;
}
bool canConnectByCorner() {
	return lineCheck(0, m) || lineCheck(0, 1) || lineCheck(n, 0) || lineCheck(1, 0);
}

bool canConnect() {
	return canConnectByAdjcent() || canConnectByCorner();
}

int main() {
	int t, cas = 0;
	int i, j;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= m; ++j) {
				scanf("%d", &Map[i][j]);
			}
		}
		printf("Case #%d: %s\n", ++cas, canConnect() ? "Yes" : "No");
	}
	return 0;
}