#include <iostream>
#include <cstring>
using namespace std;

#define MAXH 15

char hooks[MAXH+2][MAXH+2];
int rowset[MAXH];

int lowbit(int x) {
    return x & -x;
}

int Cnt1[65537];
int cnt1(int x) {
    int cnt = 0;
    while(x) {
        cnt ++;
        x ^= lowbit(x);
    }
    return cnt;
}

int Min(int a, int b) {
    return a < b ? a : b;
}
int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int i, j, k;
    for(i = 0; i < (1<<15); ++i) {
        Cnt1[i] = cnt1(i);
    }
    while(scanf("%s", hooks[0]) != EOF) {
        if(hooks[0][0] == 'E') break;
        for(i = 1; i < MAXH; ++i) {
            scanf("%s", hooks[i]);
        }
        int ans = 10000;
        for(i = 0; i < (1<<MAXH); ++i) {
            if(Cnt1[i] >= ans) {
                continue;
            }
            memset(rowset, 0, sizeof(rowset));
            for(j = 0; j < MAXH; ++j) {
                if( ((1<<j) & i) == 0 ) {
                    for(k = 0; k < MAXH; ++k) {
                        if(hooks[k][j] == '#') {
                            rowset[k] = 1;
                        }
                    }
                }
            }
            int v = 0;
            for(j = 0; j < MAXH; ++j) {
                v += rowset[j];
            }
            v = Max( Cnt1[i], v );
            ans = Min(ans, v);
        }
        printf("%d\n", ans);
    }
    return 0;
} 
