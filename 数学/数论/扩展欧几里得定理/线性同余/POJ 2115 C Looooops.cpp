#include <iostream>
#include <cmath>
using namespace std;

#define LL __int64

LL gcd(LL a, LL b)
{
	LL m = 1;
	while (m != 0)
	{
		m = a%b;
		a = b;
		b = m;
	}
	return a;
}

LL exp_gcd(LL a, LL b, LL &x, LL &y)
{
	LL q, temp;
	if (b == 0)
	{
		q = a;
		x = 1;
		y = 0;
		return q;
	}
	else
	{
		q = exp_gcd(b, a % b, x, y);
		temp = x;
		x = y;
		y = temp - (a / b) * y;
		return q;
	}
}

LL a, b, c, d, k, w, x, y, A, B, C, X, Y;
LL f[100];
int main()
{
	while (scanf("%I64d %I64d %I64d %I64d", &a, &b, &c, &k) != EOF)
	{
		if (!a && !b && !c && !k)
			break;
		if (a == b)
		{
			printf("0\n");
			continue;
		}
		if (c == 0)
		{
			printf("FOREVER\n");
			continue;
		}


		A = (LL)1 << k;
		B = c;
		C = b - a;

		d = gcd(A, B);

		if (C % d)
		{
			printf("FOREVER\n");
			continue;
		}
		A /= d;
		B /= d;
		C /= d;

		exp_gcd(A, B, x, y);

		Y = C * y;
		if (Y <= 0)
		{
			Y += (1 + (-Y) / A) * A;
		}
		Y %= A;
		if (Y == 0)
			Y = A;
		printf("%I64d\n", Y);


	}
	return 0;
}