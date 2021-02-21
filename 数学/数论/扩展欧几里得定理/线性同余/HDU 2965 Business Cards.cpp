#include <iostream>

using namespace std;

#define LL long long

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

LL lcm(int a, int b) {
	return (LL)(a / gcd(a, b)) * b;
}

int Max(int a, int b) {
	return a > b ? a : b;
}

int Min(int a, int b) {
	return a < b ? a : b;
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

bool f(int l, int s, int w, int h) {
	if (w%l == 0 && h%s == 0) {
		return true;
	}


	LL L = lcm(l, s);
	if (w % L) {
		return false;
	}
	int g = gcd(l, s);
	if (h % g) {
		return false;
	}
	h /= g;
	l /= g;
	s /= g;
	LL X, Y;
	ExpGcd(l, s, X, Y);
	X = (X % s * h % s + s) % s;
	Y = ((LL)h - l*X) / s;
	return X >= 0 && Y >= 0;
}

bool fit(int a, int b, int c, int d) {
	return f(Max(a, b), Min(a, b), c, d)
		|| f(Max(a, b), Min(a, b), d, c);
}

int main() {

	int t;
	scanf("%d", &t);

	while (t--) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		printf("%s\n", fit(a, b, c, d) ? "YES" : "NO");
	}
	return 0;
}
