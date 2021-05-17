#include <iostream> 
#include <cstring>
using namespace std;

#define ll long long

const int MOD6 = 1e9+6;
const int MOD7 = 1e9+7;

ll Exp(ll a, ll n, ll Mod){
	ll ans = 1;
	if (a == 0 || a == 1) {
		return a % Mod;
	}
	while (n){
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

char c[100010];

int main() {
    while(scanf("%s", c) != EOF) {
        int len = strlen(c);
        ll s = 0;
        for(int i = 0; i < len; ++i) {
            s = s * 10 + (c[i] - '0');
            s %= MOD6;
        }
        s = s - 1 + MOD6;
        ll ans = Exp(2, s, MOD7);
        printf("%lld\n", ans);
    }
    
    return 0;
}
