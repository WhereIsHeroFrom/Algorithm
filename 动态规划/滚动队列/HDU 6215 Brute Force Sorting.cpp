#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

#define MAXN 100010

int n, A[MAXN];
int L[MAXN], R[MAXN];
int lookup[MAXN], lookupby[MAXN];
int hashv[MAXN];
int ans[MAXN];

void output() {
	int i, p = R[0];
	ans[0] = 0;
	while (p != n + 1) {
		ans[++ans[0]] = A[p];
		p = R[p];
	}
	printf("%d\n", ans[0]);
	for (i = 1; i <= ans[0]; ++i) {
		printf("%d ", ans[i]);
	}
	puts("");
}

struct InvPair {
	int s, t;
	InvPair();
	InvPair(int _s, int _t) : s(_s), t(_t) {
	}

	void Print() {
		printf("(%d,%d)=[%d, %d]\n", s, t, A[s], A[t]);
	}
};

queue <InvPair> Q[2];
int Max(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int i, j, k;
	int t;
	//freopen("in.txt", "r", stdin);
	//freopen("my_out.txt", "w", stdout);
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		R[0] = 1;
		memset(hashv, 0, sizeof(hashv));

		for (i = 1; i <= n; ++i) {
			scanf("%d", &A[i]);
			//A[i] = n - i/ 10000;
			L[i] = i - 1;
			R[i] = i + 1;
		}
		for (i = 0; i < 2; ++i) {
			while (!Q[i].empty()) {
				Q[i].pop();
			}
		}
		A[0] = -10000000;
		A[n + 1] = 10000000;
		for (i = 1; i <= n; i++) {
			for (j = i; j <= n; ++j) {
				if (A[j] <= A[j + 1]) {
					break;
				}
			}
			if (j != i) {
				Q[0].push(InvPair(i, j));
				i = j;
			}
		}
		int p = 0;
		while (!Q[p].empty()) {
			while (!Q[p].empty()) {
				InvPair ip = Q[p].front();
				Q[p].pop();

				//printf("%d\n", p);
				//ip.Print();



				if (R[ip.s] > ip.t) {
					ip.t = R[ip.s];
				}
				if (A[ip.s] <= A[ip.t]) {
					continue;
				}

				while (A[ip.t] > A[R[ip.t]]) {
					ip.t = R[ip.t];
				}

				while (!Q[p].empty()) {
					InvPair nex = Q[p].front();
					if (nex.s <= ip.t) {
						Q[p].pop();
					}
					else break;
				}
				R[L[ip.s]] = R[ip.t];
				L[R[ip.t]] = L[ip.s];

				if (A[L[ip.s]] > A[R[ip.t]]) {
					Q[p ^ 1].push(InvPair(L[ip.s], R[ip.t]));
				}

				//output();
			}
			p ^= 1;
		}
		output();
	}
	return 0;
}

/*
10
11
10 9 8 7 7 7 6 6 5 5 4

6
8 10 9 8 7 7
12
8 10 9 8 7 7 8 10 9 8 7 7

5
2 4 1 3 5

19
2 3 4 5 4 4 4 7 9 8 7 7 6 5 5 4 3 3 3

10
2 6 6 0 3 8 0 1 2 5
*/