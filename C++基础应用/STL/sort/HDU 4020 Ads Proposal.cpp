#include <iostream>
#include <algorithm>
#include <vector>
#include <queue> 
#include <cstring>

using namespace std;

int n, m, Q;

struct Ad {
	int clicks;
	int length;
	
	Ad() {
	}
	
	Ad(int c, int l) {
		clicks = c;
		length = l;
	}
	
	bool operator < (const Ad& ad) {
		return clicks > ad.clicks;
	}
};

struct Top {
	int idx;
	int k;
	void read(int id) {
		scanf("%d", &k);
		idx = id;
	}
	
	bool operator < (const Top& top) {
		return k < top.k;
	}
}T[100010];
vector < Ad > ads[500010];
int ads_idx[500010];

#define ll long long 
ll ans [100010];

int main() {
	int t, i, j, cas = 0;
	int q;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d", &n, &m, &q);
		for(i = 1; i <= n; ++i) {
			ads[i].clear();
			ads_idx[i] = 0;
		}
		for(i = 0; i < m; ++i) {
			int u, c, l;
			scanf("%d %d %d", &u, &c, &l);
			ads[u].push_back( Ad(c, l) );
		}
		queue <int> Q;
		for(i = 1; i <= n; ++i) {
			sort(ads[i].begin(), ads[i].end());
			if(ads[i].size())
				Q.push(i);
		}
		for(i = 0; i < q; ++i) {
			T[i].read(i);
		}
		sort(T, T + q);
		
		memset(ans, 0, sizeof(ans));
		
		for(i = 0; i < q; ++i) {
			if(i && T[i].k == T[i-1].k) {
				ans[ T[i].idx ] = ans[ T[i-1].idx ];
				continue;
			}
			if(i == 0) {
				ans[ T[i].idx ] = 0;
			}else
				ans[ T[i].idx ] = ans[ T[i-1].idx ];
			queue <int> tmpQ;
			while( !Q.empty() ) {
				int f = Q.front();
				Q.pop();
				
				int s;
				for(j = ads_idx[f], s = ads[f].size(); j < s && j < T[i].k; ++j) {
					ans[ T[i].idx ] += ads[f][j].length;
				}
				ads_idx[f] = (s < T[i].k) ? s : T[i].k;
				if(T[i].k < s) {
					tmpQ.push(f);
				}
			}
			
			while( ! tmpQ.empty() ) {
				Q.push(tmpQ.front());
				tmpQ.pop();
			}
		}
		
		printf("Case #%d:\n", ++cas);
		for(i = 0; i < q; ++i) {
			printf("%lld\n", ans[i]);
		}
		
		
	}
	return 0;
} 
