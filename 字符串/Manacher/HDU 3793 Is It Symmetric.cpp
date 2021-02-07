#include <iostream>
#include <cstring>
using namespace std;

char str[1000];

int main() {
	int i, j;
	while(scanf("%s", str) != EOF) {
		if(str[0] == '#') break;
		int len = strlen(str);
		int plen = len/2;
		for(i = 0; i < len; ++i) {
			for(j = 1; j <= plen; ++j) {
				int lidx = ((i - j) % len + len) % len;
				int ridx = ((i + j) % len + len) % len;
				if(str[lidx] != str[ridx]) {
					break;
				}
			}
			if(j > plen) {
				printf("YES %d\n", i);
				break;	
			}
		}
		if(i == len) puts("NO");
		
	}
	return 0;
} 
