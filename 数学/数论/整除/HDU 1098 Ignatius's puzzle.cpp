#include <iostream>

using namespace std;

const int mod = 65;
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
ll calModA(int x) {
    int n = Exp(x, 13, mod) * 5 % mod;
    int m = Exp(x, 5, mod) * 13 % mod;
    return (n + m) % mod; 
}

ll calModB(ll k, int x) {
    return k * x % mod;
}

bool allfit(int a, int k) {
    for(int x = 0; x < mod; ++x) {
        int v = calModA(x) + calModB(k, x) * a;
        if(v % mod) {
            return false;
        }
    }    
    return true;
}

int main() {
    int k;
    while(scanf("%d", &k) != EOF) {
        int f = 0;
        for(int a = 0; a < 65; ++a) {
            if( allfit(a, k) ) {
                printf("%d\n", a);
                f = 1;
                break;
            }
        }
        if(!f) printf("no\n");
    }
    
    return 0;
} 

 
