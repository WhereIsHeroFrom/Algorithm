/**************************************************|
|*                                                *|
|*         Rabin-Miller  &  Pollard-rho           *|
|*                                                *|
|**************************************************/
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
ll p[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

ll exp_gcd(ll a, ll b, ll &X, ll &Y) {
	ll q, temp;
	if (!b) {
		q = a; X = 1; Y = 0;
		return q;
	}
	else {
		q = exp_gcd(b, a % b, X, Y);
		temp = X;
		X = Y;
		Y = temp - (a / b) * Y;
		return q;
	}
}

// a * x % b = 1
// 求 x 
ll Inv(ll a, ll b) {
    ll X, Y;
    exp_gcd(a, b, X, Y);
    X = (X % b + b) % b;
    return X;
}

ll Gcd(ll a, ll b) {
	return !b ? a : Gcd(b, a%b);
}

//计算 a*b % mod
ll Produc_Mod(ll a, ll b, ll mod) {
	ll sum = 0;
	while (b) {
		if (b & 1) sum = (sum + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return sum;
}


//计算 a^b % mod
ll Power(ll a, ll b, ll mod) {
	ll sum = 1;
	while (b) {
		if (b & 1) sum = Produc_Mod(sum, a, mod);
		a = Produc_Mod(a, a, mod);
		b /= 2;
	}
	return sum;
}

//Rabin_Miller判素
bool Rabin_Miller(ll n) {
	ll i, j, k = 0;
	ll u, m, buf;
	// 1. 如果 n = 2，本身就是素数
	if (n == 2)
		return true;
	// 2. n==1 或者 n是偶数，则不是素数
	if (n < 2 || !(n & 1))
		return false;

	// 3. 将n-1分解为 m*2^k
	// n = m*2^k + 1
	m = n - 1;
	while (!(m & 1)) k++, m >>= 1;

	// 4. 试除10个素数
	for (i = 0; i < 10; i++) {
		// 4.1 n 在这些小素数当中
		if (p[i] >= n)
			return true;

		// 4.2 满足费马小定理，则跳过检测
		u = Power(p[i], m, n);
		if (u == 1)
			continue;

		// 4.3 
		for (j = 0; j < k; j++) {
			buf = Produc_Mod(u, u, n);
			if (buf == 1 && u != 1 && u != n - 1)
				return false;
			u = buf;
		}
		// 4.4 如果p[i]^(n-1) % n != 1 那么 n为合数
		if (u != 1)
			return false;
	}
	return true;
}

//寻找n的一个因子

ll Pollard_rho(ll n) {
	ll i = 1;
	ll x = rand() % (n - 1) + 1;
	ll y = x;
	ll k = 2;
	ll d;
	do{
		i++;
		d = Gcd(n + y - x, n);
		if (d > 1 && d < n)
			return d;
		if (i == k)
			y = x, k *= 2;
		x = (Produc_Mod(x, x, n) + n - 23) % n;
		if (x < 0) x += n;
	} while (y != x);
	return n;
}

void Factor(ll v, vector <ll>& ans) {
	if (v == 1) {
		return;
	}

	if (Rabin_Miller(v)) {
		ans.push_back(v);
		return;
	}
	ll f = Pollard_rho(v);

	Factor(f, ans);
	Factor(v / f, ans);
}

int main() {
    int t;
    ll n;
	scanf("%d", &t);
	while(t--) {
        scanf("%lld", &n);
        ll ans = n-1;
        for(ll i = n-1; ; --i) {
            if(Rabin_Miller(i)) {
                break;
            }else {
                ans = Produc_Mod(ans, Inv(i, n), n);
            }
        }
        printf("%lld\n", ans);
    }


	return 0;
}
