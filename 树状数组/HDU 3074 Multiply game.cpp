#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 50010
#define LL __int64
#define MOD 1000000007 

LL c[MAXN];
int pre[MAXN];
int n;

int lowbit(int x) {
	return x & -x;
}

void add(int x, LL v) {
	while (x <= n) {
		c[x] *= v;
		if(c[x] >= MOD) c[x] %= MOD;
		x += lowbit(x);
	}
}

LL sum(int x) {
	LL s = 1;
	while (x) {
		s *= c[x];
		if(s >= MOD) s %= MOD;
		x ^= lowbit(x);
	}
	return s;
}

LL GCD(LL a, LL b) {
	return b ? GCD(b, a%b) : a;
}

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

LL Inv(LL val) {
	LL X, Y;
	ExpGcd(val, MOD, X, Y);
	return ((X%MOD)+MOD)%MOD;
} 

int main() {
	int T;
	int i, val, q;
	int a, b;
	
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 1; i <= n; ++i) {
			c[i] = 1;
		}
		for(i = 1; i <= n; ++i) {
			LL v;
			scanf("%I64d", &v);
			val = ((v % MOD) + MOD) % MOD;
			add(i, val);
			pre[i] = val;
		}
		scanf("%d", &q);
		while(q--) {
			scanf("%d %d %d", &a, &b, &val);
			if(!a) {
				LL s1 = sum(val);
				LL s2 = Inv( sum(b-1) );
				int ans = (s1 * s2) % MOD;
				printf("%d\n", ans);
			}else {
				add(b, Inv(pre[b]));
				pre[b] = ( (val % MOD) + MOD ) % MOD;
				add(b, val);
			}
		}
	}
	return 0;
}

/*
1
6
1 2 3 4 5 6
9
0 3 6
1 3 7
0 3 6
1 4 6
0 3 6
1 5 9
0 3 6
1 6 1
0 3 6
 
1
6
-1 -2 -3 -4 -5 -6
9
0 3 5
1 3 7
0 3 6
1 4 6
0 3 6
1 5 9
0 3 6
1 6 1
0 3 6


1
6
1 0 1 0 1 0
9
0 1 1
0 2 3
0 4 6

*/
