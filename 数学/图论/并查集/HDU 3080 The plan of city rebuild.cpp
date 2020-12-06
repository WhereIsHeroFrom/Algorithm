#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 40000

int f[MAXN];
int n, m;

void init_set(int n) {
	for (int i = 0; i < n; ++i) {
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

	bool operator < (const Triple& t) {
		return c < t.c;
	}

}T[MAXN];

int TotEdges;
int TotCitys;
int deserted[1000];

void init() {
	init_set(1000);
	TotEdges = 0;
	TotCitys = 0;
	memset(deserted, 0, sizeof(deserted));
}

int main() {
	int t;
	int l, n, m, e1, e2;
	int i;
	scanf("%d", &t);

	while (t--) {

		init();
		scanf("%d %d", &l, &e1);
		while (e1--) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			T[TotEdges++] = Triple(a, b, c);
		}
		scanf("%d %d", &n, &e2);
		while (e2--) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			T[TotEdges++] = Triple(a, b, c);
		}
		scanf("%d", &m);
		while (m--) {
			int h;
			scanf("%d", &h);
			deserted[h] = 1;
		}

		for (i = 0; i < n + l; ++i) {
			if (!deserted[i]) ++TotCitys;
		}

		sort(T, T + TotEdges);
		int cost = 0;
		int cnt = 0;
		for (i = 0; i < TotEdges; ++i) {
			if (deserted[T[i].a] || deserted[T[i].b]) continue;
			if (union_set(T[i].a, T[i].b)) {
				cost += T[i].c;
				++cnt;
				if (cnt == TotCitys - 1) {
					break;
				}
			}
		}

		if (cnt == TotCitys - 1) {
			printf("%d\n", cost);
		}
		else {
			printf("what a pity!\n");
		}

	}



	return 0;
}