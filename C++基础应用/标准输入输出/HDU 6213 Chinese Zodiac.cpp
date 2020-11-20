
#include <iostream>
#include <cstring>
using namespace std;

char ani[][30] = {
	"rat", "ox", "tiger", "rabbit", "dragon", "snake",
	"horse", "sheep", "monkey", "rooster", "dog", "pig"
};

char str1[30], str2[30];

int getID(char *str1) {
	int i;
	for (i = 0; i < 12; ++i) {
		if (strcmp(str1, ani[i]) == 0) {
			return i;
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s %s", str1, str2);
		int id1 = getID(str1);
		int id2 = getID(str2);
		if (id1 == id2) {
			printf("12\n");
		}
		else {
			int ans = id2 - id1;
			if (ans < 0) ans += 12;
			printf("%d\n", ans);
		}

	}
	return 0;
}
