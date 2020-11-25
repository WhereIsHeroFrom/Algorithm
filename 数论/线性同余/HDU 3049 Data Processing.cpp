#include <iostream>

using namespace std;

#define LL long long
#define MOD 1000003

// 扩展欧几里得
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
	LL q, temp;
	if (!b) {
		q = a; X = 1; Y = 0;
		return q;
	}
	else {
		q = ExpGcd(b, a % b, X, Y);
		temp = X;
		X = Y;
		Y = temp - (a / b) * Y;
		return q;
	}
}

int Pow2Mod[40010];

int main() {
	int t, cas = 0;
	int n;
	LL X, Y;
	Pow2Mod[0] = 1;
	for (int i = 1; i <= 40000; ++i) {
		Pow2Mod[i] = Pow2Mod[i - 1] * 2 % MOD;
	}
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		ExpGcd(n, MOD, X, Y);
		X = (X % MOD + MOD) % MOD;
		LL s = 0;
		for (int i = 0; i < n; ++i) {
			int v;
			scanf("%d", &v);
			s = s + Pow2Mod[v];
			if (s >= MOD) s -= MOD;
		}
		s = s * X % MOD;
		printf("Case %d:%lld\n", ++cas, s);
	}

	return 0;
}