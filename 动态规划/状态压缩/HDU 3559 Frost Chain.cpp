#include <iostream>

using namespace std;

#define MAXN 15
#define MAXM 5
#define inf -10000101

double dp[26][MAXM][1 << MAXN];
int hashv[26][MAXM][1 << MAXN], cases;
bool mat[MAXM][MAXM];
int cnt[MAXM][1 << MAXN];
int state_digit[MAXM][1 << MAXN];

int N, D;

int Sqr(int x) {
	return x*x;
}

struct Point {
	int x, y;
	void read() {
		scanf("%d %d", &x, &y);
		//x = y = 0;
	}
	int dist_sqr(Point other) {
		return Sqr(x - other.x) + Sqr(y - other.y);
	}
}P[MAXM];

bool invalid(int i, int j, int k) {
	return dp[i][j][k] < inf;
}

int HP[MAXM];
int pv[MAXM];
double ans[MAXM];

int getchange_state(int p, int state) {
	return state + (1 << pv[p]);
}

int getstate_digit(int p, int state) {
	if (state_digit[p][state] == -1)
		state_digit[p][state] = ((state >> pv[p] & 7));
	return state_digit[p][state];
}

double dfs(int time, int p, int state) {
	int i, j;
	double &dpv = dp[time][p][state];

	if (hashv[time][p][state] == cases) {
		return dpv;
	}
	hashv[time][p][state] = cases;
	dpv = 0;

	if (!time) {
		return 0;
	}

	// 从i的位置弹到p
	// prestate中，p的位置必须大于0
	for (i = 0; i < MAXM; ++i) {
		if (mat[i][p]) {
			int prestate = getchange_state(p, state);
			if (state_digit[p][prestate] > HP[p]) {
				continue;
			}
			double v = dfs(time - 1, i, prestate) / cnt[i][prestate];
			dpv += v;
			if (state_digit[p][prestate] == 1) {
				ans[p] += v;
			}
		}
	}
	return dpv;
}

int totalHP;

void enum_state(int time, int state, int idx, int useHP) {
	int i, j;

	if (idx == MAXM) {
		if (totalHP - useHP != time + 1) return;
		for (i = 0; i < MAXM; ++i) {
			dfs(time, i, state);
		}
		return;
	}
	for (i = HP[idx]; i >= 0; --i) {
		enum_state(time, state << 3 | i, idx + 1, useHP + i);
	}
}

int main() {
	int i, j, k;
	for (i = 0; i < MAXM; ++i) {
		pv[i] = (3 * MAXM - (3 * i + 3));
	}
	memset(state_digit, -1, sizeof(state_digit));
	for (int state = 0; state < (1 << MAXN); ++state) {
		for (j = 0; j < MAXM; ++j) {
			getstate_digit(j, state);
		}
	}

	while (scanf("%d %d", &N, &D) != EOF) {
		memset(mat, 0, sizeof(mat));
		totalHP = 0;
		for (i = 0; i < MAXM; ++i) {
			P[i].read();
		}
		for (i = 0; i < MAXM; ++i) {
			ans[i] = 0;
			for (j = 0; j < MAXM; ++j) {
				mat[i][j] = (i != j) && (P[i].dist_sqr(P[j]) <= D*D);
			}
		}
		for (i = 0; i < MAXM; ++i) {
			for (int state = 0; state < (1 << MAXN); ++state) {
				cnt[i][state] = 0;
				for (j = 0; j < MAXM; ++j) {
					if (mat[i][j] && state_digit[j][state]) cnt[i][state]++;
				}
			}
		}
		int start_state = 0;
		for (i = 0; i < MAXM; ++i) {
			scanf("%d", &HP[i]);
			//HP[i] = 5;
			totalHP += HP[i];
			start_state = start_state << 3 | HP[i];
		}
		++cases;

		for (i = 0; i < MAXM; i++) {
			dp[0][i][start_state - (1 << pv[i])] = 1.0 / MAXM;
			hashv[0][i][start_state - (1 << pv[i])] = cases;
			if (getstate_digit(i, start_state) == 1) {
				ans[i] += 1.0 / MAXM;
			}
		}

		for (i = 1; i <= N; i++) {
			enum_state(i, 0, 0, 0);
		}

		for (i = 0; i < MAXM; ++i) {
			if (i) printf(" ");
			printf("%.3lf", ans[i]);
		}
		puts("");
	}
	return 0;
}