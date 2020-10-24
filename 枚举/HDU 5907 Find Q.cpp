// HDU 5907
// Find Q

#include <iostream>

using namespace std;

char str[100010];
__int64 Q, q;


int main() {
	int t, i, j;
	scanf("%d", &t);

	while (t--) {
		Q = 0;
		q = 0;
		scanf("%s", str);
		for (i = 0; str[i]; ++i) {
			if (str[i] == 'q') {
				q = 1;
				for (j = i + 1; str[j] == 'q'; ++j) {
					++q;
				}
				Q += q*(q + 1) / 2;
				i = j - 1;
			}
		}
		printf("%I64d\n", Q);
	}
	return 0;
}