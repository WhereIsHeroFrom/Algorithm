/*
	题意：给出一个 K 和 一个字符串 S (len(S), K <= 10^6 )
	问有多少子串满足串中所有字母都不大于 K。
	 
	题解：二分答案 + 前缀和  
	
	枚举 子串起点，二分最大长度，统计；
	 
*/
#include <iostream>
#include <cstring>

using namespace std;

#define maxn 100005
 
int s[26][maxn];
char str[maxn];
int len;

bool check(int st, int ed, int k) {
	for(int i = 0; i < 26; ++i) {
		if(s[i][ed] - s[i][st-1] > k) return false;
	}
	return true;
}

int main() {
	int i;
	int k;
	int t;
	scanf("%d", &t);
	while( t-- ) {
		
		scanf("%s", &str[1]);
		scanf("%d", &k);
		len = strlen( &str[1]);
		for(i = 1; i <= len; ++i) {
			for(int j = 0; j < 26; ++j) {
				s[j][i] = s[j][i-1] + ( (str[i] == j+'a') ?1:0);
			}	
		}
		long long max = 0;
		for(i = 1; i <= len; ++i) {
			int l = i, r = len;
			int ans = -1;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(check(i, mid, k)) {
					ans = mid;
					l = mid + 1;
				}else {
					r = mid - 1;
				}
			} 
			max += ans - i + 1;
		}
		printf("%lld\n", max);
	}
	return 0; 
} 
