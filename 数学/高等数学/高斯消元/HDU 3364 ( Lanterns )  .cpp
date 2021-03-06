#include <iostream>

using namespace std;

#define MAXN 105
#define MOD 2
#define LL __int64

/*

开关类问题的高斯消元
    即答案只有0或者1

*/

class GaussMatrix {
public:
    int r, c;
    int d[MAXN][MAXN];
    int x[MAXN];       // 某个解集 
    LL  xcnt;          // 解集个数 
    
    int abs(int v) {
        return v < 0 ? -v : v;
    }
    
    void swap_row(int ra, int rb) {
        for(int i = 0; i <= c; i++) {
            int tmp = d[ra][i];
            d[ra][i] = d[rb][i];
            d[rb][i] = tmp;
        }
    }
    void swap_col(int ca, int cb) {
        for(int i = 0; i < r; i++) {
            int tmp = d[i][ca];
            d[i][ca] = d[i][cb];
            d[i][cb] = tmp;
        }        
    }
    
    // -1 表示无解 
    LL gauss() {
        int i, j, k;
        int col, maxrow;
        
        // 枚举行，步进列 
        for(i = 0, col = 0; i < r && col < c; i++) {
            //debug_print();
            maxrow = i;
            // 找到i到r-1行中col元素最大的那个值 
            for(j = i+1; j < r; j++) {
                if( abs(d[j][col]) > abs(d[maxrow][col]) ){
                    maxrow = j;
                }
            }
            // 最大的行和第i行交换 
            if(maxrow != i) {
                swap_row(i, maxrow);
            }
            if( d[i][col] == 0 ) {
                // 最大的那一行的当前col值 等于0，继续找下一列
                col ++;
                i--;
                continue; 
            }
            
            for(j = i+1; j < r; j++) {
                if( d[j][col] ) {
                    // 当前行的第col列如果不为0，则进行消元
                    // 以期第i以下的第col列的所有元素都消为0 
                    int lastcoff = d[i][col];
                    int nowcoff = d[j][col];
                    for(k = col; k <= c; k++) {
                         d[j][k] = ( (d[j][k] * lastcoff - d[i][k] * nowcoff) % MOD + MOD ) % MOD;
                    }
                }
            }
            col ++;
        }
        // i表示从i往后的行的矩阵元素都为0 
        // 存在 (0 0 0 0 0 0 d[j][c]) (d[j][c] != 0) 的情况，方程无解 
        for(j = i; j < r; j++) {
            if( d[j][c] ) {
                return -1;
            }
        }
        int free_num = c - i;
        return xcnt = ( ((LL)1) << (LL)free_num ); 
        // 交换列，保证最后的矩阵为严格上三角，并且上三角以下的行都为0 
        for(i = 0; i < r && i < c; i++) {
            if( !d[i][i] ) {
                // 对角线为0 
                for(j = i+1; j < c; j++) {
                    // 在该行向后找第一个不为0的元素所在的列，交换i和这一列 
                    if(d[i][j]) break;
                }
                if(j < c) {
                    swap_col(i, j);
                }
            }
        }
        xcnt = ( ((LL)1) << (LL)free_num );
        return xcnt;
    }    
    
    void debug_print() {
        int i, j;
        printf("-------------------------------\n");
        for(i = 0; i < r; i++) {
            for(j = 0; j <= c; j++) {
                printf("%d ", d[i][j]);
            }
            puts("");
        }
        printf("-------------------------------\n");
    }  
};

int val[MAXN];
int tx[MAXN][MAXN];

int main() {
    int t;
    int n, m;
    int i, j, k, l;
    int x, y;
    int cases = 1;
    scanf("%d", &t);
    
    while(t--) {
        memset(tx, 0, sizeof(tx));
        scanf("%d %d", &n, &m);
        for(i = 0; i < m; i++) {
            scanf("%d", &k);
            while(k--) {
                scanf("%d", &l);
                l--;
                tx[l][i] = 1;   // 第l个灯由第i个开关控制 
            }
        }
        int Q;
        printf("Case %d:\n", cases ++ );
        
        scanf("%d", &Q);
        
        while( Q--) { 
            for(i = 0; i < n; i++) {
                scanf("%d", &val[i]);
            }
            
            GaussMatrix M;
            M.r = n;
            M.c = m;
            for(i = 0; i < M.r; i++) {
                for(j = 0; j <= M.c; j++) {
                    if(j == M.c) {
                        M.d[i][j] = val[i];
                    }else {
                        M.d[i][j] = tx[i][j];
                    }
                }
            }
            if( M.gauss() == -1 ) {
                printf( "0\n" );
            }else {
                printf( "%I64d\n", M.xcnt );
            }
        }
        
    }
    return 0;
}

/*
10
3 2
2 1 2
2 1 3
2
0 1 1
1 1 1
3 3
0
0
0
2
0 0 0
1 0 0

10
50 50
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
5
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0  
1 1 1 1 1 1 1 1 1 1 
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
*/

