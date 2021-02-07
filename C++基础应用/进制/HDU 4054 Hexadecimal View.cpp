#include <iostream>
#include <cstring>

using namespace std;

char str[10000];
int tp;
char digit2Char[] = {
	"0123456789abcdef"
};

void addAddr(char *tl, int digit) {
	char tmp[6];
	tmp[0] = digit2Char[digit / 16 / 16 / 16 % 16];
	tmp[1] = digit2Char[digit / 16 / 16 % 16]; 
	tmp[2] = digit2Char[digit / 16 % 16];
	tmp[3] = digit2Char[digit % 16];
	tmp[4] = ':';
	tmp[5] = '\0';
	strcat(tl, tmp); 
}

char res[1000];

int main() {
	while(gets(str)) {
		int len = strlen(str);
		int cnt = (len + 15) / 16; 
		tp = 0; 
		for(int i = 0; i < cnt; ++i) {
			res[0] = '\0';
			addAddr(res, tp);						
			for(int j = i * 16; j < (i + 1)*16 && j < len; ++j) {
				char tmp[5];
				tmp[0] = digit2Char[ str[j] / 16 ];
				tmp[1] = digit2Char[ str[j] % 16 ];
				tmp[2] = '\0';
				if(j & 1) {
					
				}else {
					strcat(res, " ");
				}
				strcat(res, tmp);
			} 
			for(int d = strlen(res); d < 46; ++d) {
				res[d] = ' ';
			}
			res[46] = ' ';
			int now = 46;
			for(int j = i * 16; j < (i + 1)*16 && j < len; ++j) {
				if(str[j] >= 'a' && str[j] <= 'z') {
					res[now++] = str[j] - 'a' + 'A';
				}else if(str[j] >= 'A' && str[j] <= 'Z') {
					res[now++] = str[j] - 'A' + 'a';
				}else {
					res[now++] = str[j];
				}
			}
			res[now] = '\0';
			puts(res);
			tp += 16;
		}
		
	}	
	return 0;
} 
