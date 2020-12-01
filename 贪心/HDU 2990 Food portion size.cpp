#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1010
#define LL long long

int n, a, b;
int val[MAXN];
int has[MAXN];

struct Fraction {
	int u, d;
	Fraction() {
		u = 0;
		d = 1;
	}
	bool operator < (const Fraction& o) {
		return (LL)u * o.d < (LL)d * o.u;
	}

	void Print() {
		if (d == 1) {
			printf("%d\n", u);
		}
		else {
			printf("%d / %d\n", u, d);
		}
	}
};

int up(int x, int y) {
	return (x + y - 1) / y;
}

int gcd(int a, int b) {
	return !b ? a : gcd(b, a%b);
}

bool getAns(int u, int d, int a, int b, Fraction& ans) {
	int i;
	ans.u = 0;
	ans.d = d;
	for (i = 0; i < n; ++i) {
		int upval = up(val[i] * d, u);
		if (upval > 3) {
			return false;
		}
		ans.u += upval * b * d + (u * upval - d * val[i]) * a;
	}
	int g = gcd(ans.u, ans.d);
	ans.u /= g;
	ans.d /= g;
	return true;
}

int main() {
	int i, j;
	while (scanf("%d", &n) != EOF && n) {
		memset(has, 0, sizeof(has));
		scanf("%d %d", &a, &b);
		for (i = 0; i < n; ++i) {
			scanf("%d", &val[i]);
			has[val[i]] = 1;
		}
		Fraction ans;
		bool bfind = false;

		for (i = 1; i <= 100; ++i) {
			if (has[i]) {
				for (j = 1; j <= 3; ++j) {
					Fraction now;
					bool bFit = getAns(i, j, a, b, now);
					if (!bFit) {
						continue;
					}
					if (!bfind || now < ans) {
						ans = now;
						bfind = true;
					}
				}
			}
		}
		ans.Print();
	}


	return 0;
}

/*
5
1 1
3 7 1 9 12
3
10 1
11 13 17
2
2 3
6 3
0
*/