/*
	题意：
		给定 n 个数的序列， m 条询问 (其中 n,m <= 10^6)，对于每条询问求 [l, r] 是否是1个
	[1 ... r-l+1 ] 的排列；
	
	题解：
		若要满足条件，需要保证以下两点： 
		1）前缀和 sum[r] - sum[l-1] 一定是 x = r-l+1,  (1+x)*x / 2;
		2）[l, r] 里面没有重复元素；
		
	第一个条件：用前缀和 O(N) 预处理，O(1) 进行判断；
	第二个条件：建立一个线段树;
	用 pre[i] 表示和第i个数相同的数的最大位置；
	线段树来维护区间 [l, r] 内, max( pre[l], pre[l+1], pre[l+2], ... pre[r] )
	转换为区间最值问题；
	 

*/


#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

// RMQ 区间最小值询问

const int MAXM = 20;
const int MAXN = (1<<MAXM)+1;

//typedef long long ValueType;
// typedef double ValueType;
typedef int ValueType;


ValueType val[MAXN];
long long sum[MAXN];

ValueType node[MAXN];

int pre[MAXN], tmp[MAXN];

void initValue(int n) {
	memset(tmp, 0, sizeof(tmp));
	for(int i = 1; i <= n; ++i) {
		pre[i] = tmp[ val[i] ];
		tmp[ val[i] ] = i;
	}
}

int nodes[MAXN];

int Max(int l, int r) {
	return l > r ? l : r;
}

void build_tree(int p, int l, int r) {
	if(l == r) {
		nodes[p] = pre[l];
		return;
	}
	int mid = (l + r) >> 1; 
	build_tree(p<<1, l, mid);
	build_tree(p<<1|1, mid+1, r);
	nodes[p] = Max( nodes[p<<1], nodes[p<<1|1]);
}

int query_tree(int p, int queryL, int queryR, int l, int r) {
	if(queryL <= l && r <= queryR) {
		return nodes[p];
	}
	if(l > queryR || r < queryL) {
		return 0;
	}
	
	int mid = (l + r) >> 1;
	int lans = query_tree(p<<1,queryL,queryR,l, mid );
	int rans = query_tree(p<<1|1,queryL,queryR,mid+1, r );
	return Max(lans, rans);
}

template <class T>
inline void scan_d(T &ret) {
	char c; ret=0;
	while((c=getchar())<'0'||c>'9');
	while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
}

int main() {
	int n, m;
	int i;

	while(scanf( "%d %d", &n, &m ) != EOF) {
		for(i = 1; i <= n; ++i) {
			scan_d(val[i]);
			sum[i] = sum[i-1] + val[i]; 
		}
		initValue (n);
		build_tree(1, 1, n);
		 
		while(m--) {
			int l, r, ans = 0;
			scanf("%d %d", &l, &r);
			 
			bool bfind = false;
			long long cnt = r - l + 1;
			if( sum[r] - sum[l-1] ==  (1 + cnt) * cnt / 2 ) {
				bfind = ( query_tree(1, l, r, 1, n) < l );
				
			}
			printf("%s\n", bfind ? "YES" : "NO");
			
		}
	}
	return 0;
}


