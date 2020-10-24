// HDU 5908
// 枚举答案 + 哈希
// 枚举所有可能的 k，然后利用两个hash表；
// 前k个元素用1个哈希表，后面n-k个元素用第2个哈希表，每k个元素判断一次；

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100010

int Hash[2][MAXN];
int sta[MAXN];
int n, a[MAXN];

bool check(int per, int tot) {
	// per: 每段长度
	// tot: 总共几段
	memset(Hash, 0, sizeof(Hash));
	int i, j;

	// 第一段放在 Hash[0] 中
	for (i = 1; i <= per; ++i) {
		++Hash[0][a[i]];
	}

	for (i = 2; i <= tot; ++i) {
		// 第 i 段放到 Hash[1] 中
		for (j = 1; j <= per; ++j) {
			++Hash[1][a[(i - 1)*per + j]];
		}

		for (j = 1; j <= per; ++j) {
			if ((i - 1) * Hash[0][a[j]] != Hash[1][a[j]]) {
				return false;
			}
		}
	}
	return true;
}


int main() {
	int t;
	int i;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		sta[0] = 0;
		for (i = 1; i <= n; ++i) {
			if (n % i == 0) {
				if (check(i, n / i)) {
					sta[++sta[0]] = i;
				}
			}
		}

		for (i = 1; i <= sta[0]; ++i) {
			if (i > 1) printf(" ");
			printf("%d", sta[i]);
		}
		puts("");
	}
	return 0;
}