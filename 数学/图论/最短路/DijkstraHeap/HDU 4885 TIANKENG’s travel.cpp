/*
	最短路 + 极角排序建边
	 
	注意：
	
	题目要求：
		1）坐标系为直角坐标系； 
		2）任意两点间只能走直线；
		3）如果走到 加油站 必须加油； 
	
	所以两点之间在行进过程中如果有其它点，是一定要加油的；
	 
*/


#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath> 
using namespace std;

#define ll long long
const int maxn = 1100;
const int inf = 10000000;
ll sqr(ll x) {
	return x * x;
}

struct Edge {
	int u, times;
	
	Edge() {
	} 
	
	Edge(int to, int t) : u(to), times(t) {
	}
	bool operator < (const Edge& e) const {
		return times > e.times;
	}
};

struct Pos {
	int x, y;
	int u;
	double ang;
	ll dist;
	
	void pol(const Pos& o) {
		ang = angle(o);
		dist = dis(o);
	}
	
	ll dis(const Pos& p) {
		return sqr(x - p.x) + sqr(y - p.y);
	}
	double angle(const Pos& o) {
		return atan2(0.0+y-o.y, 0.0+x-o.x); 
	}
	
	bool operator < (const Pos& p) const {
		if(fabs( ang - p.ang ) < 1e-8) {
			return dist < p.dist; 
		}
		return ang < p.ang;
	}
}P[maxn], Q[maxn];

ll L;
int dist[maxn];


int spfa(int n) {
	
	// P[n]     start
	// P[n+1]   end
	for(int i = 0; i <= n+1; ++i) dist[i] = inf;
	dist[n] = 0;
	
	priority_queue <Edge> que;
	que.push( Edge(n, 0) );

	
	while(!que.empty()) {
		Edge edge = que.top();
		que.pop();
		
		if(edge.u == n+1) {
			return edge.times;
		}

		int tp = 0;
		for(int j = 0; j <= n+1; ++j) {
			
			// 最短路径树上的先驱结点，不应回去 
			if(dist[j] <= dist[edge.u]) {
				continue;
			}
			
			Q[tp] = P[j];
			Q[tp].u = j;
			Q[tp].pol(P[ edge.u ]);
			++tp;
		}
		sort(Q, Q + tp);
		for(int j = 0; j < tp; ++j) {
			// 这样做可以保证两个点之间没有其它点 
			if( j && fabs( Q[j].ang - Q[j-1].ang ) < 1e-8 ) {
				continue;
			}
			if(Q[j].dist > L) {
				continue;
			}
			int s = edge.u;
			int e = Q[j].u;
			int d = dist[s] + ( (e==n||e==n+1) ? 0 : 1);
			
			if(d < dist[e]) {
				dist[e] = d;
				que.push( Edge(e, d) );
			}
		}
	}
	return -1;
}

int main() {
	int t, i;
	int n, l;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &l);
		L = sqr(l);
		scanf("%d %d", &P[n].x, &P[n].y);
		scanf("%d %d", &P[n+1].x, &P[n+1].y);
				
		for(i = 0; i < n; ++i) {
			scanf("%d %d", &P[i].x, &P[i].y);
		}
		int ans = spfa(n);
		if(ans == -1) {
			printf("impossible\n");
		}else {
			printf("%d\n", ans);
		}
	}
	
	return 0;
} 

/*
100
5 2
0 0
6 6

1 1
2 2
3 3
4 4
5 5

100
1 10
0 0
8 6
4 3

100
0 10
0 0
8 6
*/
