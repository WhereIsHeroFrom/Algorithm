#include <iostream>

using namespace std;

const int mod = 1000000007;

/*

0  1  2  ...  2000000016  2000000017
2  1  3  ...      2           1        
*/
int main() {
	int i, t;
	int prepre = 2;
	int pre = 1;
	for(i = 2;;++i) {
		int now = (prepre + pre) % mod;
		if(pre == 2 && now == 1) {
			break;
		}
		prepre = pre;
		pre = now;
	}
	printf("%d\n", i);

	return 0;
} 
