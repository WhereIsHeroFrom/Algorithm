#include <iostream>

using namespace std;

#define MAXN 100010

int n, m;

int num[MAXN][32];
int m2Array[32];

bool check(int l, int r) {
    int i;
    l--;
    if(num[r][0] < m2Array[0]) {
        return true;
    }
    
    for(i = num[r][0]; i >= 1; i--) {
        int pre = ( i <= num[l][0] ? num[l][i] : 0);
        int delta = num[r][i] - pre ? 1 : 0;
        int cmpv = (i <= m2Array[0] ? m2Array[i] : 0);
        if( delta < cmpv ) {
            return true;
        }else if( delta > cmpv ){
            return false;
        }
    }
    return false;
}

int main() {
    int t, cases = 0;
    int i, j;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d %d", &n, &m);
        m2Array[0] = 0;
        while(m) {
            m2Array[ ++m2Array[0] ] = m & 1;
            m >>= 1;
        }
        int maxsize = 0;
        
        for(i = 1; i <= n; i++) {
            int val, size = 0;
            scanf("%d", &val);

            while(val) {
                num[i][ ++size ] = val&1;
                val >>= 1;
            }
            if(size > maxsize) {
                maxsize = size;
            }
            for(j = size+1; j <= maxsize; j++) {
                num[i][j] = (j <= num[i-1][0] ? num[i-1][j] : 0);
            }
            for(j = 1; j <= size; j++) {
                num[i][j] += (j<=num[i-1][0] ? num[i-1][j] : 0);
            }
            num[i][0] = maxsize;
            
            // test
            /*printf("%d\n", maxsize);
            for(j = 1; j <= maxsize; j++) {
                printf("%d ", num[i][j]);
            }
            puts("");*/
        }
        
        __int64 res = 0;
        for(i = 1; i <= n; i++) {
            int l = i, r = n, ans = i-1;
            while(l <= r) {
                int mid = (l + r) >> 1;
                if( check(i, mid) ) {
                    ans = mid;
                    l = mid + 1;
                }else {
                    r = mid - 1;
                }
            }
            res += ans - i + 1;
            //printf("%d %d\n", i, ans);
        }
        printf("Case #%d: %I64d\n", ++cases, res);
    }
    return 0;
}

