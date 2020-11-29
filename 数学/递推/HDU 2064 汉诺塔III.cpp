// HDU 2064
// 简单动态规划、数学递推
// f(n) 代表n个盘子从最左边移动到最右边的次数
// 那么先把 f(n-1) 移动过去，然后大盘移动到中间+1，再把f(n-1)移动回来，再把大盘移动到最右边，再把f(n-1)移动过去，完成；
// 所以，f(n) = 3*f(n-1) + 2， 其中 f(0) = 0;

#include <iostream>
#include <cstring>
using namespace std;

#define LL __int64
#define MAXN 40

LL f[100];

int main() {
	int i;
	int n;
	f[0] = 0;
	for (i = 1; i < MAXN; ++i) f[i] = f[i - 1] * 3 + 2;
	while (scanf("%d", &n) != EOF) {
		printf("%I64d\n", f[n]);
	}

}