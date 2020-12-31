/*

	HDU 5627 Clarke and MST

	求一张无向图的 位与(&) 最大生成树

	从高往低枚举每一位：把所有那一位是1的边加到候选边集合中，然后用 Kruskal 求一次最小生成树；
		如果能够求出最小生成树，则对这些边继续筛选；
		如果不能求出，则用上一次的边；
*/


#include <iostream>

using namespace std;

#define MAXN 300010
#define MAXM 300010
#define MAXBIT 31

int f[MAXN];
unsigned int Pow2[MAXBIT + 1];

void init_set(int n) {
	for (int i = 1; i <= n; ++i) {
		f[i] = i;
	}
}

int find_set(int x) {
	return (f[x] == x) ? x : (f[x] = find_set(f[x]));
}

bool union_set(int x, int y) {
	int fx = find_set(x);
	int fy = find_set(y);
	if (fx != fy) {
		f[fx] = fy;
		return true;
	}
	return false;
}

struct Triple {
	int a, b, c;
	Triple() {}
	Triple(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {

	}

	void read() {
		scanf("%d %d %d", &a, &b, &c);
	}

	bool operator < (const Triple& t) {
		return c < t.c;
	}

}edges[2][MAXN];
int edgeCount[2];

bool Kruskal(int vertexCount, int idx) {
	init_set(vertexCount);
	int c = 0;
	for (int i = 0; i < edgeCount[idx]; ++i) {
		if (union_set(edges[idx][i].a, edges[idx][i].b))
		{
			++c;
		}
		if (c == vertexCount - 1) {
			return true;
		}
	}
	return false;
}

int main() {
	int t;
	int n, m;
	int i, j;

	for (i = 0; i <= MAXBIT; ++i) {
		Pow2[i] = (((unsigned int)1) << i);
	}

	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		
		edgeCount[0] = m;
		for (i = 0; i < edgeCount[0]; ++i) {
			edges[0][i].read();
		}

		int used = 1;
		unsigned int ans = 0;
		for (i = MAXBIT; i >= 0; i--) {
			edgeCount[used] = 0;
			for (j = 0; j < edgeCount[used ^ 1]; ++j) {
				if (Pow2[i] & edges[used ^ 1][j].c) {
					edges[used][edgeCount[used]++] = edges[used ^ 1][j];
				}
			}

			if (Kruskal(n, used)) {
				ans |= Pow2[i];
				used ^= 1;
			}
		}
		printf("%u\n", ans);
	}
	return 0;
}