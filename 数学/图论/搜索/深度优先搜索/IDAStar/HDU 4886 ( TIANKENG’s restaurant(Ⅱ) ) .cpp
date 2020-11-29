#include <iostream>

using namespace std;

#define MAXL 3000010

char S[MAXL];
int hash[MAXL], cases;
int stack[10], top;
int sLen;
int pow8[10];

int getVal(char c) {
	return c - 'A';
}

int getChar(int val) {
	return val + 'A';
}

void hashThis(int len) {
	int i;
	int sum = 0;
	for (i = 0; i < sLen; i++) {
		sum = sum << 3 | (S[i] - 'A');
		if (sum >= pow8[len]) {
			sum &= (pow8[len] - 1);
		}
		if (i >= len - 1)
			hash[sum] = cases;
	}
}

bool dfs(int hasv, int depth, int maxDepth) {
	if (depth == maxDepth) {
		return hash[hasv] != cases;
	}
	for (int i = 0; i < 8; i++) {
		stack[top++] = i;
		if (dfs(hasv << 3 | i, depth + 1, maxDepth)){
			return true;
		}
		top--;
	}
	return false;
}

int main() {
	int i, t;
	pow8[0] = 1;
	for (i = 1; i < 10; i++) pow8[i] = pow8[i - 1] * 8;

	scanf("%d", &t);
	while (t--) {
		scanf("%s", S);
		sLen = strlen(S);

		for (i = 1;; i++) {
			cases++;
			hashThis(i);
			top = 0;
			if (dfs(0, 0, i)) {
				break;
			}
		}
		for (i = 0; i < top; i++) {
			printf("%c", getChar(stack[i]));
		}
		puts("");
	}
	return 0;
}