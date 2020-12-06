#include <iostream>

using namespace std;

char str[110];

int main() {
	int t, n, i;
	scanf("%d", &t);

	while (t--) {

		scanf("%d", &n);
		double all = 0;
		for (i = 0; i < n; ++i) {
			scanf("%s", str);
			strcat(str, "-");
			int idx = 0;
			__int64 sum = 0, s = 0;

			while (str[idx]) {
				if (str[idx] == '-') {
					sum += s;
					s = 0;
				}
				else {
					s = s * 10 + str[idx] - '0';
				}
				++idx;
			}
			all += 1.0 / sum;
		}
		if (all > 0) {
			all = 1 / all;
		}
		printf("%.2lf\n", all);
	}
	return 0;
}