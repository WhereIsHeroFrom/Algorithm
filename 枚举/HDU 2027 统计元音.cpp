// HDU 2027
// Ã¶¾Ù¡¢Í³¼Æ
#include <iostream>
using namespace std;

char str[200];
char yu[] = { 'a', 'e', 'i', 'o', 'u' };
int cnt[5];

int main() {
	int t;
	int i, j;
	bool f = false;
	scanf("%d", &t);
	getchar();
	while (t--) {
		if (f) { puts(""); }
		f = true;
		gets(str);
		for (i = 0; i < 5; ++i) cnt[i] = 0;
		for (i = 0; str[i]; ++i) {
			for (j = 0; j < 5; ++j) {
				if (str[i] == yu[j]) {
					++cnt[j];
					break;
				}
			}
		}
		for (i = 0; i < 5; ++i) {
			printf("%c:%d\n", yu[i], cnt[i]);
		}
	}
	return 0;
}