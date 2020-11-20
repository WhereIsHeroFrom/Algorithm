#include <iostream>
#include <algorithm>
using namespace std;

#define LL __int64
#define MAXN 200000
#define MAXR 1500
#define MAXC 120

struct Info {
	int x, y;
	void read() {
		scanf("%d %d", &x, &y);
	}
	int getVal() {
		return 500 * x + 2 * y;
	}
};

int cmp(Info a, Info b) {
	if (a.x == b.x) return a.y > b.y;
	return a.x > b.x;
}

Info task[MAXN], machine[MAXN];
int startN, N, M;
int y[MAXN];

void process(int x) {
	int i;
	for (i = startN; i < N; i++) {
		if (machine[i].x >= x) {
			y[machine[i].y] ++;
		}
		else {
			startN = i;
			return;
		}
	}
	startN = N;
}

bool check(int sy) {
	int i;
	for (i = sy; i <= 100; i++) {
		if (y[i]) {
			y[i] --;
			return true;
		}
	}
	return false;
}

int main() {
	int i;
	while (scanf("%d %d", &N, &M) != EOF) {
		memset(y, 0, sizeof(y));
		startN = 0;
		for (i = 0; i < N; i++) {
			machine[i].read();
		}
		sort(machine, machine + N, cmp);
		for (i = 0; i < M; i++) {
			task[i].read();
		}
		sort(task, task + M, cmp);

		LL ans = 0;
		int v = 0;
		for (i = 0; i < M; i++) {
			process(task[i].x);
			if (check(task[i].y)) {
				v++;
				ans += task[i].getVal();
			}
		}
		printf("%d %I64d\n", v, ans);

	}
	return 0;
}