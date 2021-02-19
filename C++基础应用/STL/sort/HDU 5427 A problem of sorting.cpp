#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char line[110];

struct Name {
	char name[110];
	int year;
	
	bool operator < (const Name& n) const {
		return year > n.year;
	}
}N[110];

int main() {
	int t, n, i, j;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		getchar();
		for(i = 0; i < n; ++i) {
			gets(line);
			int s = strlen(line);
			for(j = 0; j < s - 5; ++j) {
				N[i].name[j] = line[j];
			}
			N[i].name[j] = '\0';
			N[i].year = (line[j+1]-'0') * 1000 + (line[j+2]-'0') * 100 + (line[j+3]-'0') * 10 + (line[j+4]-'0');
		}
		sort(N, N + n);
		for(i = 0; i < n; ++i) {
			printf("%s\n", N[i].name);
		}

	}
	return 0;
} 
