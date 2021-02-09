#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Point {
	int u, v, val;
	Point() {
	}
	Point(int _u, int _v, int _val) : u(_u), v(_v), val(_val) {
		
	}
	bool operator < (const Point& a) const {
		return val < a.val;
	}
}P[10010], E[10010];
int tp, etp;

int Map[110][110];
int Pre[110][110];
int n;

int main() {
	int t, cas = 0;
	int i, j;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		tp = 0;	
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				int v;
				scanf("%d", &v);
				//v = 1;
				if(i != j) {
					P[tp++] = Point(i, j, v);
				}
				Pre[i][j] = v;
			}
		}
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				Map[i][j] = (i==j) ? 0 : 100000000;
			}
		}
		sort(P, P + tp);
		int cnt = 0, flag = 0;
		etp = 0;
		
		for(i = 0; i < tp; ++i) {
			int u = P[i].u, v = P[i].v, val = P[i].val;
			
			if(Map[u][v] == val) {
				continue;
			}
			if(Map[u][v] < val) {
				flag = 1;
				break;
			}
			Map[u][v] = val;
			++cnt;
			
			for(int x = 0; x < n; ++x) {
				for(int y = 0; y < n; ++y) {
					if(x == y) continue;
					
					int dist = Map[x][u] + val + Map[v][y];
					if( dist < Map[x][y]) {
						Map[x][y] = dist;
						if(Map[x][y] < Pre[x][y]) {
							flag = 1;
							break;
						}
					}
				}
				if(flag) break;
			}
			if(flag) break;
		}
		printf("Case %d: ", ++cas);
		if(i == tp) {
			printf("%d\n", cnt);
		}else {
			printf("impossible\n");
		}
		
	}
	return 0;
} 
