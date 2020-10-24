// HDU 2066
// 图论：最短路
// STL : 队列 queue 的应用
// 贝尔曼 BFS 注意双向边

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1010

int T, n, S, D;
int tar[MAXN];

struct Edge {
	int to, val;
	Edge() {}
	Edge(int t, int v) : to(t), val(v) {}
};
vector <Edge> E[MAXN];
int dist[MAXN];

int main() {
	int i;
	int v;
	while (scanf("%d %d %d", &T, &S, &D) != EOF) {
		for (i = 0; i < MAXN; ++i) {
			E[i].clear();
			tar[i] = 0;
			dist[i] = -1;
		}
		for (i = 0; i < T; ++i) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			E[x].push_back(Edge(y, z));
			E[y].push_back(Edge(x, z));
		}

		while (S--) {
			scanf("%d", &v);
			E[0].push_back(Edge(v, 0));
		}

		while (D--) {
			scanf("%d", &v);
			tar[v] = 1;
		}
		dist[0] = 0;
		queue <Edge> Q;
		Q.push(Edge(0, 0));

		while (!Q.empty()) {
			Edge now = Q.front();
			Q.pop();

			for (i = 0; i < E[now.to].size(); ++i) {
				int to = E[now.to][i].to;
				int val = dist[now.to] + E[now.to][i].val;
				if (dist[to] == -1 || val < dist[to]) {
					dist[to] = val;
					Q.push(Edge(to, val));
				}
			}
		}

		int ans = -1;
		for (i = 0; i < MAXN; ++i) {
			if (tar[i] && dist[i] != -1) {
				if (ans == -1 || dist[i] < ans) ans = dist[i];
			}
		}
		if (ans == -1) ans = 0;
		printf("%d\n", ans);
	}

	return 0;
}