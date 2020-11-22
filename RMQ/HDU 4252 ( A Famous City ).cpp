#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010
#define MAXL 18

int a[MAXN], b[MAXN], n, L, bs;
int prep[MAXN];

class RMQData {
public:
        int index;
        int val;
}rd[MAXN];

int Log2[MAXN];        // Log2[i] = log2(i)
int f[MAXN][MAXL];     // f[i][j] 表示 [i, (i + 2^j) - 1]这个区间的最小值 对应数的下标
                       // f[i][j] = min{ f[i][j-1] , f[ i + 2^(j-1) ][j-1] }

void RMQ_Init() {
        int i, j, p;

        // 计算log以2为底的i的对数 log2(i)
       Log2[1] = 0;
        for(i = 2; i <= n; i++) {
              Log2[i] = Log2[i-1];
               if( 1<<(Log2[i] + 1) == i ) {
                     Log2[i] ++;
              }
       }
        for(j = 0; j < MAXL; j++) {
               for(i = 0; i < n; i++) {
                      if(j == 0) {
                           f[i][0] = i;
                     } else {
                           f[i][j] = f[i][j-1];
                           p = i + (1<<(j-1));
                            if(p < n) {
                                   if( rd[ f[p][j-1] ].val < rd[ f[i][j] ].val ) {
                                         f[i][j] = f[p][j-1];
                                  }
                           }                          
                     }
              }
       }
}

// 询问的时候拆成两个长度为2^k的区间
// f[l][k] 和 f[r-2^k+1][k]
// 并且k的取值要求能够使得 [l,l+2^k-1] 和 [r-2^k+1,r] 的并集 为 [l, r]
// 于是 k为满足l+2^k-1 <= r并且值最大，即2^k <= r-l+1
// k <= log2(r-l+1), 又k为整数，所以k为log2(r-l+1)的下取整
int RMQ_Query(int l, int r) {
        if(l > r) {
               int tmp = l;
              l = r;
              r = tmp;
       }
        int k = Log2[r - l + 1];
        return rd[ f[l][k] ].val < rd[ f[r-(1<<k)+1][k] ].val ? f[l][k] : f[r-(1<<k)+1][k];
}

int getIndex(int v) {
    int l = 1, r = L;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(v == b[mid]) return mid;
        else if(v < b[mid]) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
}

int main() {
    int cases = 0;
    int i, j;
    while( scanf("%d", &n) != EOF ) {
        bs = 0;
        L = 1;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            b[++bs] = a[i];
        }
        sort(&b[1], &b[1] + bs);
        for(i = 2; i <= bs; i++) {
            if(b[i] != b[i-1]) {
                b[++L] = b[i];
            }
        }
        for(i = 0; i < n; i++) {
            rd[i].index = i;
            rd[i].val = getIndex(a[i]);
        }
        RMQ_Init();
        for(i = 1; i <= L; i++) prep[i] = -1;
        
        int ans = 0;
        for(i = 0;i < n; i++) {
            int v = rd[i].val;
            if(b[v] == 0) {
                continue;
            }
            if(prep[v] == -1) {
                ans ++;
            }else {
                if( rd[ RMQ_Query(prep[v], i) ].val < v ) {
                    ans ++;
                }
            }
            prep[v] = i;
        }
        
        printf("Case %d: %d\n", ++cases, ans);
        
    }
    return 0;
}

/*
6
1 6 2 9 3 8
*/
