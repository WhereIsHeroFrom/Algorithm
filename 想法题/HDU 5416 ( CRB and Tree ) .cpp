#include <iostream>
#include <vector>
using namespace std;

#define MAXN (1<<17)

struct edge{
	int v, val;
	edge() {
	}
	edge(int _v, int _val) {
		v = _v;
		val = _val;
	}
};

vector <edge> vec[MAXN];

int N;
int xorsum[MAXN];
int has[MAXN];

void dfs(int fat, int u) {
	for (int i = 0; i < vec[u].size(); i++) {
		edge nex = vec[u][i];
		if (nex.v == fat) {
			continue;
		}
		xorsum[nex.v] = xorsum[u] ^ nex.val;
		dfs(u, nex.v);
	}
}
int main() {
	int t;
	int i;
	int Q, s;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &N);
		for (i = 1; i <= N; i++) {
			vec[i].clear();
			xorsum[i] = 0;
		}
		for (i = 0; i < MAXN; i++) {
			has[i] = 0;
		}
		for (i = 0; i < N - 1; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			vec[x].push_back(edge(y, z));
			vec[y].push_back(edge(x, z));
		}
		dfs(-1, 1);
		for (i = 1; i <= N; i++) {
			has[xorsum[i]] ++;
			//printf("%d %d\n", xorsum[i], has[ xorsum[i] ]);
		}

		scanf("%d", &Q);
		while (Q--) {
			scanf("%d", &s);
			__int64 ans = 0;
			if (s == 0) {
				for (i = 1; i <= N; i++) {
					if (has[xorsum[i]] > 1) {
						__int64 cnt = has[xorsum[i]];
						ans += (cnt - 1);
					}
				}
				ans /= 2;
				ans += N;
			}
			else {

				for (i = 1; i <= N; i++) {
					ans += has[xorsum[i] ^ s];
				}
				ans /= 2;
			}
			printf("%I64d\n", ans);
		}

	}
	return 0;
}

/*
10
3
1 2 1
2 3 2
3
2
3
4

10
5
1 2 4
1 3 5
3 4 1
3 5 6
10
0 1 2 3 4 5 6 7 8 9

10
5
1 2 5
1 3 5
3 4 5
3 5 5
10
0 1 2 3 4 5 6 7 8 9
*/