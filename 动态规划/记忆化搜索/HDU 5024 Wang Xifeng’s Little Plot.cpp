#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 110;
const int invalid = -1;

char mat[maxn][maxn];
int f[8][maxn][maxn];

const int dir[8][2] = {
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 1},
	{1, 0},
	{1, -1},
	{0, -1},
	{-1, -1},
};
int n;

void init() {
	memset(f, invalid, sizeof(f));
}

int dfs(int d, int x, int y) {
	// 1. 判断边界
	if(x < 0 || y < 0 || x >= n || y >= n) {
		return 0;
	}
	
	// 2. 递归出口
	if(mat[x][y] == '#') {
		f[d][x][y] = 0;
		return 0;
	}
	
	// 3. 记忆化
	int &val = f[d][x][y];
	if(val != invalid) {
		return val;
	}
	
	// 4. 计算逻辑 
	int nx = x + dir[d][0];
	int ny = y + dir[d][1];
	val = 1 + dfs(d, nx, ny);
	
	// 5. 返回答案
	return val; // val <--> f[d][x][y]; 
}

void debug() {
	int i, j, k;
	for(k = 0; k < 8; ++k) {
		printf("%d:\n", k);
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				printf("%d", f[k][i][j]);
			}
			puts("");
		}
	}
}

int main() {
	int i, j, k;
    while (scanf("%d", &n) != EOF && n) {
        init();
		for (i = 0; i < n; ++i) {
        	scanf("%s", mat[i]);
		}
		for(i = 0; i < n;  ++i) {
			for(j = 0; j < n; ++j) {
				for(k = 0; k < 8; ++k) {
					dfs(k, i, j);
				}
			}
		}
		// debug();
		int ans = 0;
		for(i = 0; i < n; ++i) {
			for(j = 0; j < n; ++j) {
				for(k = 0; k < 8; ++k) {
					int nk = (k+2) % 8;
					int val = -1 + f[k][i][j] + f[nk][i][j];
					ans = max(ans, val);
				}
			}
		}
		printf("%d\n", ans);
    }

    return 0;
}
