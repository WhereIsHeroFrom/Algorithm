// HDU 2072
// 字符串处理
// STL map 的应用

#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>

using namespace std;

char str[100000];
char tmp[10000];
std::map <string, int> Map;

int main() {
	int i, j;
	while (gets(str) && str[0] != '#') {
		Map.clear();
		int idx = 0;
		for (i = 0; str[i]; ++i) {
			if (str[i] != ' ') {
				idx = 0;
				for (j = i; str[j]; ++j) {
					if (str[j] == ' ') break;
					tmp[idx++] = str[j];
				}

				tmp[idx] = '\0';
				Map[tmp] = 1;
				if (str[j] == '\0') break;
				i = j - 1;
			}
		}
		printf("%d\n", Map.size());
	}

	return 0;
}