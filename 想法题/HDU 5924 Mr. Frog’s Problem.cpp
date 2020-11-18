/*
题意：A <= C <= B, A <= D <= B，满足   A/B+B/A <= C/D+D/C，求满足条件的 C 和 D；
题解：假设 C <= D，所以只有当 C == A 且  D == B 的时候才能满足情况；
分情况讨论：
1) A == B;
2) A > B;
3) A < B;
*/

#include <iostream>

using namespace std;

#define LL __int64

int main() {
	int t, cas = 0;
	LL A, B;
	scanf("%d", &t);

	while (t--) {
		scanf("%I64d %I64d", &A, &B);

		printf("Case #%d:\n", ++cas);
		if (A == B) {
			printf("1\n%I64d %I64d\n", A, B);
		}
		else if (A > B) {
			printf("0\n");
		}
		else {
			printf("2\n%I64d %I64d\n%I64d %I64d\n", A, B, B, A);
		}
	}


	return 0;
}
