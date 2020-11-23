#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <map>
using namespace std;

#define MAXN 100010
#define MAXM 500010
#define LL __int64

int n, m;

struct Edge {
	int v;
	int value;
	int next;
	Edge(){}
	Edge(int _v, int _value, int _next) : v(_v), value(_value), next(_next) {
	}
}edges[2][MAXM];

int head[2][MAXN], totEdge[2];
map <string, int> vertexMap;
int totVertex;
LL dist[2][MAXN];

void init() {
	totEdge[0] = totEdge[1] = 0;

	totVertex = 1;
	vertexMap.clear();
	memset(head, -1, sizeof(head));
	memset(dist, -1, sizeof(dist));
}

int getVertex(string name) {
	int v = vertexMap[name];
	if (!v) {
		v = totVertex++;
		vertexMap[name] = v;
	}
	return v;
}

void addEdge(string a, string b, int idx, int val) {
	int va = getVertex(a);
	int vb = getVertex(b);
	edges[idx][totEdge[idx]] = Edge(vb, val, head[idx][va]);
	head[idx][va] = totEdge[idx]++;
}

LL spfa(int s, int t, int idx) {
	dist[idx][s] = 0;
	queue <int> Q;
	Q.push(s);

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();

		for (int e = head[idx][u]; e != -1; e = edges[idx][e].next) {
			Edge &edge = edges[idx][e];
			int v = edge.v;

			if (dist[idx][v] == -1 || dist[idx][u] + edge.value < dist[idx][v]) {
				dist[idx][v] = dist[idx][u] + edge.value;
				Q.push(v);
			}
		}
	}
	return dist[idx][t];
}

int main() {
	int s, t;
	char a[20], b[20];
	while (scanf("%d %d", &n, &m) != EOF) {
		init();
		while (m--) {
			int v;
			scanf("%s %s %d", a, b, &v);
			addEdge(a, b, 0, v);
			addEdge(b, a, 1, v);
		}
		scanf("%s %s", a, b);
		s = getVertex(a);
		t = getVertex(b);
		LL d = spfa(s, t, 0);
		if (d == -1) {
			printf("-1\n");
		}
		else {
			spfa(t, s, 1);
			LL ans = -1;
			for (int i = 1; i <= n; ++i) {
				int u = i;
				for (int e = head[0][u]; e != -1; e = edges[0][e].next) {
					Edge &edge = edges[0][e];
					int v = edge.v;
					if (dist[0][u] != -1 && dist[1][v] != -1) {
						if (ans == -1 || dist[0][u] + edge.value / 2 + dist[1][v] < ans) {
							ans = dist[0][u] + edge.value / 2 + dist[1][v];
						}
					}
				}
			}
			printf("%I64d\n", ans);
		}
	}
	return 0;
}

/*
4 4
a b 20
b d 80
a c 1
c d 99
a d

4 4
a d 70
d b 70
a c 41
c b 100
a b

*/