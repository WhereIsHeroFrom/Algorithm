// HDU 2034
// 组合数学：集合的运算（差集）
// 枚举、STL 排序
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 1010

int from[MAXN], to[MAXN];
int sta[MAXN], staidx;

int main() {
	int n, m;
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for (i = 0; i < n; ++i) {
			scanf("%d", &from[i]);
		}
		for (i = 0; i < m; ++i) {
			scanf("%d", &to[i]);
		}
		staidx = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				if (from[i] == to[j]) {
					break;
				}
			}
			if (j == m) {
				sta[staidx++] = from[i];
			}
		}
		sort(sta, sta + staidx);
		if (staidx) {
			for (i = 0; i < staidx; ++i) {
				printf("%d ", sta[i]);
			}
			puts("");
		}
		else {
			printf("NULL\n");
		}
	}
	return 0;
}