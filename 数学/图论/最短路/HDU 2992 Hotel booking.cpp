/*
两次最短路：
1）求所有有宾馆的点到所有其他点的最短路（触发距离不能超过600），然后建立新边；
2）对新的边求一次最短路；
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 10010

int n;
int visited[MAXN];
int start[MAXN];

struct Edge {
	int to, val;
	Edge() {}
	Edge(int _to, int _val) : to(_to), val(_val) {
	}
};
vector <Edge> E[2 * MAXN], NewE[2 * MAXN];


void bfs(int s) {
	NewE[s].clear();
	memset(visited, -1, sizeof(visited));

	queue <int> Q;
	Q.push(s);
	visited[s] = 0;

	int i;
	while (!Q.empty()) {
		int s = Q.front();
		Q.pop();
		for (i = E[s].size() - 1; i >= 0; --i) {
			Edge &e = E[s][i];
			if (visited[s] + e.val > 600) {
				continue;
			}
			if (visited[e.to] == -1 || visited[s] + e.val < visited[e.to]) {
				visited[e.to] = visited[s] + e.val;
				Q.push(e.to);
			}
		}
	}

	for (i = 1; i <= n; ++i) {
		if (i != s && visited[i] != -1) {
			NewE[s].push_back(Edge(i, visited[i]));
			//printf("%d --%d--> %d\n", s, visited[i], i);
		}
	}
}

int BFS(int s, int t) {
	memset(visited, -1, sizeof(visited));

	queue <int> Q;
	Q.push(s);
	visited[s] = 0;

	int i;
	while (!Q.empty()) {
		int s = Q.front();
		Q.pop();
		if (s == t) {
			return visited[s];
		}
		for (i = NewE[s].size() - 1; i >= 0; --i) {
			Edge &e = NewE[s][i];
			if (visited[e.to] == -1) {
				visited[e.to] = visited[s] + 1;
				Q.push(e.to);
			}
		}
	}

	return -1;
}


int main() {
	int i, j;
	int m;
	while (scanf("%d", &n) != EOF && n) {
		for (i = 1; i <= n; ++i) {
			NewE[i].clear();
			E[i].clear();
		}
		scanf("%d", &start[0]);
		for (i = 1; i <= start[0]; ++i) {
			scanf("%d", &start[i]);
		}

		start[++start[0]] = 1;
		scanf("%d", &m);
		while (m--) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			E[a].push_back(Edge(b, c));
			E[b].push_back(Edge(a, c));
		}
		for (i = 1; i <= start[0]; ++i) {
			int u = start[i];
			bfs(start[i]);
		}
		int ans = BFS(1, n);
		if (ans != -1) --ans;
		printf("%d\n", ans);
	}
	return 0;
}

/*
6
3 2 5 3
8
1 2 400
3 2 80
3 4 301
4 5 290
5 6 139
1 3 375
2 5 462
4 6 300
3
0
2
1 2 371
2 3 230
*/