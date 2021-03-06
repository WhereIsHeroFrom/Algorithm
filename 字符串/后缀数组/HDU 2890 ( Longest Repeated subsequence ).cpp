#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100060

int bucket[MAXN];         // 桶计数数组
int wx[MAXN], wy[MAXN];   // 排序辅助数组 
int key[MAXN];            
int src[MAXN];

int sa[MAXN], rank[MAXN]; // 后缀数组、名次数组 
int height[MAXN];         // 前缀数组
 
void debug_print(int *src, int size) {
    for(int i = 0; i < size; i++) printf("%d ", src[i]);
    puts("");
}


int da_cmp(int *x, int a, int b, int l) {
    return x[a] == x[b] && x[a+l] == x[b+l];
}

// 基数排序
// 函数作用：对y[i]数组以key[i]为键值进行排序  (key, y)为一个键值对 
// 函数结果：排序结果存在sa数组中
void calculateSA(int *key, int *sa, int *y, int n, int m) {
    int i, j, *tmp = bucket;
    // 将m个桶置空 
    for(i = 0; i < m; i++) tmp[i] = 0;
    // 统计每个桶中需要放置的元素的个数 
    for(i = 0; i < n; i++) tmp[ key[i] ] ++;
    // 将所有的桶串起来 
    for(i = 1; i < m; i++) tmp[i] += tmp[i-1];
    // 记录每个桶中对应的后缀编号 
    for(i = n-1; i >= 0; i--) sa[ --tmp[ key[i] ] ] = y[i]; 
}

// 倍增算法

// val[i] 源字符串, 需要保证val[n-1]一定是字典序最小的字符 
// sa[i] 表示字典序排在第i个的后缀为suffix(sa[i])
// n 源字符串的长度
// m 源字符集合的最大字符+1 
void doublingAlgorithm(int *src, int *sa, int n, int m) {
    int i, j, p;
    int *x = wx, *y = wy, *t;
    memset(sa, 0, sizeof(sa));
    
    // 1.对一个字符的所有后缀进行基数排序
    for(i = 0; i < n; i++) {
        x[i] = src[i], y[i] = i;
    }
    calculateSA(x, sa, y, n, m);
    
    for(j = 1, p = 1; p < n; j *= 2, m = p) {

        for(p = 0, i = n-j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
        
        
        for(i = 0; i < n; i++) key[i] = x[ y[i] ];
        calculateSA(key, sa, y, n, m);

        
        // 通过sa数组来对名次数组进行反算
        // 这里需要比较相邻两个后缀sa[i-1]和sa[i]是否相等
        // 如果相等，x[ sa[i] ] = x[ sa[i-1] ];
        // 否则  x[ sa[i] ] 为之前没有出现过的一个新的编号 
        for(t=x, x=y, y=t, p=1, x[ sa[0] ] = 0, i=1; i < n; i++)
            x[ sa[i] ] = da_cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
      
    }
}

void lcprefix(int *src, int *sa, int n) {
    int i, j, k = 0;
    
    for(i = 0; i < n; i++) rank[ sa[i] ] = i;
    // h[i] >= h[i-1] - 1;
    for(i = 0; i < n; i++) {
        if(k) {
            k--;
        }
        for(j = sa[ rank[i] - 1 ]; src[i+k] == src[j+k]; k++);
        height[ rank[i] ] = k;
    }
    // height[0] = 0  定义如此 
    // height[1] = 0  因为排名第0位的字符串永远是结尾的那个最小字符，所以字典序最小的两个后缀的公共前缀必定为空集 
}
 
char str1[MAXN];

int ABS(int v) {
    return v < 0 ? -v : v;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int var[MAXN], N;
int org[MAXN];

int getIndex(int v) {
    int l = 0, r = N;
    while( l <= r ) {
        int mid = (l + r) >> 1;
        if(var[mid] == v) {
            return mid + 1;
        }
        if(var[mid] > v) {
            r = mid - 1;
        }else {
            l = mid + 1;
        }
    }
}
int n, k;
int ans_s[MAXN], ans_top;

bool sub_check(int *tmp, int tsize, int maxlen) {
    if(!tsize) return false;
    
    sort( tmp, tmp + tsize );
    int presa = tmp[0];
    int cnt = 1;
    for(int i = 1; i < tsize; i++) {
        if( tmp[i] - presa >= maxlen ) {
            presa = tmp[i];
            cnt++;
            if(cnt >= k) return true;
        }
    }
    return false;
}

bool check(int maxlen) {
    int *tmp = wx;
    int tsize = 0;
    int i;
    
    for(i = 2; i < n; i++) {
        if( height[i] >= maxlen ) {
            tmp[ tsize++ ] = sa[i-1];
            tmp[ tsize++ ] = sa[i];
        }else {
            if( sub_check(tmp, tsize, maxlen) ) return true;
            tsize = 0;
        }
    }
    return sub_check(tmp, tsize, maxlen);
}

void printans(int spos, int maxlen) {
    for(int i = spos; i < spos + maxlen; i++) {
        printf("%d\n", var[ src[i] - 1 ]);
    }
}

void getans(int maxlen) {
    int *tmp = wx;
    int tsize = 0;
    int i;
    
    for(i = 2; i < n; i++) {
        if( height[i] >= maxlen ) {
            tmp[ tsize++ ] = sa[i-1];
            tmp[ tsize++ ] = sa[i];
        }else {
            if( sub_check(tmp, tsize, maxlen) ) {
                printans(tmp[0], maxlen);
                return ;
            }
            tsize = 0;
        }
    }
    if( sub_check(tmp, tsize, maxlen) ) {
        printans(tmp[0], maxlen);
    }
}

int main() {
    int t;
    int i;
    scanf("%d", &t);
    
    while( t-- ) { 
        scanf("%d %d", &n, &k);
        int tmp = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &org[i]);
            var[tmp++] = org[i];
        }
        sort(var, var+tmp);
        N = 1;
        for(i = 1; i < tmp; i++) if( var[i] != var[i-1] ) var[N++] = var[i];
        for(i = 0; i < n; i++) {
            src[i] = getIndex(org[i]);
        }
        src[n++] = 0;
        doublingAlgorithm(src, sa, n, N+10);
        lcprefix(src, sa, n);
        
        /*for(i = 0; i < n; i++) {
            printf("%d ", height[i]);
        }
        puts("");
        */
        
        int l = 0, r = n;
        int ans = -1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if( check(mid) ) {
                l = mid + 1;
                ans = mid;
            }else {
                r = mid - 1;
            }
        }
        
        printf("%d\n", ans);
        getans(ans);
        if(t) printf("\n");
    }
    return 0;
}
/*
10
8 2
1 2 3 2 3 2 3 1

10
8 2
1000 23 54 23 54 23 54 1000

10
12 2
9 8 7 9 8 7 7 6 5 7 6 5

*/

