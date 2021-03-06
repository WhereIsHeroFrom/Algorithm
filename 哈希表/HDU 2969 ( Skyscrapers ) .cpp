#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1000100

int has[MAXN], T;

struct Item {
    int idx;
    int height;
    
    friend bool operator < (Item a, Item b) {
        return a.height > b.height;
    }
    
    void read(int _idx) {
        idx = _idx;
        scanf("%d", &height);
    }
    
    void print() {
        printf("h[%d] = %d\n", idx, height);
    }
    
}I[MAXN];

int n, d;
int days[MAXN], ans[MAXN];

int main() {
    int t;
    int i, j, k;
    scanf("%d", &t);
    while( t-- ) {
        T ++;
        scanf("%d %d", &n, &d);
        for(i = 0; i < n; i++) {
            I[i].read(i + 1);
        }
        for(i = 0; i < d; i++) {
            scanf("%d", &days[i]);
        }
        sort(I, I + n);
        
        //for(i = 0; i < n; i++) {
        //    I[i].print();
        //}
        
        int start = 0;        
        int blocks = 0;
        ans[d] = 0;
        
        for(i = d-1; i >= 0; i--) {
            for(j = start; j < n; j++) {
                if(I[j].height <= days[i]) {
                    break;
                }
            }
            //printf("<%d, %d>\n", start, j-1);
            // (start, j-1) 这一段是当前这次浮上来的块块
            if( start < j ) {
                for(k = start; k < j; k++) {
                    has[ I[k].idx ] = T;
                    
                    int left = has[ I[k].idx - 1 ];
                    int right = has[ I[k].idx + 1 ];
                    if( left < T && right < T ) {
                        blocks += 1;
                    }else if( left < T && right == T || left == T && right < T) {
                        blocks += 0;
                    }else {
                        blocks -= 1;
                    }
                }
                ans[i] = blocks;
            }else {
                ans[i] = ans[i+1];
            }
            start = j;
        }
        for(i = 0; i < d; i++) {
            printf("%d ", ans[i]);
        }
        puts("");
    }
    
    return 0;
}

/*
10
3 3
1 2 3
1 2 3
5 3
1 3 5 1 3
0 2 4
*/
