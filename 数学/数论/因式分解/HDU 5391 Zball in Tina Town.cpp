/*
	题意：求 (N-1)! MOD N   (2<=N<=10^9)
	
	题解：
	1） N = p，等于素数，则 答案为 p-1
	2） N = p^n， 等于素数的次幂 (n>1)，
		如果 (N-1)! 中有  p, 2p, 3p, np 则答案为0，那么就要满足：
			np <= p^n - 1 
	 	只有当 p=2， n=2 时，情况特殊，需要特殊处理，其它情况
		 	p^n - 1 > np 恒成立
	3） N = p1^n1 p2^n2 ... pk^nk，   
	 	一定可以找到素因子，使得 mod N 的值为 0 
	
*/



/*
Eratosthenes素数筛选
    利用素数的倍数必然是合数这个性质，从小到大枚举，标记所有合数。
Author: WhereIsHeroFrom
Update Time: 2018-3-19
Algorithm Complexity: O(n)
*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXP 31633
#define LL __int64

int primes[MAXP];
bool notprime[MAXP];

struct factor {
	int prime, count;
	factor() {
	} 
	factor(int p, int c) {
		prime = p;
		count = c;
	}
	void print() {
		printf("(%d, %d)\n", prime, count);
	}
};

// 厄尔多塞素数筛选法 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for(int i = 2; i < MAXP; i++) {
		if( !notprime[i] ) {
			primes[ ++primes[0] ] = i;
		    //需要注意i*i超出整型后变成负数的问题，所以转化成 __int64 
			for(LL j = (LL)i*i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// 因式分解 - 将n分解成素数幂乘积的形式
// 举例：
// 252 = (2^2) * (3^2) * (7^1) 
// 则 ans = [ (2,2), (3,2), (7,1) ]
void Factorization(int n, vector <factor>& ans) {
	ans.clear();
	if(n == 1) {
		return ;
	}
	if(n < MAXP) {
		if( !notprime[n] ) {
			ans.push_back( factor(n, 1) );
			return ;
		}
 	}
	// 素数试除 
	for(int i = 1; i <= primes[0]; i++) {
		if(n % primes[i] == 0) {
			factor f(primes[i], 0);
			while( !(n % primes[i]) ) {
				n /= primes[i];
				f.count ++;
			}
			ans.push_back(f);
			if(ans.size() > 1) {
				return ;
			}
		}
		if(n == 1) {
			return ;
		}
	}
	// 漏网之素数， 即大于MAXP的素数，最多1个 
	ans.push_back( factor(n, 1) );
}

int main() {
	Eratosthenes();
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		if(n == 4) {
			printf("2\n");
			continue;
		}
		vector <factor> ans;
		Factorization(n, ans);
		if(ans.size() == 1) {
			if(ans[0].count == 1) {
				printf("%d\n", n - 1);
			}else {
				printf("%d\n", 0);
			}
		}else {
			printf("0\n");
		}
	} 
	return 0;
}

