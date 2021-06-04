#include <cstdio>
#include <iostream>
#include <cstring>
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


const int maxn = 5000010;
int a[maxn]; 
ll h[maxn]; 

template <class T>
inline void scan_d(T &ret) {
	char c; ret=0;
	while((c=getchar())<'0'||c>'9');
	while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
}




int main() {
    int n, p, k;
    while(scanf("%d %d %d", &n, &p, &k) != EOF) {
        for(int i = 1; i <= n; ++i) {
            scan_d(a[i]);
        }
        
        h[n+1] = 1;
        for(int i = n; i >= 1; --i) {
            h[i] = ( h[i+1] * a[i] );
            if(h[i] >= p) h[i] %= p;
        }
        ll ans = 0;
        ll kpre = 1, fpre = 1, fh;
        for(int i = 1; i <= n;++i) {
            fh = fpre * h[i+1];                if(fh >= p) fh %= p;
            fpre *= a[i];                      if(fpre >= p) fpre %= p;
            kpre = kpre * k;                   if(kpre >= p) kpre %= p;
            ans += kpre * fh;                  if(ans >= p) ans %= p;
        }
        ans = ans * Exp(h[1], p-2, p) % p;
        printf("%d\n", ans);
    }
    
    return 0;
}
