#include <cstdio>
#include <iostream>

using namespace std;

#define ll long long

ll Exp(ll a, ll n, ll Mod){
	ll ans = 1;
	while (n){
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}

const int mod = 19260817;
const int maxn = 10010;
char a[maxn], b[maxn];

int numMod(char *v) {
    ll s = 0;
    for(int i = 0; v[i]; ++i) {
        s = (s * 10 + v[i] - '0') % mod;
    }    
    return s;
}

int Inv(int a, int p) {
    return Exp(a, p-2, p);
}

int main() {
    while(scanf("%s %s", a, b) != EOF) {
        int bb = numMod(b);
        if(bb == 0) {
            printf("Angry!");
            continue;
        }
        ll aa = numMod(a);
        int ans = Inv(bb, mod) * aa % mod;
        printf("%d\n", ans);
    }
    
    return 0;
}
