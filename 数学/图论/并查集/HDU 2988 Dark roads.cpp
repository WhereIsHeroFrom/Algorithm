#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 400000

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


int main() {
	int i;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		init_set(n);
		for (i = 0; i < m; ++i) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			T[i] = Triple(x, y, z);
		}
		sort(T, T + m);

		int ans = 0;
		for (i = 0; i < m; ++i) {
			if (!union_set(T[i].a, T[i].b)) {
				ans += T[i].c;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}