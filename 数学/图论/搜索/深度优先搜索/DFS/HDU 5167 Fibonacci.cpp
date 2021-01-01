/*
	深搜求解一个数能不能被斐波那契数列的数相乘得出 
*/

#include <iostream>

using namespace std;

int f[100], fsize;
int n;

bool dfs(int value, int idx) {
	if(value <= 1) {
		return true;
	}
	
	for(int i = idx; i < fsize; ++i ) {
		if(value % f[i] == 0) {
			if(dfs(value / f[i], i)) {
				return true;
			}
		}
	}	
	return false;
}

int main() {
	int t;
	int i;
	f[0] = 0; f[1] = 1;
	for(i = 2; i < 100; ++i) {
		f[i] = f[i-1] + f[i-2];
		if(f[i] > 1000000000) {
			fsize = i;
			break;
		}
		//printf("%d %d\n", i, f[i]);
	}
	scanf("%d", &t);
	
	while(t--) {
		
		scanf("%d", &n); 
		printf("%s\n", dfs(n, 3) ? "Yes" : "No");
	}
	
	return 0;
}
