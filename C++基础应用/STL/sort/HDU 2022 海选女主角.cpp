// HDU 2022
// vector
// STL 排序 + 小于号重载 的应用
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Grid {
	int r, c;
	__int64 v;
	__int64 absv;

	bool operator <(const Grid& other) const {
		if (absv != other.absv)
		{
			return absv > other.absv;
		}
		if (r != other.r) {
			return r < other.r;
		}
		return c < other.c;
	}
};

vector <Grid> vec;
int main() {
	int n, m;
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF) {
		vec.clear();
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= m; j++) {
				Grid g;
				scanf("%I64d", &g.v);
				g.absv = g.v < 0 ? -g.v : g.v;
				g.r = i;
				g.c = j;
				vec.push_back(g);
			}
		}
		sort(vec.begin(), vec.end());
		printf("%d %d %I64d\n", vec[0].r, vec[0].c, vec[0].v);
	}
	return 0;
}