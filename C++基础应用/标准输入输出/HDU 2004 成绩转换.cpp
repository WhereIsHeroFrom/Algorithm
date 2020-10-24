// HDU 2004
// C语言基础函数应用
// 简单逻辑判断和标准输入输出
#include <iostream>
#include <cmath>
using namespace std;

int v;

int main() {
	while (scanf("%d", &v) != EOF) {
		if (v < 0 || v>100) {
			printf("Score is error!\n");
		}
		else {
			if (v >= 0 && v <= 59) {
				printf("E\n");
			}
			else if (v == 100) {
				printf("A\n");
			}
			else{
				char c = 'D' - (v - 60) / 10;
				printf("%c\n", c);
			}
		}
	}
	return 0;
}
