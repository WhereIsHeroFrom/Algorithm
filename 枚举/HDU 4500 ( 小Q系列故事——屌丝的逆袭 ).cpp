#include <iostream>

using namespace std;

int mat[25][25];
int n, m;

int dir[4][2] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
};

int main() {
    int i, j, k;
    while(scanf("%d %d", &n, &m)!=EOF && (n||m)) {
        for(i = 0; i < n; ++i) {
            for(j = 0; j < m; ++j) {
                scanf("%d", &mat[i][j]);
            }    
        }
        int Max = -1000000, r, c;
        for(i = 0; i < n; ++i) {
            for(j = 0; j < m; ++j) {
                int v = 0;
                for(k = 0; k < 4; ++k) {
                    int ti = i + dir[k][0];
                    int tj = j + dir[k][1];
                    
                    if(ti<0 || tj<0 || ti>=n || tj>=m) {
                        continue;
                    }
                    if(mat[i][j] * mat[ti][tj] < 0) {
                        v += mat[ti][tj] < 0 ? -mat[ti][tj]: mat[ti][tj];
                    }else {
                        v -= mat[ti][tj] < 0 ? -mat[ti][tj]: mat[ti][tj];
                    } 
                }
                if(v > Max) {
                    Max = v;
                    r = i;
                    c = j;
                }
            }
        }
        printf("%d %d %d\n", r+1, c+1, Max);
    }
    return 0;
} 
