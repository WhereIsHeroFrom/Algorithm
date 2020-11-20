#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define MAXN 1000010
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



char str[MAXN];
int N, K, L;

#define MAXL 110

// dp[i][j][k] 表示可以选择的子串集合为 [1-i]，并且选择个数为j个，组成的长度为k 的方案是否可行。
bool dp[MAXL][MAXL][MAXL];
int lenCnt[MAXL];

int main() {
	int t;
	int i, j, k, c;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d %d", &N, &K, &L);
		for (i = 1; i <= L; ++i) lenCnt[i] = 0;
		for (i = 0; i < N; ++i) {
			scanf("%s", str);
			ManacherPre(str);
			Manacher(str);
			for (j = 0; str[j]; ++j) {
				int len = p[j] - 1;
				if (len & 1) {
					for (k = 1; k <= len; k += 2) lenCnt[k] ++;
				}
				else {
					for (k = 2; k <= len; k += 2) lenCnt[k] ++;
				}
			}
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		bool flag = false;
		for (i = 1; i < L; ++i) {
			if (flag) {
				break;
			}
			int ncnt = lenCnt[i];

			for (j = 0; j <= K; ++j) {
				for (k = 0; k <= L; ++k) {
					bool &v = dp[i][j][k];

					for (c = 0; c <= ncnt && c <= j; ++c) {
						int prek = k - c*i;
						if (prek < 0) break;
						v |= (dp[i - 1][j - c][prek]);
						if (v) break;
					}

					if (j == K && k == L && v) {
						flag = 1;
						break;
					}
				}
			}
		}
		printf("%s\n", flag ? "True" : "False");
	}
	return 0;
}