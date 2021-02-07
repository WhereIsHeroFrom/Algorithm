#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 110;

char str[maxn];
int cnt[3];
int value[256];
char s[] = "ZOJ";

int main() {
	int n;
	
	value['Z'] = 0;
	value['O'] = 1;
	value['J'] = 2;
	
	while(scanf("%s", str) != EOF) {
		if(str[0] == 'E') break;
		int len = strlen(str);
		cnt[0] = cnt[1] = cnt[2] = 0;
		for(int i = 0; i < len; ++i) ++cnt[ value[ str[i] ] ];
	
		bool flag = 1;
		while(flag) {
			flag = 0;
			for(int i = 0; i < 3; ++i) {
				if(cnt[i]) {
					printf("%c", s[i]);
					-- cnt[i];
					flag = 1; 
				}
			}
		}
		
		puts("");
	}
	
	return 0;
}

