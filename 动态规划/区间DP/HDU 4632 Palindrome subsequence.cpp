#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1010;
const int mod = 10007;

char str[maxn];
int f[maxn][maxn][4];
int cas;
// 00 左右都不包含
// 01 包含右端点
// 10 包含左端点
// 11 左右端点都包含


int main() {
	int t;
	cas = 0;
	
	memset(f, 0x3f, sizeof(f));
	
	scanf("%d", &t);

	while (t--) {
		scanf("%s", str + 1);
		int len = strlen(str + 1);
		
		for(int i = 0; i < 4; ++i) {
			for(int j = 1; j <= len; ++j) {
				f[j][j-1][i] = 0;
				f[j][j][i] = (i==3) ? 1 : 0;
			}
		}
		
		
		for(int L = 2; L <= len; ++L) {
			for(int l = 1; l <= len; ++l) {
				int r = l + L - 1;
				if(r > len) break;
				for(int bit = 0; bit < 4; ++bit) {
					int val = 0;
					if (bit == 0) {
						val = (f[l+1][r-1][0] + f[l+1][r-1][1] + f[l+1][r-1][2] + f[l+1][r-1][3]);
					}
					else if (bit == 1) {
						val = f[l+1][r][1] + f[l+1][r][3];
					}
					else if (bit == 2) {
						val = f[l][r-1][2] + f[l][r-1][3];
					}
					else if (bit == 3) {
						if (str[l] == str[r]) {
							val = (f[l+1][r-1][0] + f[l+1][r-1][1] + f[l+1][r-1][2] + f[l+1][r-1][3]) + 1;
						}
					}
					f[l][r][bit] = val % mod;
				}
			}
		}
		
		int ans = (f[1][len][0] + f[1][len][1] + f[1][len][2] + f[1][len][3]) % mod;
		printf("Case %d: %d\n", ++cas, ans );
	}

	return 0;
}

/*
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*/ 
