/*
题意：求一个素数是不是两个立方数的差；
题解：p = a^3 - b^3 = (a-b)(a^2+ab+b^2)
=> a-b = 1, 带入得到：   p = ((b+1)^2+(b+1)b+b^2) = 3b^2 + 3b + 1

	二次函数求根公式

*/

#include <iostream>
#include <cmath>
using namespace std;

#define LL __int64

LL p;
bool isFit(LL p) {
	p = p * 12 - 3;
	LL v = int(sqrt(p*1.0) + 1e-6);
	if (v*v != p) {
		return false;
	}
	return (v - 3) % 6 == 0;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--){
		scanf("%I64d", &p);
		printf("%s\n", isFit(p) ? "YES" : "NO");
	}
	return 0;
}