/*
题意：n 个顶点的完全图，边权是顶点编号的最小公倍数，求整个图的最小生成树。
题解：最小生成树贪心算法是取每次最小的边，而1和所有顶点的最小公倍数最小，所以这棵树就是所有的顶点的都和1相连，边权就是：
S(n) = (2 + 3 + ... n);
*/

#include <iostream>

using namespace std;

#define LL __int64

int main() {
	int t, cas = 0;
	LL n;
	scanf("%d", &t);

	while (t--) {
		scanf("%I64d", &n);
		n = (n*n + n - 2) / 2;
		printf("Case #%d: %I64d\n", ++cas, n);
	}


	return 0;
}
