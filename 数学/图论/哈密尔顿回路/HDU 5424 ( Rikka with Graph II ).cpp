#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1010

int n;
int deg[MAXN];
int vis[MAXN];
int mat[MAXN][MAXN], T = 1;

struct edge {
	int u, v, next;
	edge() {
	}
	edge(int _u, int _v, int _next) {
		u = _u;
		v = _v;
		next = _next;
	}

	bool eq(edge tar) {
		return (u == tar.u && v == tar.v) || (v == tar.u && u == tar.v);
	}

}E[MAXN], nodes[MAXN * 2];
int tot;
int head[MAXN];

void addEdge(int u, int v) {
	nodes[tot] = edge(u, v, head[u]);
	head[u] = tot++;
}

void dfs(int u, edge exclude) {
	vis[u] = T;

	for (int e = head[u]; e != -1; e = nodes[e].next) {
		int v = nodes[e].v;
		if (exclude.eq(nodes[e])) continue;
		if (vis[v] != T) {
			dfs(v, exclude);
		}
	}
}

bool isJoint(int start, edge exclude = edge(-1, -1, -1)) {
	T++;
	dfs(start, exclude);
	for (int i = 1; i <= n; i++) {
		if (vis[i] != T) {
			return false;
		}
	}
	return true;
}

bool hasHamiltonian() {
	if (n == 1) {
		return true;
	}

	int i, j;
	T++;
	int loops = 0, multi_edges = 0;
	int loops_idx = -1, multi_edges_idx = -1;

	tot = 0;
	memset(head, -1, sizeof(head));
	memset(deg, 0, sizeof(deg));
	memset(mat, 0, sizeof(mat));

	for (i = 0; i < n; i++) {
		if (E[i].u == E[i].v) {
			loops++;
			loops_idx = i;
			continue;
		}

		if (mat[E[i].u][E[i].v]) {
			multi_edges++;
			multi_edges_idx = i;
			continue;
		}

		mat[E[i].u][E[i].v] = mat[E[i].v][E[i].u] = 1;

		deg[E[i].u] ++;
		deg[E[i].v] ++;

		addEdge(E[i].u, E[i].v);
		addEdge(E[i].v, E[i].u);

	}

	if (!isJoint(1)) {
		return false;
	}

	if (loops + multi_edges > 1) {
		// 自环加上重边 > 1，剩下 n - (loops+multi_edges) 条边无法构成哈密尔顿路径 
		return false;
	}
	else if (loops == 1 || multi_edges == 1) {
		int elimate_idx = loops_idx != -1 ? loops_idx : multi_edges_idx;

		int deg1[3] = { 0 };

		for (j = 1; j <= n; j++) {
			if (deg[j] == 1 || deg[j] == 2) {
				if (deg[j] == 1) {
					if (deg1[0] == 2) {
						break;
					}
					else {
						deg1[++deg1[0]] = j;
					}
				}
			}
			else {
				break;
			}
		}

		if (j <= n || deg1[0] != 2) {
			// 去掉重边或者自环后，所有点的度数必须满足，要么是1，要么是2
			// 并且，度数为1的点必须正好是两个 
			return false;
		}
		else {
			return true;
		}
	}
	else {
		// 无自环 无重边 
		int notDeg2 = 0;
		int deg3[4] = { 0 };

		for (i = 1; i <= n; i++) {
			if (deg[i] >= 4) {
				// 某个点度数大于等于4，说明要去掉两条边，不行 
				return false;
			}

			if (deg[i] != 2) {
				notDeg2++;
			}

			if (deg[i] == 3) {
				if (deg3[0] == 2) {
					// 不可能有3个度数为3的点 
					return false;
				}
				else {
					deg3[++deg3[0]] = i;
				}
			}
		}

		if (notDeg2 == 0) {
			// 都是度数为2的点，则从1开始搜索，如果是连通的，就一定是一个环 
			// 否则可能是多个环 
			return true;
		}
		else if (deg3[0] == 1) {
			// 度数为3的点的个数允许 0 、 1 、 2 个 
			return true;
		}
		else if (deg3[0] == 2) {
			return (mat[deg3[1]][deg3[2]] == 1) && isJoint(1, edge(deg3[1], deg3[2], -1));
		}
		else {
			return false;
		}
	}
}

int main() {
	int i;
	while (scanf("%d", &n) != EOF) {
		for (i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			E[i] = edge(x, y, -1);
		}
		printf("%s\n", hasHamiltonian() ? "YES" : "NO");
	}
	return 0;
}