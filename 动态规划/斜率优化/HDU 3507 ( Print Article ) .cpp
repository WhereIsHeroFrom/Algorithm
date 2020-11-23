#include <iostream>

using namespace std;

#define LL __int64 
#define MAXN 500010
#define INF ((LL)INT_MAX*(LL)INT_MAX)

LL f[MAXN];
LL M;
LL s[MAXN], s2[MAXN];

// j < k
// 斜率满足 slope < 某个数，表示k这个决策更优 
double slope(int j, int k) {
	if (s[k] == s[j]) {
		return INF;
	}
	return 1.0*(f[k] - f[j] + s2[k] - s2[j]) / (s[k] - s[j]);
}

int n;
int Q[2 * MAXN], front, rear;

LL Min(LL a, LL b) {
	if (a == INF) return b;
	return a < b ? a : b;
}


int main() {
	int i, j;
	while (scanf("%d %d", &n, &M) != EOF) {
		f[0] = s[0] = s2[0] = 0;
		front = rear = 0;
		for (i = 1; i <= n; i++) {
			scanf("%I64d", &s[i]);
			s[i] += s[i - 1];
			s2[i] = s[i] * s[i];
		}

		// 第1个决策时0 这个位置 
		Q[rear++] = 0;
		bool useOpt = 1;
		for (i = 1; i <= n; i++) {
			while (useOpt && rear - front > 1) {
				if (slope(Q[front], Q[front + 1]) < 2 * s[i]) {
					front++;
				}
				else if (rear - front > 2 && slope(Q[rear - 3], Q[rear - 2]) > slope(Q[rear - 2], Q[rear - 1])) {
					Q[rear - 2] = Q[rear - 1];
					rear--;
				}
				else {
					break;
				}
			}
			f[i] = INF;
			//printf("%d\n", i);
			for (j = front; j <= front; j++) {
				int p = Q[j];
				//printf(", %d ", p);
				f[i] = Min(f[i], f[p] + (s[i] - s[p])*(s[i] - s[p]) + M);
			}
			Q[rear++] = i;
			//puts("");
		}
		printf("%I64d\n", f[n]);
	}
	return 0;
}

/*
12 6
4 5 3 2 1 6 3 2 1 1 7 2

12 11111
1 2 3 4 5 6 7 8 9 10 11 12

*/