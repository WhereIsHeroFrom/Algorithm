#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

int n;

struct Pop {
	char name[20];
	int v;
	void read() {
		scanf("%s %d", name, &v);
	}

	void print() {
		printf("%s", name);
	}
	bool operator<(const Pop& other) {
		return v > other.v;
	}
}P[MAXN];


int main() {
	int t;
	int i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			P[i].read();
		}
		sort(P, P + n);
		for (i = 0; i < n; ++i) {
			if (i) printf(" ");
			P[i].print();
		}
		puts("");
	}
	return 0;
}