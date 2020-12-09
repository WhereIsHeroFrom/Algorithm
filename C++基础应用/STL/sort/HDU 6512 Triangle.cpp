#include <iostream>
#include <algorithm>
using namespace std;

int n;
int v[5000010];

int main() {
	int i;
	while (scanf("%d", &n) != EOF) {
		for (i = 0; i < n; ++i) {
			scanf("%d", &v[i]);
		}
		sort(v, v + n);
		bool f = false;
		for (i = 2; i < n; ++i) {
			int c = v[i], b = v[i - 1], a = v[i - 2];
			if (a + b > c) {
				f = true;
				break;
			}
		}
		printf("%s\n", f ? "YES" : "NO");
	}
	return 0;
}