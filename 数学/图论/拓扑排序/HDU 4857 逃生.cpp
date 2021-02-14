#include <iostream> 
#include <vector>
#include <queue>
#include <algorithm>
 
using namespace std;

#define MAXN 30010

vector <int> edges[MAXN];
vector <int> invedges[MAXN];

int in[MAXN], out[MAXN];
int Min[MAXN], ans[MAXN];

struct Vertex {
	int v;
	Vertex() {
		
	}
	Vertex(int vv): v(vv) {
		
	}
	
	bool operator < (const Vertex& other) const {
		return v < other.v;
	}
};



void dfs(int u, int minv) {
	if(Min[u] == -1 || minv < Min[u]) {
		Min[u] = minv;
	}
	
	for(int i = 0, s = invedges[u].size(); i < s; ++i) {
		int v = invedges[u][i];
		dfs(v, v < minv ? v : minv);
	}	
}

int main() {
	int t, i;
	int n, m;
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i <= n; ++i) {
			edges[i].clear();
			invedges[i].clear();		
			in[i] = out[i] = 0;
			Min[i] = -1;
		}
		
		while(m--) {
			int x, y;
			
			scanf("%d %d", &y, &x);
			edges[x].push_back(y);
			invedges[y].push_back(x);
			++ in[y];
			++ out[x];
			
		} 
		
		priority_queue <Vertex> Q;
		/*for(i = 1; i <= n; ++i) {
			if(!out[i]) {
				dfs(i, i);
			}
		}*/

		for(i = 1; i <= n; ++i) {
			if(!in[i]) {
				Q.push( Vertex(i) );
			}
		}
		
		int tp = 0;
		while(!Q.empty()) {
			Vertex x = Q.top();
			Q.pop();

			ans[tp++] = x.v;
			
			for(i = 0; i < edges[ x.v ].size(); ++i) {
			    int u = edges[ x.v ][i];
				-- in[u];
				if( !in[u] ) {
					Q.push( Vertex(u) );
				}
			}
		}
		
		bool print = 0;
		
		for(int j = tp-1; j >= 0; --j) {
			if(print) {
				printf(" ");
			}
			print = 1;
			printf("%d", ans[j]);
		}

		puts("");
	}
	return 0;
}

/*
5656
5 4
5 4
4 1
5 3
3 2

7 6
7 6
7 5
5 4
6 1
5 3
3 2

7 6
7 6
7 5
5 4
6 1
5 3
4 2

8 4
5 1
6 1
7 1
8 1

10 6
10 6
9 6
8 6
7 1
5 1
3 1

5 5
5 4
4 2
2 1
5 3
3 1

*/
