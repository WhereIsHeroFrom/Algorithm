/*
题意:求1-N中包含49的数的个数（N <= 2^63-1）。

dp[i][0] 表示长度为i并且不含有49，且最高位不是9的数的个数；
dp[i][1] 表示长度为i并且不含有49，但是最高位是9的数的个数；
dp[i][2] 表示长度为i并且含有49的个数；

dp[1][0] = 9;
dp[1][1] = 1;
dp[1][2] = 0;

dp[i][0] = 9*dp[i-1][0] + 8*dp[i-1][1] + 0*dp[i-1][2];
dp[i][1] =   dp[i-1][0] +  dp[i-1][1]  + 0*dp[i-1][2];
dp[i][2] = 0*dp[i-1][0] +  dp[i-1][1] + 10*dp[i-1][2];

| 9 8 0  |
| 1 1 0  |
| 0 1 10 |
*/

#include <iostream>

using namespace std;

#define MAXL 30
#define LL unsigned __int64

LL dp[MAXL][3];

void init() {
	int i;
	dp[1][0] = 9; dp[1][1] = 1; dp[1][2] = 0;
	for (i = 2; i < MAXL; ++i) {
		dp[i][0] = 9 * dp[i - 1][0] + 8 * dp[i - 1][1] + 0 * dp[i - 1][2];
		dp[i][1] = dp[i - 1][0] + dp[i - 1][1] + 0 * dp[i - 1][2];
		dp[i][2] = 0 * dp[i - 1][0] + dp[i - 1][1] + 10 * dp[i - 1][2];
	}
}

char str[100];
int len;

LL num(int l) {
	LL v = 0;
	while (str[l]) {
		v = v * (LL)10 + str[l] - '0';
		l++;
	}
	return v + 1;
}

LL dfs(int pos) {
	LL ans = 0;
	int i;
	bool f = 0;
	int l = len - pos - 1;
	if (pos && str[pos - 1] == '4' && str[pos] == '9') {
		ans += num(pos + 1);
		f = 1;
	}
	if (l == 0) {
		return ans;
	}
	if (str[pos] != '0')
		ans += (LL)(str[pos] - '0') * dp[l][2];
	if (str[pos] > '4')
		ans += dp[l][1];
	return ans + (f ? 0 : dfs(pos + 1));
}

int main() {
	init();
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		len = strlen(str);
		printf("%I64u\n", dfs(0));
		/*int asn = 0;
		for(int i = 1; i < num(0); i++) {
		int v = i;
		while(v) {
		if(v % 100 == 49) {
		asn ++;
		break;
		}
		v /= 10;
		}
		}
		printf("%d\n", asn);*/
	}
	return 0;
}