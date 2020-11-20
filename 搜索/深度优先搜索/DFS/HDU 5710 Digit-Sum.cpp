#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 100100

int GCD(int a, int b) {
	return !b ? a : GCD(b, a%b);
}

int X, Y, A, B;
int stk[MAXN], tp;

void dfs(int sum, int tot) {
	int i;
	if (tot) {
		for (i = 9; i >= 5; --i) {
			if ((tot - 1) * 5 + i <= sum) {
				break;
			}
		}
		stk[tp++] = i;
		dfs(sum - i, tot - 1);
	}
	else {
		if (sum == 0) {
			for (i = tp - 1; i >= 0; --i) printf("%d", stk[i]);
			puts("");
			return;
		}
		if (sum >= 4) {
			stk[tp++] = 4;
			dfs(sum - 4, 0);
		}
		else {
			stk[tp++] = sum;
			dfs(0, 0);
		}
	}
}

int digit(int v) {
	int s = 0;
	while (v) {
		s += v % 10;
		v /= 10;
	}
	return s;
}


int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &X, &Y);
		if (2 * Y < X || Y > 5 * X) {
			printf("0\n");
		}
		else if (2 * Y == X) {
			printf("1\n");
		}
		else if (Y == 5 * X) {
			printf("5\n");
		}
		else {
			int A = 9 * Y;
			int B = 2 * Y - X;
			int G = GCD(A, B);
			A /= G;
			B /= G;
			int R = B;
			int PQ = A;
			//printf("%d %d\n", A, B);
			tp = 0;
			dfs(PQ, R);
		}
	}
	return 0;
}