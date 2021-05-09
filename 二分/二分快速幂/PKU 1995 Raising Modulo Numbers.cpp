#include <iostream>

using namespace std;

__int64 mod(__int64 a, __int64 b, __int64 c)
{
	if(!b) return 1;
	__int64 p = mod( (a*a)%c, b/2, c);
	if(b & 1)
		return ( p * a ) % c;
	return p % c;
}

int z;
__int64 M, sum, a, b;
int r;

int main()
{
	scanf("%d", &z);

	while(z--)
	{
		scanf("%I64d", &M);
		scanf("%d", &r);

		sum = 0;

		while(r--)
		{
			scanf("%I64d %I64d", &a, &b);
			sum = ( sum + mod(a, b, M) ) % M;
		}
		printf("%I64d\n", sum);
	}
}
