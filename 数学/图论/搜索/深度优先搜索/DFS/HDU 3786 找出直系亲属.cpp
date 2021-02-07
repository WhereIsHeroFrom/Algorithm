#include <iostream>
#include <cstring>

using namespace std;

int n, m;
int l[256], r[256];
char str[100];
int stk[1000], tp;
char ans[1000000];

bool dfs(int now, int target) {
	if(now == target) {
		return true;
	}

	if(l[now] != -1) {
		stk[tp++] = 0;	
		if( dfs(l[now], target) ) {
			return true;
		}
		--tp;
	}
	if(r[now] != -1) {
		stk[tp++] = 1;
		if( dfs(r[now], target) ) {
			return true;
		}
		--tp;
	}
	return false;
}

bool findfather(char a, char b) {
	int i;
	tp = 0;
	ans[0] = '\0';
	bool find = dfs(a, b);
	
	for(i = 0; i < tp - 2; ++i) {
		strcat(ans, "great-");
	}
	if(tp >= 2) {
		strcat(ans, "grand");
	}
	if(tp >= 1) {
		strcat(ans, "parent");
	}
	
	return find;
}

bool findchild(char a, char b) {
	int i;
	tp = 0;
	ans[0] = '\0';
	bool find = dfs(a, b);
	
	for(i = 0; i < tp - 2; ++i) {
		strcat(ans, "great-");
	}
	if(tp >= 2) {
		strcat(ans, "grand");
	}
	if(tp >= 1) {
		strcat(ans, "child");
	}
	
	return find;
}

void getans(char a, char b) {
	if( !findfather(b, a) ) {
		if( !findchild(a, b) ) {
			ans[0] = '-';
			ans[1] = '\0';
		}
	}
}
int main() {
	while(scanf("%d %d", &n, &m) != EOF && (n||m) ) {
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		while(n--) {
			scanf("%s", str);
			if(str[1] != '-') {
				l[ str[0] ] = str[1];
			}
			if(str[2] != '-') {
				r[ str[0] ] = str[2];
			}
		}
		while(m--) {
			scanf("%s", str);
			getans(str[0], str[1]);
			puts(ans);
		}
	}
	return 0;
} 

/*
3 10
ABC
CDE
EFG
FA
BE
*/
