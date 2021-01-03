#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// RMQ 区间最小值询问

const int MAXM = 9;
const int MAXN = 256;

// typedef __int64 ValueType;
// typedef double ValueType;
typedef int ValueType;
int lg2K[MAXN];

int RMQ_Pack(int r, int c) {
	return (r << MAXM | c);
}

void RMQ_UnPack(int code, int& r, int& c) {
	r = (code >> MAXM);
	c = (code & ( (1<<MAXM) - 1) );
}

ValueType RMQ_GetValue(ValueType A[MAXN][MAXN], int code) {
	int r, c;
	RMQ_UnPack(code, r, c);
	return A[r][c];
}

int RMQ_MinIndex(ValueType A[MAXN][MAXN], int a, int b) {
    return RMQ_GetValue(A, b) < RMQ_GetValue(A, a) ? b : a;
}

void RMQ_Init(ValueType A[MAXN][MAXN], int XLen, int YLen, int f[MAXM][MAXM][MAXN][MAXN]) {
	int i, j, x, y, k = 0;
	for (i = 1; i < MAXN; i++) {
		lg2K[i] = k - 1;
		if ((1 << k) == i) k++;
	}
	
	for (i = 0; i < MAXM; i++) {
		for(j = 0; j < MAXM; ++j) {
			for(x = 1; x + (1<<i) - 1 <= XLen; ++x) {
				for(y = 1; y + (1<<j) - 1 <= YLen; ++y) {
					int &rf = f[i][j][x][y];
					
					if(i == 0 && j == 0) {
						rf = RMQ_Pack(x, y);
					}else if(i == 0) {
						rf = RMQ_MinIndex(A, f[i][j-1][x][y], f[i][j-1][x][y + (1<<(j-1))]);
					}else if(j == 0) {
						rf = RMQ_MinIndex(A, f[i-1][j][x][y], f[i-1][j][x + (1<<(i-1))][y]);
					}else {
						int a = RMQ_MinIndex(A, f[i][j-1][x][y], f[i][j-1][x][y + (1<<(j-1))]);
						int b = RMQ_MinIndex(A, f[i-1][j][x][y], f[i-1][j][x + (1<<(i-1))][y]);
						rf = RMQ_MinIndex(A, a, b);
					}
				}
			}
		}
	}
}

// (lx, ly) 左上角
// (rx, ry) 右下角 
int RMQ_Query(ValueType A[MAXN][MAXN], int f[MAXM][MAXM][MAXN][MAXN], int lx, int ly, int rx, int ry ) {
	
    int i = lg2K[ rx - lx + 1 ];
    int j = lg2K[ ry - ly + 1 ];
    
    
	if( lx == rx && ly == ry ) {
		return RMQ_Pack(lx, ly);
	}else if(lx == rx) {
		return 		
		RMQ_MinIndex( 
			A,
			f[0][j][lx][ry-(1<<j)+1], 
			f[0][j][lx][ly] 
		);
	}else if(ly == ry) {
		return 
		RMQ_MinIndex( 
			A,
			f[i][0][lx][ly], 
			f[i][0][rx-(1<<i)+1][ly]
		);
	}
	
    return 
	
	RMQ_MinIndex(
		A, 
		
		RMQ_MinIndex( 
			A,
			f[i][j][lx][ly], 
			f[i][j][rx-(1<<i)+1][ry-(1<<j)+1]
		), 
		
		RMQ_MinIndex( 
			A,
			f[i][j][lx][ry-(1<<j)+1], 
			f[i][j][rx-(1<<i)+1][ly] 
		) 
	);
}


int fMin[MAXM][MAXM][MAXN][MAXN], fMax[MAXM][MAXM][MAXN][MAXN];
ValueType vMin[MAXN][MAXN], vMax[MAXN][MAXN];


int n, m;

int main() {
	int n, b, k;
	while(scanf("%d %d %d", &n, &b, &k) != EOF) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				scanf("%d", &vMin[i][j]);
				vMax[i][j] = - vMin[i][j];
			}
		}
		RMQ_Init(vMin, n, n, fMin);
		RMQ_Init(vMax, n, n, fMax);
		
		while(k--) {
			int l, r;
			scanf("%d %d", &l, &r);
			int idxMin = RMQ_Query(vMin, fMin, l, r, l + b - 1, r + b - 1);
			int idxMax = RMQ_Query(vMax, fMax, l, r, l + b - 1, r + b - 1);
			
			int ans = - RMQ_GetValue(vMax, idxMax) - RMQ_GetValue(vMin, idxMin);
			
			printf("%d\n", ans);
			
		}
		
	}
	
	
} 

