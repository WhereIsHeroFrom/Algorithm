// HDU 2091
// ASCII ×Ö·û´®´¦Àí

#include <iostream>
#include <cstring>
using namespace std;

char str[100];
char Map[100][100];
int n;

int main() {
	int i, j;
	int t = 0;
	while (scanf("%s", str) != EOF && str[0] != '@') {
		if (t++) {
			puts("");
		}

		scanf("%d", &n);
		char c = str[0];
		memset(Map, 0, sizeof(Map));
		for (i = 0; i < 2 * n - 1; ++i) {
			Map[n - 1][i] = c;
		}
		int cnt = 1;
		for (i = n - 2; i >= 0; --i) {
			for (j = 0; j < 2 * n - 1; ++j) {
				if (j == cnt) {
					Map[i][j] = c;
				}
				else if (j == 2 * n - 2 - cnt) {
					Map[i][j] = c;
				}
				else if (j < 2 * n - 2 - cnt) {
					Map[i][j] = ' ';
				}
			}
			++cnt;
		}
		for (i = 0; i < n; ++i) puts(Map[i]);
	}
}