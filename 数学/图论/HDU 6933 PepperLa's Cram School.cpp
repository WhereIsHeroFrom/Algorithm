/*
题意：N个点，两两距离相等，但是边一开始都是不通的，只有边连通才能通行；
任意两点间的最短距离给出，求至少需要让多少条边连通；

图论：因为任意两个点举例相等，所以给出的最短距离图必然是有GCD >= 1的，
换言之，给出的距离中最小的两个点，他们之间的边必然要打通；
然后只要统计最小的边即可，因为是双向图，所以最后答案 / 2；

*/

#include <iostream>

using namespace std;

#define MAXN 1010

int n;
int Map[MAXN][MAXN];

int main() {
	int i, j;
	int cnt;
	while (scanf("%d", &n) != EOF) {
		int Min = 10000000, cnt = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%d", &Map[i][j]);
				if (i == j) continue;
				if (Map[i][j] < Min) {
					Min = Map[i][j];
					cnt = 1;
				}
				else if (Map[i][j] == Min) {
					++cnt;
				}
			}
		}
		printf("%d\n", cnt / 2);
	}

	return 0;
}

/*
5
0 1 2 1 1
1 0 3 2 2
2 3 0 1 2
1 2 1 0 1
1 2 2 1 0
*/