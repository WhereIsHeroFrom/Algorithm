#include <iostream>
#include <cstring>

using namespace std;

char str[2][100];
int val[2];
int pow10[10];

int main() {
	pow10[0] = 1;
	for(int i = 1; i < 10; ++i) {
		pow10[i] = pow10[i-1] * 10;
	}
	
	while(scanf("%s %s", str[0], str[1]) != EOF) {
		for(int i = 0; i < 2; ++i) {
			val[i] = 0;
			int p = 0;
			int len = strlen(str[i]);
			for(int j = len-1; j >= 0; --j) {
				if(str[i][j] == ',') continue;
				if(str[i][j] == '-') {
					val[i] = -val[i]; 
					break;
				}
				val[i] += pow10[p++] * (str[i][j] - '0');
			}					
		}		 
		printf("%d\n", val[0] + val[1]);
	}
	return 0;
} 
