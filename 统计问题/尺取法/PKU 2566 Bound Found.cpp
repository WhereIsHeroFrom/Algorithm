#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100010;
#define ll long long 

struct Sum {
	int s;
	int idx;
	Sum() {
	}
	Sum(int _s, int _idx) : s(_s), idx(_idx) {
		
	} 
	bool operator < (const Sum& other) {
		return s < other.s;
	}
}S[maxn];

int n, n1, a[maxn], sum[maxn];

void check(int i, int j, int t, int &clo, int & val,int & l,int & r) {
	if(i == j) {
		return ;
	}
	
	int v = (S[j].s - S[i].s);
	if(v < 0) v = -v;
	v -= t;
	if(v < 0) v = -v;
	
	if(v >= clo) {
		return ;
	}
	clo = v;
	val = (S[j].s - S[i].s);
	if(val < 0) val = -val;
	
	if(S[i].idx < S[j].idx) {
		l = S[i].idx + 1;
		r = S[j].idx;
	}else {
		l = S[j].idx +1;
		r = S[i].idx; 
	}
	
}
 
int solve(int n, int t, int & l, int & r) {
	int i = 0, j = -1;
	int val = -1000000;
	int clo = 1000000010;
	while(j < n - 1) {
		++j;
		while (S[j].s - S[i].s > t) {
			check(i, j, t, clo, val, l, r);
			++i;
		}
		check(i, j, t, clo, val, l, r);
	}
	return val;
}

int main() {
	int t;
	int n, k;
	while(scanf("%d %d", &n, &k) != EOF && (n || k)) {
		n1 = 0;
		sum[0] = 0;
		S[n1++] = Sum(0, 0);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			sum[i] = sum[i-1] + a[i];
			S[n1++] = Sum(sum[i], i);
		}
		
		sort(S, S + n1);
		while(k--) {
			scanf("%d", &t);
			int l, r; 
			int ans = solve(n1, t, l, r);
			printf("%d %d %d\n", ans, l, r);
		}
		
	}
	
	return 0;
} 
