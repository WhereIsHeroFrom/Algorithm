#include <iostream>

using namespace std;

char str[1010];

bool check(char *str) {
	int i, cnt = 0;
	int z = 0, j = 0, zpos, jpos;
	for(i = 0; str[i]; ++i) {
		if(str[i] == 'z') {
			++z;
			zpos = i;
		}
		if(str[i] == 'j') {
			++j;
			jpos = i;
		}
		++cnt;
	}
	// z 和 j 正好1个 
	if(z != 1 || j != 1) {
		return false;
	}
	if(zpos > jpos) {
		return false;
	}
	if(zpos + 1 == jpos) {
		return false;
	}
	int prez = zpos;
	int prej = jpos - zpos - 1;
	int lasto = cnt - jpos - 1;
	return prez * prej == lasto;
}

int main() {
	while(scanf("%s", str) != EOF) {
		printf("%s\n", check(str) ? "Accepted" : "Wrong Answer");
	}	
	
	return 0;
} 
