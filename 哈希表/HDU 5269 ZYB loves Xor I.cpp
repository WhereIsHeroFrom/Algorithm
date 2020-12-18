/*

HDU 5269 ZYB loves Xor I

题意：给定 N (N<=100000)个 [0,2^29] 的数 A[i]，对于任意的 i,j，求 sum{  lowbit( A[i] xor A[j] ) }

*/

#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 100010
#define LL long long
#define MAXBIT 29
#define MOD 998244353

LL Pow2[MAXBIT + 1];

void initPow2() {
	int i;
	for (i = 0; i <= MAXBIT; ++i) {
		Pow2[i] = ((LL)1 << i);
	}
}

#define HASHMOD ((1<<17)-1)
bool hashKey[HASHMOD + 1];
int hashValue[HASHMOD + 1];

int Hash(int val) {
	int s = (val & HASHMOD);
	while (1) {
		if (!hashKey[s]) {
			hashKey[s] = 1;
			hashValue[s] = val;
			return s;
		}
		else {
			if (hashValue[s] == val) {
				return s;
			}
			s = (s + 1) & HASHMOD;
		}
	}
}

int a[MAXN];
int valCount[HASHMOD];

LL getLowbitSum(int n) {
	int i, j;
	LL ans = 0;
	for (i = 0; i <= MAXBIT; ++i) {
		memset(hashKey, 0, sizeof(hashKey));
		memset(valCount, 0, sizeof(valCount));

		for (j = 0; j < n; ++j) {
			if (Pow2[i] & a[j]) continue;
			int hashID = Hash(a[j] & (Pow2[i] - 1));
			++valCount[hashID];
		}

		for (j = 0; j < n; ++j) {
			if (Pow2[i] & a[j])
			{
				int hashID = Hash(a[j] & (Pow2[i] - 1));
				ans += Pow2[i] * valCount[hashID];
				if (ans >= MOD) ans %= MOD;
			}
		}
	}
	ans = (ans * 2) % MOD;
	return ans;
}

int main() {
	initPow2();

	int t, i;
	int n, cas = 0;

	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		int ans = getLowbitSum(n);
		printf("Case #%d: %d\n", ++cas, ans);
	}

	return 0;
}