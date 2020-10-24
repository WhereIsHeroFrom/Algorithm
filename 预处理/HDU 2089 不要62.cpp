// HDU 2089
// ‘§¥¶¿Ì

#include <iostream>

using namespace std;

#define MAXN 1000010

int sum[MAXN];

int val(int v) {
	int now, last = -1;
	while (v) {

		now = v % 10;
		v /= 10;
		if (now == 4) return 0;
		if (now == 6 && last == 2) return 0;
		last = now;
	}
	return 1;
}

int main() {
	int i;
	for (i = 1; i < MAXN; ++i) {
		sum[i] = sum[i - 1] + val(i);
	}
	int s, t;
	while (scanf("%d %d", &s, &t) != EOF && (s || t)) {
		printf("%d\n", sum[t] - sum[s - 1]);
	}

	return 0;
}