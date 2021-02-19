/*
	题意：给定 1 <= a,b,c <= 10^6 ，求 ax+by = c 的解 (x,y) 的对数
	
	题解：线性同余
	1)  令 g = gcd(a, b)，如果 c % g != 0， 则无解，输出 0；否则，转 2 
	2)  a /= g, b /= g, c /= g;
	3)  利用扩展欧几里得找出最小正整数 X 满足  aX + by = c
	4)  所有满足等式的 x = X + kb (k = 0,1,2,3,...)
	y = [c - a(X + kb) ] / b = -ak + (c-aX)/b,     y是关于k的一次递减函数
	即当 k 越大，则 y 越小，为了保证 y > 0， 只需要  c - a(X + kb) > 0
		
		
		令 y0 = (-X * a + c) / b;
		满足 y0 > ak
		
		LL ans = 0; 
		
		if(y0 <= 0) {
			ans = 0;
		}else {
			if(y0 % a) {
				ans = y0 / a;
			}else {
				ans = y0 / a + 1;
			}
		}
*/
#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 100010

LL GCD(LL a, LL b) {
	return b ? GCD(b, a%b) : a;
}

// 扩展欧几里得
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
     LL q, temp;
     if( !b ) {
         q = a; X = 1; Y = 0;
         return q;
     }else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X; 
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
	 }
}

int main() {
	int t;
	scanf("%d", &t);
	
	while(t--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		LL X, Y;
		LL g = ExpGcd(a, b, X, Y); 
		
		if(c % g != 0) {
			printf("0\n");
			continue;
		}
		a /= g;
		b /= g;
		c /= g;
		X = ( (X % b) * c ) % b;
		if( X <= 0 ) {
			X += b;
		}
		// y0 > ak
		LL y0 = (-X * a + c) / b;

		LL ans = 0; 
		
		if(y0 <= 0) {
			ans = 0;
		}else {
			if(y0 % a == 0) {
				ans = y0 / a;
			}else {
				ans = y0 / a + 1;
			}
		}
		printf("%lld\n", ans);
		 
	}
	return 0;
} 
