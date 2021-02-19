/*
	题意：给定 n (2 <= n <= 200000) 和 k (2 <= k <= 30) 
	求一个集合是否存在；
	这个集合满足两个条件：
	1）集合的元素和等于 n；
	2）集合的元素个数等于 k；
	3）k-1个集合元素的和等于一个平方数；
	4）集合元素各不相同；
	
	
	题解：
	
	首先，对于 k-1 个元素加和是平方数，可以枚举所有小于等于 n 的平方数 x^2 
	令 g = n - x^2
	那么现在就是要将 x^2 分解成 k-1 个不同的正整数，且不包含 g；
	
	k-1 个不同正整数（不包含 g）的和的最小值 s 为：
	if (g > k-1) {
		s = (1 + k-1) * (k-1) / 2;
	}else {
		s = (1 + g-1) * (g-1) / 2;
		s += (g+1 + k) * (k-g) / 2; 
	}
	
	只要 x^2 >= s 则定有办法组合出来，只要把最大的那个数不断扩大直到适应等于 x^2 即可； 
	注意 1,2,3,4,k-1,g  这种情况的时候 x2 = s+1 时是无法再往上扩展的	
	
*/

#include <iostream>

using namespace std;

#define ll long long 

int main() {
	int n, k;
	
	while(scanf("%d %d", &n, &k) != EOF) {
		ll s = 0;
		bool f = 0;
		for(int x = 1; ; x++) {
			int x2 = x*x;
			if(x2 >= n) {
				break;
			}
			ll g = n - x2;
			if(g >= k) {
				s = k*(k-1) / 2; 
				if(x2 < s) {
					continue;
				} 
				if(x2 == s) {
					f = 1;
					break;
				}
				if(x2 == s + 1) {
					// 1,2,3,4,k-1,g  这种情况的时候 x2 = s+1 时是无法再往上扩展的		
					if(g != k) {
						f = 1;
						break;					
					}
				}else {
					f = 1;
					break;
				}
			}else {
				s = g * (g-1) / 2;
				s += (g+k+1) * (k-g) / 2;	
				
				// 只需要把最大的数继续往上扩 
				if(x2 >= s) {
					f = 1;
					break;
				}	
			}
		}
		printf("%s\n", f ? "YES" : "NO");
	}
	
	return 0;
} 

/*
2 2



3 2
4 2
... 2

6 3

10 4

*/
