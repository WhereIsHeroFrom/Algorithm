#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 51
#define eps 1e-6

class Point {
public:
	double x, y;

	Point() {}
	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}
	Point operator+(const Point& other) {
		return Point(x + other.x, y + other.y);
	}
	Point operator-(const Point& other) {
		return Point(x - other.x, y - other.y);
	}
	double dist2(const Point& other) {
		Point pt = *this - other;
		return pt.x*pt.x + pt.y*pt.y;
	}
}p[MAXN * 2];

int cmp(const Point a, const Point b) {
	return a.x + a.y < b.x + b.y;
}


int n, k;
bool mat[MAXN][MAXN];
int dp[MAXN], maxVal;

// 找到下一个和u相邻的结点
int get_next(int u, bool adj[]) {
	for (int i = u + 1; i < n; i++) {
		if (adj[i]) {
			return i;
		}
	}
	return -1;
}

bool dfs(int depth, int now, bool adj[]) {
	int i;
	bool next_adj[MAXN];
	bool now_adj[MAXN];

	for (i = now; i < n; i++) {
		next_adj[i] = adj[i];   // 用于传参
		now_adj[i] = adj[i];    // 用于回溯
	}

	// 找到和now相邻的编号最小的结点
	int next = get_next(now, adj);
	if (next == -1) {
		if (depth + 1 > maxVal) {
			maxVal = depth + 1;
			return true;
		}
		return false;
	}

	// 遍历now邻接的所有顶点
	// now -> next
	while (next != -1) {

		// 不算now，团里点数为depth
		// 到now为止已经在团里的点数为 depth+1
		if ((n - now) + depth <= maxVal) {
			// next以后的结点组成的团的最大值 n-next
			// 两者相加小于等于最大值，无需往下枚举
			return false;
		}
		if (dp[next] + depth + 1 <= maxVal) {
			// next以后的结点组成的团的最大值 n-next
			// 两者相加小于等于最大值，无需往下枚举
			return false;
		}

		now_adj[next] = 0;
		for (i = next + 1; i < n; i++) {
			next_adj[i] = (now_adj[i] && mat[next][i]);
		}

		if (dfs(depth + 1, next, next_adj)) {
			return true;
		}
		next = get_next(next, now_adj);
	}
	return false;
}

bool MaximumClique() {
	int i, j;
	bool adj[MAXN];

	maxVal = 0;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j < n; j++) {
			adj[j] = mat[i][j];
		}
		dfs(0, i, adj);
		dp[i] = maxVal;
		if (dp[i] >= k) {
			return true;
		}
		if (dp[i] + i < k) {
			return false;
		}
	}
	return false;
}

bool check(int dist) {
	int i, j;
	int Max = 0;
	for (i = 0; i < n; i++) {
		int cnt = 0;
		for (j = 0; j < n; j++) {
			mat[i][j] = (p[i].dist2(p[j]) >= dist);
			if (mat[i][j]) cnt++;
		}
		if (cnt >= k - 1) Max++;
	}
	if (Max < k) return false;

	return MaximumClique();
}

int main() {
	int i;
	while (scanf("%d %d", &n, &k) != EOF) {
		for (i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			p[i] = Point(x, y);
		}
		sort(p, p + n, cmp);
		int l = 0, r = 1000000000;
		int ans = 0;
		while (l <= r) {

			int mid = (l + r) / 2;
			//printf("%d %d %d\n", l, r, mid);
			if (check(mid)) {
				l = mid + 1;
				ans = mid;
			}
			else {
				r = mid - 1;
			}
		}
		printf("%.2lf\n", sqrt(1.0*ans));

	}
	return 0;
}

/*
3 2
0 0
10 0
0 20

50 25
1 21 2 222 3 23 4 224 5 25
1 1 2 2 3 3 4 4 5 5

11 11 12 12 13 13 14 14 15 15

211 211 212 212 213 213 14 214 215 215

211 211 212 212 213 213 214 214 215 215

1211 1211 1212 1212 2113 2113 114 2114 2115 1215

11 11 12 12 13 13 14 14 15 15

211 211 212 212 213 213 14 214 215 215

211 211 212 212 213 213 214 214 215 215

1211 1211 1212 1212 2113 2113 114 2114 2115 1215
*/