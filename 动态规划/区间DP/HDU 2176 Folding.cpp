#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 150;
const int inf = -1;
const int mod = 1e9 + 7; 
#define ll long long

int f[maxn][maxn];
int p[maxn][maxn];

void init() {
	memset(f, inf, sizeof(f));
}
int n;
char c[maxn];

int atomlen[maxn][maxn];
char atom[maxn][maxn][maxn];
int split[maxn][maxn][maxn];
int digitlen[maxn];
bool match[maxn][maxn][maxn];
char digitstr[maxn][10];

#define maxc 1

int dfs(int l, int r) {
	
	if(l > r) {
		return 0;
	}
	
	int &val = f[l][r];
	if(val != inf) {
		return val;
	}
	val = atomlen[l][r];
	p[l][r] = -1;
	
	for(int k = l; k <= r; ++k) {
		int ans = dfs(l, k) + dfs(k+1, r);
		if(ans < val) {
			val = ans;
			p[l][r] = k;
		}
	}
	
	for(int kidx = 1; kidx <= split[l][r][0] && kidx <= maxc; ++kidx) {
		int k = split[l][r][kidx];
		int cnt = (r-l+1) / k;
		int v = dfs(l, l + k - 1);
		if(digitlen[cnt] + v + 2 < val) {
			val = digitlen[cnt] + v + 2;
			p[l][r] = -1 + (-k);
		}
	} 
	return val;
}

void genans(int l, int r, int pos, char *str) {
	if(l > r) {
		return ;
	}
	if(p[l][r] == -1) {
		strcpy(str + pos, atom[l][r]);
		return ;
	} 
	if(p[l][r] < 0) {
		int k = - (p[l][r] + 1);
		int cnt = (r-l+1) / k;
		strcpy(str + pos, digitstr[cnt] );
		pos += digitlen[cnt];
		strcpy(str + pos, "(");
		++pos;
		genans(l, l + k - 1, pos, str);
		pos += f[l][l+k-1];
		strcpy(str + pos, ")");
		++pos;
		return;
	}
	
	genans(l, p[l][r], pos, str);
	pos += f[l][ p[l][r] ];
	genans(p[l][r] + 1, r, pos, str);
}





void precalc() {
	memset(match, 0, sizeof(match));
	memset(split, 0, sizeof(split));
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			for(int k = 1; i+k-1 < n && j+k-1 < n; ++k) {
				if(c[i+k-1] != c[j+k-1]) {
					break;
				}
				if(c[i+k-1] == '(' || c[i+k-1] == ')') {
					break;
				}
				match[i][j][k] = 1;
			}
		}
	}
	
	for(int i = 0; i < n; ++i) {
		for(int j = i; j < n; ++j) {
			int len = j - i + 1;
			
			atomlen[i][j] = len;
			for(int k = 0; k <= j-i; ++k)
				atom[i][j][k] = c[i+k];
			atom[i][j][j-i+1] = '\0';
			
			for(int k = 1; k < len; ++k) {
				if(len % k == 0) {
					int t, cnt = len / k;
					for(t = 1; t < cnt; ++t) {
						if(!match[i][i + t*k ][k]) {
							break;
						}
					}
					if(t == cnt) {
						split[i][j][ ++split[i][j][0] ] = k;
						if(split[i][j][0] >= maxc)
							break;
					}
				}
			}
		}
	}
}

char ans[maxn];
int main() {
	int i;
	int t;
	memset(digitstr, 0, sizeof(digitstr));
	
	for(i = 1; i < 10; ++i) {
		digitlen[i] = 1;
		digitstr[i][0] = i + '0';
	}
	for(i = 10; i < 100; ++i) {
		digitlen[i] = 2;
		
		digitstr[i][0] = (i/10) + '0';
		digitstr[i][1] = (i%10) + '0';
	}
	digitlen[100] = 3;
	digitstr[100][0] = '1';
	digitstr[100][1] = '0';
	digitstr[100][2] = '0';
	
	while(scanf("%s", c)!= EOF) {
		init();
		n = strlen(c);
		precalc();
		
		dfs(0, n-1);
		memset(ans, 0, sizeof(ans));
		genans(0, n-1, 0, ans);
		printf("%s\n", ans);
	}	
	return 0;
}

/*
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
ASFAMFKASFKSJFKSGSAGPAAPFOPASOGEWGPFOSAPDOAPVOSAGPASFASKDPAKVSDLADSPFKASDFGHJKKLVCNMXJDFKMVBFODPSSCX

EDCBAAAAABAAAAACBAAAAABAAAAADCBAAAAABAAAAACBAAAAABAAAAAEDCBAAAAABAAAAACBAAAAABAAAAADCBAAAAABAAAAACBAAAAABAAAAA

gfABCDEABCDEABCDEABCDEfABCDEABCDEABCDEABCDEgfABCDEABCDEABCDEABCDEfABCDEABCDEABCDEABCDE
*/
