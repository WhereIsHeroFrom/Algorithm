#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100010
#define LL __int64

#define PRE 0
#define POST 1

int c[2][MAXN];
int a[MAXN];
int n, m;

int lowbit(int x) {
	return x&-x;
}

void add(int tp, int x, int v) {
	while (x <= n) {
		c[tp][x] += v;
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
	int t, i;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		for (i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			c[PRE][i + 1] = c[POST][i + 1] = 0;
		}

		LL minv, inv = 0;
		for (i = m; i < n; i++) {
			inv += sum(POST, n) - sum(POST, a[i]);
			add(POST, a[i], 1);
		}
		minv = inv;
		//printf("%d\n", (int)inv);
		for (i = 0; i + m < n; i++) {

			add(POST, a[i + m], -1);
			inv += sum(POST, a[i] - 1) - sum(POST, a[i + m] - 1);

			if (a[i] < a[i + m]) {
				inv += sum(PRE, a[i + m]) - sum(PRE, a[i]);
			}
			else {
				inv -= sum(PRE, a[i]) - sum(PRE, a[i + m]);
			}

			add(PRE, a[i], 1);
			//printf("%d\n", (int)inv);

			if (inv < minv) {
				minv = inv;
				//if(!minv) break;
			}
		}
		printf("%I64d\n", minv);
	}
	return 0;
}

/*
8 2
1 5 4 2 2 1 3 3
*/