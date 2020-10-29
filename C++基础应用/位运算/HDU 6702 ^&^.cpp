// HDU 6702
// 简单位运算原理
// 给定A和B，要求一个最小的C，使得 (A^C) & (B^C) 最小
// 
// A 和 B 的对应位总共两种情况：
// 1）全为1：       C的对应位提供1个1；
// 2）至少一个0：   C的对应位提供0；


#include <iostream>

using namespace std;

unsigned int A, B;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%u %u", &A, &B);
		unsigned int C = (A&B);
		if (C == 0) C = 1;
		printf("%u\n", C);
	}
	return 0;
}