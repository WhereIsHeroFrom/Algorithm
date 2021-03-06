#include <iostream>
#include <cmath>
#include<algorithm>
using namespace std;

#define MAXN 110
#define eps 1e-6

class GaussMatrix {
public:
    int r, c;                 // r个方程，c个未知数 
    double d[MAXN][MAXN];     // 增广矩阵 
    double x[MAXN];           // 解集 
    /*
    d[0][0]   * x[0] +   d[0][1] * x[1] + ... +   d[0][c-1] * x[c-1] =   d[0][c];
    d[1][0]   * x[0] +   d[1][1] * x[1] + ... +   d[1][c-1] * x[c-1] =   d[1][c];
    ...
    ...
    d[r-1][0] * x[0] + d[r-1][1] * x[1] + ... + d[r-1][c-1] * x[c-1] = d[r-1][c];
    */
    
    void swap_row(int ra, int rb) {
        int i;
        for(i = 0; i <= c; i++) {
            double tmp = d[ra][i];
            d[ra][i] = d[rb][i];
            d[rb][i] = tmp;
            
        }
    }
    
    bool zero(double v) {
        return fabs(v) < eps;
    }
    
    bool gauss() {
        int i, j, k;
        int col = 0;           // 当前枚举列 
        int maxrow;            // 第col列中绝对值最大的行号
        
        for(i = 0; i < r && col < c; i++) {
            maxrow = i;
            for(j = i+1; j < r; j++) {
                if( fabs(d[j][col]) > fabs(d[maxrow][col]) ) {
                    maxrow = j;
                }
            }
            // 将第col列最大的行maxrow和第i行交换，避免误差 
            if(i != maxrow) swap_row(i, maxrow);
            // 如果第col中最大的那行的值为0继续找下一列的 
            if( zero(d[i][col]) ) {
                col ++;
                i --;
                continue;
            }
            for(j = i+1; j < r; j++) {
                // 将第j行第col列的元素消为0 
                if( !zero(d[j][col]) ) {
                    double sub = d[j][col]/d[i][col];
                    for(k = col; k <= c; k++) {
                        d[j][k] = d[j][k] - d[i][k] * sub; // 注意：这一步是关键，精度误差就在这里出现 
                    }
                }
            }
            col++;
        }
        
        // 唯一解 回归 
        for(i = c-1; i >= 0; i--) {
            double sum = 0;
            for(j = i+1; j < c; j++) {
                sum += x[j] * d[i][j];
            }
            x[i] = (d[i][c] - sum) / d[i][i];
            if( zero(x[i]) ) x[i] = 0;
        }
        return true;
    }    
    void debug_print_x() {
        int i;
        for(i = 0; i < c; i++) {
            printf("%.3lf ", x[i]);
        }
        puts("");
    }
    
    void debug_print() {
        int i, j;
        puts("---------------------------------");
        for(i = 0; i < r; i++) {
            for(j = 0; j <= c; j++) {
                printf("%.3lf ", d[i][j]);
            }
            puts("");
        }
        puts("---------------------------------");
    } 
};

double t[MAXN][MAXN];

int ABS(int a) {
    return a < 0 ? -a : a;
}

int main() {
    /*GaussMatrix M;
    M.r = 2;
    M.c = 2;
    M.d[0][0] = 3; M.d[0][1] = 9; M.d[0][2] = 2;
    M.d[1][0] = 7; M.d[1][1] = 5; M.d[1][2] = 12;
    M.debug_print();
    M.gauss();*/
    
    int W, H, D;
    int i, j;
    int k, l;
    int cases = 1;
    while( scanf("%d %d %d", &W, &H, &D) != EOF && (W + H) ) {
        
        if( cases ++ > 1 ) {
            printf("\n");
        }
        
        for(i = 0; i < H; i++) {
            for(j = 0; j < W; j++) {
                scanf("%lf", &t[i][j]);
            }
        }
        GaussMatrix M;
        M.r = M.c = H * W;
        
        for(i = 0; i < H; i++) {
            for(j = 0; j < W; j++) {
                int cnt = 0;
                int line = i * W + j;
                for(k = 0; k < H; k++) {
                    for(l = 0; l < W; l++) {
                        int col = k * W + l;
                        if( ABS(k-i) + ABS(l-j) <= D ) {
                            cnt ++;
                            M.d[line][col] = 1;
                        }else {
                            M.d[line][col] = 0;
                        }
                    }
                }
                M.d[line][ M.c ] = cnt * t[i][j];
            }
        }
        M.gauss();
        for(i = 0; i < H; i++) {
            for(j = 0; j < W; j++) {
                printf("%8.2lf", M.x[ i*W + j ] );
            }
            puts("");
        }
    }
    return 0;
}

/*
4 5 2
14 15 14 15
14 15 14 15
14 15 14 15
14 15 14 15
14 15 14 15

*/

