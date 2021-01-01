#include <iostream>

using namespace std;

#define ll long long
#define maxb 63

ll f[maxb + 1];

/*
	mask[62] = 1000000...       1      + 62个0
	mask[61] = 1100000...       11     + 61个0
	...
	mask[1]  = 11111...10       111... +  1个0
	mask[0]  = 11111...11       111... +  0个0 
*/

ll mask[maxb + 1];

ll Max (ll x, ll y) {
	return x > y ? x : y;
}

ll mid(int depth, ll l, ll r) {
	return (mask[depth] & r);
}

ll MaxV;

ll dfs(int depth, ll a, ll b, ll c, ll d, ll ans) {
	if(depth == -1) {
		if(ans > MaxV) {
			MaxV = ans;
		}
		return ans;
	}
	
	//printf("%d %lld %lld %lld %lld %lld\n", depth, a, b, c, d, ans);
	
	bool ab = ( (a & mask[depth]) == (b & mask[depth]) );
	bool cd = ( (c & mask[depth]) == (d & mask[depth]) );
	
	// ab=true 表示 [a,b] 中所有数的第 depth 高位是否相等；
	// cd=true 表示 [c,d] 中所有数的第 depth 高位是否相等；
	
	if(ab && cd) {
		ll val = ( (a & f[depth]) ^ (c & f[depth]) );
		return dfs(depth-1, a, b, c, d, (ans | val) );
	}else if(!ab && cd) {
		ll m = mid(depth, a, b);
		
		if(c & f[depth]) {
			b = m -1;
		}else {
			a = m;
		}
		
		return dfs(depth-1, a, b, c, d, (ans | f[depth]) );
	}else if(ab && !cd) {
		
		ll m = mid(depth, c, d);
		
		if(a & f[depth]) {
			d = m - 1;
		}else {
			c = m;
		}
		
		return dfs(depth-1, a, b, c, d, (ans | f[depth]) );
	}else {
		// 这种情况，后面的低位必然可以组成  11111... 
		return ans | (f[depth+1] - 1);
	}
}

int main() {
	int i;
	for(i = 0; i <= maxb; ++i) {
		f[i] = (ll)1 << i;
		//printf("%lld\n", f[i]);
	}
	
	mask[maxb] = 0;
	for(i = maxb-1; i >= 0; --i) {
		mask[i] = mask[i+1] + f[i];
	}
	//printf("%lld\n", mask[0]);
	
	int t;
	scanf("%d", &t);
	ll a, b, c, d;
	while(t--) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		MaxV = 0;
		printf("%lld\n", dfs(62, a, b, c, d, 0));
	}
	
	return 0;
} 

/*
10
1 1000000000000000000 1 1000000000000000000
1 100 1 100
*/
