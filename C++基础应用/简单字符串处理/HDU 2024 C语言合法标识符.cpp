// HDU 2024
// 分情况讨论:
// 1. 出现空格(或tab)非法
// 2. 首字符不能是数字
// 3. 中间不能出现空格
// 4. 字符集合只有 数字、_、大写字母、小写字母
#include <iostream>
using namespace std;

#define __UNDEFINE 100000
char str[100];

bool isnum(char c) {
	return c >= '0' && c <= '9';
}

bool is_space_or_tab(char c) {
	return c == ' ' || c == '\t';
}

bool judge_char(char c) {
	if (isnum(c)) return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	if (c == '_') return true;
	return false;
}

bool judge(const char* str) {
	int i;
	int s, t;
	s = __UNDEFINE;
	t = 0;
	for (i = 0; str[i]; ++i) {
		if (!is_space_or_tab(str[i])) {
			if (s == __UNDEFINE) {
				s = i;
			}
			t = i;
		}
		else {
			return false;
		}
	}
	// 全是空格
	if (s > t) {
		return false;
	}
	// 首字符不能是数字
	if (isnum(str[s])) {
		return false;
	}
	for (i = s; i <= t; ++i) {
		// 中间不能出现空格
		if (is_space_or_tab(str[i])) {
			return false;
		}
		if (!judge_char(str[i])) {
			return false;
		}
	}
	return true;
}

int main() {
	int t;
	scanf("%d", &t);
	getchar();
	while (t--) {
		gets(str);
		printf("%s\n", judge(str) ? "yes" : "no");
	}
	return 0;
}