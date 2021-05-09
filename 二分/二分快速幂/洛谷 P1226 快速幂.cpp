#include <iostream>
#include <cstdio>

using namespace std;
 
#define ll long long

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

int main() {
    int a, b, c;
    while(scanf("%d %d %d", &a, &b, &c) != EOF) {
        printf("%d^%d mod %d=%d\n", a, b, c, Exp(a, b, c));
    }
    return 0;
}
