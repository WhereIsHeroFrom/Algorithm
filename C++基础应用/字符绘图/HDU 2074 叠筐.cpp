// HDU 2074 
// ×Ö·û´¦Àí

#include <iostream>
#include <cstring>
using namespace std;

char str1[100], str2[100];
int L;
char Map[100][100];


int main() {
	int i, j;
	int t = 0;
	while (scanf("%d %s %s", &L, str1, str2) != EOF)  {
		if (t++) puts("");
		memset(Map, 0, sizeof(Map));
		int idx = 0;
		char c;
		for (i = L; i >= 1; i -= 2) {
			if ((idx + L / 2) & 1) {
				c = str2[0];
			}
			else {
				c = str1[0];
			}

			for (j = idx; j < L - idx; ++j) {
				Map[j][idx] = c;
			}
			for (j = idx; j < L - idx; ++j) {
				Map[j][L - 1 - idx] = c;
			}


			for (j = idx; j < L - idx; ++j) {
				Map[idx][j] = c;
			}
			for (j = idx; j < L - idx; ++j) {
				Map[L - 1 - idx][j] = c;
			}
			idx++;
		}
		if (L > 1) {
			Map[0][0] = ' ';
			Map[0][L - 1] = ' ';

			Map[L - 1][0] = ' ';
			Map[L - 1][L - 1] = ' ';
		}


		for (i = 0; i < L; ++i) puts(Map[i]);

	}
	return 0;
}