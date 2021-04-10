#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int dir[4][2] = {
    { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }
};

const int maxn = 210;
const int inf = -1;
int n, m;
int f[maxn][maxn];
int A[maxn][maxn];

void init() {
    memset(f, inf, sizeof(f));
}

int dfs(int preval, int x, int y) {
	// 1. 坐标合法性判断
	if(x < 1 || y < 1 || x > n || y > m) {
	    return 0;
	}
	// 2. 偏序关系合法性判断
	if(A[x][y] >= preval) {
		return 0;
	}
	
	// 3. 记忆化 
    int &val = f[x][y];
    if (val != inf) {
        return val;
    }
    
    // 4. 计算值 
    val = 1;
    for (int i = 0; i < 4; ++i) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        val = max(val, dfs(A[x][y], tx, ty) + 1);
    }
    
    // 5. 返回结果 
    return val;
}




int main() {
	
    while (scanf("%d %d", &n, &m) != EOF) {
        init();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &A[i][j]);

            }
        }
        int Max = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                Max = max(Max, dfs(100000000, i, j));
            }
        }
        printf("%d\n", Max);
    }
    return 0;
}
