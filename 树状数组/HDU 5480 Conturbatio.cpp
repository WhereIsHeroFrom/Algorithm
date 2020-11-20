#include <iostream>
#include <cstring>
using namespace std;

#define HOR 0
#define VER 1
#define MAXN 100100

int c[2][MAXN];
int has[2][MAXN], T;

int lowbit(int x) {
	return x & -x;
}

void add(int tp, int x, int val) {
	while (x < MAXN) {
		c[tp][x] += val;
		x += lowbit(x);
	}
}

int sum(int tp, int x) {
	int s = 0;
	while (x) {
		s += c[tp][x];
		x ^= lowbit(x);
	}
	return s;
}

int main() {
	int t;
	int n, m, K, Q;
	int i, j;

	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &n, &m, &K, &Q);
		memset(c, 0, sizeof(c));
		T++;
		while (K--) {
			int x, y;
			scanf("%d %d", &x, &y);
			has[HOR][y] = T;
			has[VER][x] = T;
		}

		for (i = 0; i < 2; i++) {
			for (j = 1; j < MAXN; j++) {
				if (has[i][j] == T) {
					add(i, j, 1);
				}
			}
		}

		while (Q--) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			int xdelta = sum(VER, x2) - sum(VER, x1 - 1);
			int ydelta = sum(HOR, y2) - sum(HOR, y1 - 1);

			if (xdelta < x2 - x1 + 1 && ydelta < y2 - y1 + 1) {
				printf("No\n");
			}
			else {
				printf("Yes\n");
			}
		}

	}
	return 0;
}
