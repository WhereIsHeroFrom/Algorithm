#include <iostream>

using namespace std;

#define LL long long

char str[100110];

int main() {
	int t, i;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", str);
		LL cnt = 0, ans = 0;
		for (i = 0; str[i]; ++i) {
			if (str[i] != 'q') {
				ans += cnt * (cnt + 1) / 2;
				cnt = 0;
			}
			else {
				++cnt;
			}
		}
		ans += cnt * (cnt + 1) / 2;
		printf("%lld\n", ans);
	}
	return 0;
}