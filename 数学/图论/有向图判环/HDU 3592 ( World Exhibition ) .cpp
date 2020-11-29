#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1010

struct edge {
	int to, val;
	edge() {
	}
	edge(int _t, int _v) {
		to = _t;
		val = _v;
	}
};

int n;
int dis[MAXN];
int visitCount[MAXN];

vector <edge> vec[MAXN];

// 返回是否存在环 
bool spfa(int s) {
	int i;
	for (i = 1; i <= n; i++) {
		dis[i] = -1;
		visitCount[i] = 0;
	}
	dis[s] = 0;

	queue <edge> Q;
	Q.push(edge(s, 0));

	while (!Q.empty()) {
		edge now = Q.front();
		Q.pop();

		int from = now.to;
		int predist = now.val;

		if (visitCount[from]++ > n) {
			return true;
		}

		for (i = vec[from].size() - 1; i >= 0; i--) {
			int to = vec[from][i].to;
			int nextdist = vec[from][i].val + predist;

			if (nextdist < dis[to] || dis[to] == -1) {
				dis[to] = nextdist;
				Q.push(edge(to, nextdist));
			}
		}
	}

	return false;
}

void addEdge(int u, int v, int c) {
	vec[u].push_back(edge(v, c));
}

int main() {
	int t;
	int X, Y;
	int i, j;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d %d", &n, &X, &Y);
		for (i = 1; i <= n; i++) {
			vec[i].clear();
			if (i > 1) {
				addEdge(i, i - 1, -1);
			}
		}
		while (X--) {
			int A, B, C;
			scanf("%d %d %d", &A, &B, &C);
			addEdge(A, B, C);
		}

		while (Y--) {
			int A, B, C;
			scanf("%d %d %d", &A, &B, &C);
			addEdge(B, A, -C);
		}

		bool ans = spfa(1);
		if (dis[n] == -1) {
			printf("-2\n");
		}
		else {
			if (ans) {
				printf("-1\n");
			}
			else {
				printf("%d\n", dis[n]);
			}
		}

	}
	return 0;
}

/*
2
4 2 1
1 3 8
2 4 15
2 3 4


2 1 1
1 2 4
1 2 5
*/
[Copy to Clipboard][Save to File]
