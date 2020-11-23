#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#define eps 1e-6
#define maxn 1010
#define inf 10000000

struct point {
	int x, y;
}pt[maxn];

bool cmp(point a, point b) {
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

double dis[maxn][maxn];
int n;

double sqr(double x) {
	return x * x;
}

double Dist(point pt1, point pt2) {
	double tmp = sqr(pt1.x - pt2.x) + sqr(pt1.y - pt2.y);
	return sqrt(tmp);
}

bool SameLine(point a, point b, point c) {
	return (a.x - b.x) * (c.y - b.y) == (c.x - b.x) * (a.y - b.y);
}

int s[maxn], top;

int main() {
	int t;
	int i, j, k;
	int Case = 1;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
		}
		sort(pt, pt + n, cmp);

		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				dis[i][j] = dis[j][i] = Dist(pt[i], pt[j]);
			}
		}
		double ans = 1e30;

		for (i = 0; i < n; i++) {
			top = 0;
			for (j = i + 1; j < n; j++) {
				if (dis[i][j] >= ans)
					continue;
				if (pt[j].x - pt[i].x >= ans)
					break;
				s[top++] = j;
			}

			for (j = 0; j < top; j++) {
				for (k = s[j] + 1; k < n; k++) {
					if (SameLine(pt[i], pt[s[j]], pt[k]))
						continue;
					double sd = dis[i][s[j]] + dis[i][k] + dis[s[j]][k];
					if (sd < ans) {
						ans = sd;
					}
				}
			}
		}

		printf("Case %d: ", Case++);
		if (ans > 1e20)
			printf("No Solution\n");
		else
			printf("%.3lf\n", ans);
	}
	return 0;
}