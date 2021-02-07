#include <iostream>
#include <cstring>

using namespace std;

int n;
int a[10000];
int has[1000000];

int main() {
	int i;
	while(scanf("%d", &n ) != EOF && n) {
		memset(has, 0, sizeof(has));
		int Max = 0;
		for(i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			int v = a[i];
			while(v != 1) {
				if(v & 1) {
					v = (3*v + 1) / 2;
				}else {
					v = v / 2;
				}
				//if(v > Max) Max = v;
				has[v] = 1;
			}
		}
		int hasprint = false;
		for(i = n-1; i >= 0; --i) {
			if(!has[ a[i] ]) {
				if(hasprint) {
					printf(" ");
				}
				hasprint = true;
				printf("%d", a[i]);
			}
		}
		puts("");
	}	
	return 0;
} 
