/*
	离线算法 + 线段树
	 
	线段树维护的时候一个结点内所有可能出现的 1-100 内的取值（用两个 INT64 来存储标记） 
	
	两个结点合并的是 两个结点 内所有取值的和；
	
	low   ->   1-50  位组表示存不存在 
	high  -> 51-100  位组表示存不存在
	 
*/


#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

#define ll long long
const int MAXS = 2;
const int LOWMAX = 50;
const int MAXN = 20010;
const int MAXM = 100010;

ll p[100];

void init() {
	p[0] = 1;
	for(int i = 1; i < 60; ++i) {
		p[i] = p[i-1] << 1;
	}
}

ll lowbit(ll x) {
	return x & -x;
}

int getk(ll x) {
	return int(log2( x + 0.1 ) );
}

ll filter(ll x) {
	return x & (p[LOWMAX] - 1);
}

struct Node {
	
	// 1 - 50
	ll low;
	
	// 50 - 100
	ll high;
	
	Node() {
		low = high = 0;
	}
	
	Node (int x) {
		setv(x);
	}
	
	void reset() {
		low = high = 0;
	}
	
	void setv(int x) {
		if( x <= LOWMAX ) {
			low = p[x-1];
			high = 0;
		}else {
			low = 0;
			high = p[x - LOWMAX - 1];
		}
	}
	
	bool hasv(int x) {
		if(  x <= LOWMAX ) {
			return low & p[x-1]; 
		}else {
			return high & p[x - LOWMAX - 1];
		}
	}
	
	
	void merge(const Node& other) {
		ll tlow = low, thigh = high; 
		if(low + 1 == p[LOWMAX] && high + 1 == p[LOWMAX]) {
			return ;
		}
		
		// low 部分
		ll nlow = low;
		while(nlow) {
			ll x = lowbit(nlow);
			nlow ^= x;
			
			int i = getk(x) + 1;
			
			tlow |= filter(other.low << i);
			thigh |= filter( other.high << i | ( other.low >> (LOWMAX - i) ) );
		}
		
		
		// high 部分 
		ll nhigh = high;
		while(nhigh) {
			ll x = lowbit(nhigh);
			nhigh ^= x;
			
			int i = getk(x) + 1;
			
			thigh |= filter( other.low << i ) ;
		}
		
		low = (low | tlow | other.low);
		high = (high | thigh | other.high);
	}
};

struct Quest {
	int type;
	int l, r, c, s;
	int index;
	
	Quest() {

	}
	
	Quest(int _t, int _l, int _r, int _c, int _s, int idx) {
		type = _t;
		l = _l;
		r = _r;
		c = _c;
		s = _s;
		index = idx;
	}
	
	void print () {
		printf("tp=%d, [%d,%d], c=%d, s=%d, index=%d\n", type, l, r, c, s, index);
	}
	
	bool operator < (const Quest& q) const {
		if(c == q.c) {
			return type < q.type;
		}
		return c < q.c;
	}
}Q[MAXN + MAXM];

int s[MAXN];
int d[MAXN];
int tot;

Node T[1<<16];

void build(int p, int l, int r) {
	if(l == r) {
		T[p].reset();
		return;
	}
	int mid = (l + r) >> 1;
	build(p<<1, l, mid);
	build(p<<1|1, mid + 1, r);
	T[p] = T[p<<1];
	T[p].merge(T[p<<1|1]);
	
}

void insert(int p, int l, int r, int pos, int val) {
	if(pos < l || pos > r) {
		return ;
	}
	if(l == pos && pos == r) {
		T[p].setv(val);
		return ;
	}
	int mid = (l + r) >> 1;
	insert(p<<1, l, mid, pos, val);
	insert(p<<1|1, mid + 1, r, pos, val);
	
	T[p] = T[p<<1];
	T[p].merge(T[p<<1|1]);	
	
} 

void query(int p, int l, int r, int L, int R, int val, Node& ans, bool& find) {
	if(R < l || L > r) {
		return;
	}
	if(find) {
		return ;
	}
	
	if(L <= l && r <= R) {
		ans.merge( T[p] );
		if(ans.hasv(val)) {
			find = true;
		}
		return ;
	}
	
	int mid = (l + r) >> 1;
	query(p<<1, l, mid, L, R, val, ans, find);
	query(p<<1|1, mid+1, r, L, R, val, ans, find);
	
}

int ans[MAXM];
int n, m;

int main() {
	int i;
	init();
	
	int t;
	scanf("%d", &t);
	
	while(t--) {
		tot = 0;
		scanf("%d %d", &n, &m);
		for(i = 1; i <= n; ++i) {
			scanf("%d", &s[i]);	
		}
		for(i = 1; i <= n; ++i) {
			scanf("%d", &d[i]);
			
			Q[tot++] = Quest(0, -1, -1, d[i], s[i], i);
		}
		build (1, 1, n); 
		
		
		for(i = 0; i < m; ++i) {
			int l, r, c, s;
			scanf("%d %d %d %d", &l, &r, &c, &s);
			
			Q[tot++] = Quest(1, l, r, c, s, i);
		}
		
		sort( Q, Q + tot );
		
		for(i = 0; i < tot; ++i) {
			//Q[i].print();
			
			if(Q[i].type == 0) {
				// 线段树插入操作 
				insert(1, 1, n, Q[i].index, Q[i].s);
			} else {
				// 线段树查询操作
				Node as;
				bool find = false;
				query(1, 1, n, Q[i].l, Q[i].r, Q[i].s, as, find);
				ans[ Q[i].index ] = !find;
			}
		}
		for(i = 0; i < m; ++i) {
			printf("%d", ans[i]);
		}
		puts("");
		
	}


	return 0;
} 
