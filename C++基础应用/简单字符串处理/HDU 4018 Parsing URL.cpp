#include <iostream>

using namespace std;

char str[100000];

int main() {
	int t, cas = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%s", str);
		int start = -1;
		int end = -1;
		
		for(int i = 0; str[i]; ++i) {
			if(str[i] == ':' && str[i+1] == '/' && str[i+2] == '/') {
				start = i + 3;
				i += 2;
			}else if(str[i] == ':') {
				end = i - 1;
				break;
			}else if(str[i] == '/') {
				end = i - 1;
				break;
			}
		}		
		printf("Case #%d: ", ++cas);
		for(int i = start; i <= end; ++i) {
			printf("%c", str[i]);
		}
		puts("");
	}
	return 0;
} 
