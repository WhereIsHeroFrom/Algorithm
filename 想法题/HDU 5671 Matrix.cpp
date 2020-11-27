#include <iostream> 
using namespace std;

#define LL long long
#define MAXN 1010

LL Mat[MAXN][MAXN];
LL Row[MAXN], Col[MAXN];
int rowIdx[MAXN], colIdx[MAXN];

int main() {
	int t;
	int n, m, Q;
	int i, j;
	
	scanf("%d", &t);
	
	while(t--) {
		scanf("%d %d %d", &n, &m, &Q);
		for(i = 1; i <= n; ++i) {
			Row[i] = 0;
			rowIdx[i] = i;
			for(j = 1; j <= m; ++j) {
				int v;
				scanf("%d", &v);
				Mat[i][j] = v;
				Col[j] = 0;
				colIdx[j] = j;
			}
		}
		while(Q--) {
			int tp, x, y;
			scanf("%d %d %d", &tp, &x, &y);
			if(tp == 1) {
				int tmp = rowIdx[x]; rowIdx[x] = rowIdx[y]; rowIdx[y] = tmp;
			}else if(tp == 2) {
				int tmp = colIdx[x]; colIdx[x] = colIdx[y]; colIdx[y] = tmp;
			}else if(tp == 3) {
				Row[ rowIdx[x] ] += y;
			}else if(tp == 4) {
				Col[ colIdx[x] ] += y;
			}
		}
		
		for(i = 1; i <= n; ++i) {
			for(j = 1; j <= m; ++j) {
				Mat[i][j] += Row[i] + Col[j];
			}
		}
		
		for(i = 1; i <= n; ++i) {
			for(j = 1; j <= m; ++j) {
				if(j > 1) printf(" ");
				printf("%I64d", Mat[ rowIdx[i] ][   colIdx[j]  ]);
			}
			puts("");
		}	
		
	}
	return 0;
}


/*
210
3 4 4
1 2 3 4
100 200 300 400
-1 -2 -3 -4
1 1 2
2 2 3
3 1 1
4 4 2


10
5 3 6
1 2 3
4 5 6
7 8 9
3 2 1
4 3 2

1 1 2
1 1 3
1 3 5
3 1 1
3 2 2
3 3 3


*/
