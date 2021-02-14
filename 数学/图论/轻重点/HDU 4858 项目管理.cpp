/*
	图的轻重点
	
		对于一个图，度数小于 sqrt(m) 的点称为 轻点，否则为重点
		
		轻点 向 所有点连边；   （保证小于 sqrt(m) 条） 
		重点 向 所有重点连边； （保证小于 sqrt(m) 条） 
		
		注意：重点 向 轻点 不连边； 
		
		增加权值时： 
			1、增加当前结点给周围邻接结点的贡献值 a[i]; 
			2、如果当前结点为轻点 u， 那么遍历它周围所有的重点 v，增加权值和 sum[v]; 
			
		统计时：
			轻点:遍历所有邻接点，对 a[i] 求和即为答案；
			重点:遍历所有邻接点，对 a[i] 求和，再加上本身记录的 邻接和 sum[i]； 
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100020;
#define ll long long 

vector< int > edges[MAXN];
int deg[MAXN];
int heav[MAXN];

struct Edge {
	int u, v;
}E[ MAXN ];

struct Quest {
	char tp;
	int u, v; 
};

ll a[MAXN], s[MAXN];

int main() {
	int t, i, j;
	int q, n, m;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 1; i <= n; ++i) {
			edges[i].clear();
			deg[i] = 0;
			a[i] = s[i] = 0;
			heav[i] = 0;
		}
		
		for(i = 0; i < m; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			E[i].u = x;
			E[i].v = y;
			
			++deg[x];
			++deg[y];
		}
		int sqrtm = sqrt(0.0 + m);
		
		for(i = 1; i <= n; ++i) {
			if(deg[i] > sqrtm) {
				heav[i] = 1;
			}
		}
		for(i = 0; i < m; ++i) {
			int u = E[i].u, v = E[i].v;
			
			// 重点不向轻点连边
			
			if( heav[u] && !heav[v] ) {
			}else {
				edges[u].push_back(v);
			}
			
			if( heav[v] && !heav[u] ) {
			}else {
				edges[v].push_back(u);
				
			}
		}
		
		
		scanf("%d", &q);
		Quest Q;
		for(i = 0; i < q; ++i) {
			scanf("%d %d", &Q.tp, &Q.u);
			if(Q.tp == 0) {
				scanf("%d", &Q.v);
				
				// 1. 给邻接所有点的权值更新值 
				a[ Q.u ] += Q.v;
				
				if( !heav[ Q.u ]) {
					// 2. 轻点给重点的权值更新值 
					for(j = 0; j < edges[Q.u].size(); ++j) {
						int adj = edges[Q.u][j];
						
						if( heav[ adj ] ) {
							s[ adj ] += Q.v;
						}
					}			
				}
			}else {
				ll sum = 0; 
				if( !heav[Q.u] ) {
					// 1. 如果是轻点，则直接统计邻接点的和
					for(j = 0; j < edges[Q.u].size(); ++j) {
						int adj = edges[Q.u][j];

						sum += a[adj];
					}	
				}else {
					// 2. 如果是重点，需要统计  轻点过来的 + 重点过来的和
					// 2.1 轻点过来的就是  sum[ Q.u ]; 
					// 2.2 重点过来的就是  a[  adj[ Q.u ][j] ]  求和； 
					sum = s[Q.u];
					 
					for(j = 0; j < edges[Q.u].size(); ++j) {
						int adj = edges[Q.u][j];

						sum += a[adj];
					}
					
				}
				
				printf("%lld\n", sum);
				
			}
		}

		
	}
	return 0;
} 
