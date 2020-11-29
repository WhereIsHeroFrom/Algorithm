#include <iostream>
#include <cmath> 
using namespace std;

#define LL long long

LL p, x;
LL a, b;
LL k;

LL Product_Mod(LL a, LL b, LL mod) {
	LL sum = 0;
	while(b) {
		if(b & 1) sum = (sum + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return sum;
}

void frac(LL lu, LL ld, LL ru, LL rd, LL& b, LL& k) {
	if( lu < ld && ru > rd) {
		b = 1;
		k = 1;
		//printf("%lld/%lld < %lld/%lld < %lld/%lld\n", lu, ld, b, k, ru, rd );
		return ;	
	}
	

	LL ud = lu / ld;
	frac(rd, ru - ud * rd, ld, lu % ld, b, k);
	LL tmp = k + ud * b;
	k = b;
	b = tmp; 
	
	//printf("%lld/%lld < %lld/%lld < %lld/%lld,   [ud=%lld]\n", lu, ld, b, k, ru, rd, ud);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld %lld", &p, &x);
		frac(p, x, p, x-1, b, k);
		//printf("%lld\n", b*x - k*p);
		a = Product_Mod(b, x, p);
		printf("%lld/%lld\n", a, b);
	}
	return 0;
}

/*
11111
100000000000007 10000000004
100000000000007 1000000004
100000000000007 100000004
100000000000007 10000004
100000000000007 1000004
100000000000007 100004
100000000000007 10004
100000000000007 1004
100000000000007 104
100000000000007 14

107 3

*/
