#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000010
#define MAXM 510

int C[MAXN];
int N;

int lowbit(int x) {
	return x & (-x);
}

void add(int x, int val) {
	while (x <= N) {
		C[x] += val;
		x += lowbit(x);
	}
}

bool sum(int x, int key) {
	int s = 0;
	while (x > 0) {
		s += C[x]; if (s >= key) return true;
		x -= lowbit(x);
	}
	return false;
}


int a[MAXM][MAXM];
int ans[MAXM][MAXM];
int v[250010];

int getIndex(int val) {
	int l = 1, r = N;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (v[mid] == val) return mid;
		if (v[mid] > val) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
}

int getMid(int key) {
	int l = 1, r = N;
	int ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (sum(mid, key)) {
			r = mid - 1;
			ans = mid;
		}
		else {
			l = mid + 1;
		}
	}
	return ans;
}

int n, r;


int main() {
	int i, j, k;
	while (scanf("%d %d", &n, &r) != EOF && (n + r)) {
		int tmp = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				scanf("%d", &a[i][j]);
				//a[i][j] = i*j;
				v[++tmp] = a[i][j];
				// 500 150 7Ãë a[i][j] = i*j;
			}
		}
		N = 1;
		sort(v + 1, v + tmp + 1);
		for (i = 2; i <= tmp; i++) {
			if (v[i] != v[i - 1]) {
				v[++N] = v[i];
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				a[i][j] = getIndex(a[i][j]);
			}
		}

		for (i = 1; i <= N; i++) {
			C[i] = 0;
		}

		int m = (2 * r + 1)*(2 * r + 1) / 2 + 1;

		// ×óÉÏ½ÇµÄ 
		for (j = 0; j < 2 * r + 1; j++) {
			for (k = 0; k < 2 * r + 1; k++) {
				add(a[k][j], 1);
			}
		}

		for (i = 0; i + 2 * r < n; i++) {
			if (!(i & 1)) {
				for (j = 0; j + 2 * r < n; j++) {
					ans[i][j] = getMid(m);

					// ÓÒÒÆ 
					for (k = i; k < i + 2 * r + 1; k++) {
						if (j + 2 * r + 1 < n) {
							add(a[k][j], -1);
							add(a[k][j + 2 * r + 1], 1);
						}
					}
				}
				if (i + 2 * r + 1 != n) {
					// ÏÂÒÆ 
					for (j = n - 2 * r - 1; j < n; j++) {
						add(a[i][j], -1);
						add(a[i + 2 * r + 1][j], 1);
					}
				}
			}
			else {
				for (j = n - 2 * r - 1; j >= 0; j--) {
					ans[i][j] = getMid(m);

					// ×óÒÆ 
					for (k = i; k < i + 2 * r + 1; k++) {
						if (j > 0) {
							add(a[k][j + 2 * r], -1);
							add(a[k][j - 1], 1);
						}
					}
				}
				if (i + 2 * r + 1 != n) {
					// ÏÂÒÆ 
					for (j = 0; j < 2 * r + 1; j++) {
						add(a[i][j], -1);
						add(a[i + 2 * r + 1][j], 1);
					}
				}
			}
		}
		for (i = 0; i + 2 * r < n; i++) {
			for (j = 0; j + 2 * r < n; j++) {
				//if(j) printf(" ");
				printf("%d ", v[ans[i][j]]);
			}
			puts("");
		}
	}
	return 0;
}

/*
5 1
1 2 3 4 6
7 6 4 3 2
5 4 6 3 7
9 0 9 1 1
3 4 5 2 1
*/