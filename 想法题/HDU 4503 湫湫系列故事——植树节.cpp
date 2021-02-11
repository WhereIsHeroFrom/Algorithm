#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define maxn 1010

bool Map[maxn][maxn];
int s[2][maxn];

struct Point {
	int deg;
	int idx;
	
	Point() {}
	Point(int d, int i): deg(d), idx(i) {}
	
	bool operator < (const Point& p) const {
		return deg < p.deg;
	}
};

int main() {
	int t, n;
	int i, j;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		priority_queue <Point> Q;
		
		for(i = 1; i <= n; ++i) {
			int d;
			scanf("%d", &d);
			if(d)
				Q.push( Point(d, i) );	
			
			s[0][i] = s[1][i] = 0;
		}
		memset(Map, 0, sizeof(Map));
		while( !Q.empty() ) {
			Point a = Q.top();
			Q.pop();
			Point b = Q.top();
			Q.pop();
			
			--a.deg;
			--b.deg;
			Map[ a.idx ][ b.idx ] = Map[ b.idx ][ a.idx ] = 1;
			
			//printf("%d %d %d %d\n", a.deg, b.deg, a.idx, b.idx);
			if(a.deg) {
				Q.push( a );
			}
			if(b.deg) {
				Q.push( b );
			}
		}
		
		int sum = 0;
		
		for(i = 1; i <= n; ++i) {
			for(j = i + 1; j <= n; ++j) {
				int x = (Map[i][j]) ? 1 : 0;
				
				printf("<%d - %d> = %d\n", i, j, s[x][i]);
				sum += s[x][i];
				
				++ s[x][i];
			}
		}
		
		printf("%d\n", sum); 
		
		
	}
	
	return 0;
} 
