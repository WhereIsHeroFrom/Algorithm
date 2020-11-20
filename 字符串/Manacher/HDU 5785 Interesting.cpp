#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAXN 2000010
int p[MAXN];
char strTmp[MAXN];

int Min(int a, int b) {
	return a < b ? a : b;
}

void ManacherPre(char *str) {
	strcpy(strTmp, str);
	int i;
	for (i = 0; strTmp[i]; ++i) {
		str[2 * i] = '$';
		str[2 * i + 1] = strTmp[i];
	}
	str[2 * i] = '$';
	str[2 * i + 1] = '\0';
}

int Manacher(char *str) {
	int ct = 0, r = 0, maxLen = 1;
	p[0] = 1;
	for (int i = 1; str[i]; ++i) {
		// 1.计算p[i]初始值 
		if (i < r) {
			p[i] = Min(p[2 * ct - i], r - i);
		}
		else {
			p[i] = 1;
		}
		// 2.扩张p[i]，以适应达到p[i]最大值 
		while (i - p[i] >= 0 && str[i - p[i]] == str[i + p[i]])
			++p[i];

		// 3.更新ct
		if (p[i] + i > r) {
			ct = i;
			r = p[i] + i;
		}
		// 4.更新最长回文 
		if (2 * p[i] - 1 > maxLen) {
			maxLen = 2 * p[i] - 1;
		}
	}
	return maxLen;
}

#define MOD 1000000007
#define LL __int64

void add(int x, int max, int *c, int val) {
	if (x <= 0) {
		c[0] += val;

		// 用加减法代替取模，加速
		if (val < 0) {
			if (c[x] < 0) c[x] += MOD;
		}
		else {
			if (c[x] >= MOD) c[x] -= MOD;
		}
		return;
	}
	c[x] += val;

	// 用加减法代替取模，加速
	if (val < 0) {
		if (c[x] < 0) c[x] += MOD;
	}
	else {
		if (c[x] >= MOD) c[x] -= MOD;
	}
}

char str[MAXN];
int Sum[MAXN], Cnt[MAXN];
int L[MAXN], R[MAXN];

void smoothMod(int& v) {
	if (v < 0) {
		v += MOD;
	}
	else {
		if (v >= MOD) {
			v -= MOD;
		}
	}
}

void init() {
	memset(Sum, 0, sizeof(Sum));
	memset(Cnt, 0, sizeof(Cnt));
}

int main() {
	int i;
	while (scanf("%s", str) != EOF) {
		init();
		ManacherPre(str);
		Manacher(str);
		int len = strlen(str);
		int totalSum = 0, totalCnt = 0;
		// 统计左边的
		for (i = 1; i < len; ++i) {
			add(i, len, Cnt, 1);
			add(i + p[i], len, Cnt, -1);

			add(i, len, Sum, i);
			add(i + p[i], len, Sum, -i);

			totalSum += Sum[i]; smoothMod(totalSum);
			totalCnt += Cnt[i]; smoothMod(totalCnt);

			if (i & 1) {
				L[i] = ((LL)totalSum - (LL)totalCnt * (LL)(i - 1) / 2) % MOD;
				if (L[i] < 0) L[i] += MOD;
			}
		}
		init();
		LL s = 0;
		totalSum = 0, totalCnt = 0;
		// 统计右边的
		for (i = len - 2; i >= 1; --i) {
			add(i, len, Cnt, 1);
			add(i - p[i], len, Cnt, -1);

			add(i, len, Sum, i);
			add(i - p[i], len, Sum, -i);

			totalSum += Sum[i]; smoothMod(totalSum);
			totalCnt += Cnt[i]; smoothMod(totalCnt);

			if (i & 1) {
				int lidx = i - 2;

				R[i] = ((LL)totalSum - (LL)(totalCnt)* (LL)(i - 1) / 2) % MOD;
				if (R[i] < 0) R[i] += MOD;

				if (lidx >= 1) {
					s += (LL)R[i] * L[lidx];
					if (s >= MOD) s %= MOD;
				}
			}
		}

		printf("%d\n", int(s));
	}
	return 0;
}