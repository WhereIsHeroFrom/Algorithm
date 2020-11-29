#include <iostream>

using namespace std;

#define MAXN 1000010
#define LL __int64

int primes[MAXN], primescnt;
bool f[MAXN];

int EXP(int a, int b) {
	if (a == 1) {
		return 1;
	}
	if (a == -1) {
		return (b & 1) ? (-1) : 1;
	}
	return 0;
}

LL mod(LL a, LL b, LL c) {
	if (b == 0){
		return 1 % c;
	}
	return mod(a*a%c, b / 2, c) * (b & 1 ? a : 1) % c;
}

// 二次剩余存在与否的条件

int L(int a, int p) {
	if (a % p == 0) {
		return 0;
	}
	if (a >= p) {
		return L(a % p, p);
	}
	if (p == 2) {
		return 1;
	}

	if (mod(a, (p - 1) / 2, p) == 1) {
		// 二次剩余 
		return 1;
	}
	else if (mod(a, (p - 1) / 2, p) == p - 1) {
		// 二次非剩余 
		return -1;
	}
	return 0;
}

int J(int a, int n) {
	if (!f[n]) {
		return L(a, n);
	}
	if (a == 0) {
		return 0;
	}
	int ans = 1;
	for (int i = 0; i < primescnt; i++) {
		if (n % primes[i] == 0) {
			int cnt = 0;
			while (n % primes[i] == 0) {
				n /= primes[i];
				cnt++;
			}
			ans *= EXP(J(a, primes[i]), cnt);
			if (ans == 0) {
				break;
			}
		}
		if (!f[n]) {
			ans *= J(a, n);
			n = 1;
			break;
		}
	}
	return ans;
}

int a, n;
int main() {
	int i, j;
	f[0] = 1;
	f[1] = 1;
	for (i = 2; i < MAXN; i++) {
		if (!f[i]) {
			primes[primescnt++] = i;
			for (j = i + i; j < MAXN; j += i) {
				f[j] = 1;
			}
		}
	}
	while (scanf("%d %d", &a, &n) != EOF) {
		//for(a = 300000; a <= 1000000; a++) 
		//    for(n = 300001; n <= 1000000; n+=2)
		printf("%d\n", J(a, n));
	}

	return 0;
}
