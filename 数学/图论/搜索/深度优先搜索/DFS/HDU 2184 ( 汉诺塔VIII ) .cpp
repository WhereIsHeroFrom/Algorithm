#include <iostream>

using namespace std;

#define LL __int64

LL n, m;
int a[3][100];
void dfs(LL n, LL m, int from, int buffer, int to) {
    LL o = ((LL)1<<(n-1));
    if(n == 0) {
        return ;
    }

    if(m < o) {
        a[from][ ++a[from][0] ] = n;
        dfs(n-1, m, from, to, buffer);
    }else {
        m -= o;
        a[to][ ++a[to][0] ] = n;
        dfs(n-1, m, buffer, from, to);
    }
}

int main() {
    int t, i, j;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%I64d %I64d", &n, &m);
        a[0][0] = a[1][0] = a[2][0] = 0;
        dfs(n, m, 0, 1, 2);
        for(i = 0; i < 3; ++i) {
            printf("%d", a[i][0]);
            for(j = 1; j <= a[i][0]; ++j) printf(" %d", a[i][j]);
            puts("");
        }
    }
    return 0;
}

/*
3
3 2
4 5
39 183251937942


1 3
1 2
1 1
2 4 1
1 3
1 2
13 39 36 33 30 27 24 21 18 15 12 9 4 1
12 38 35 32 29 26 23 20 17 14 11 8 5
14 37 34 31 28 25 22 19 16 13 10 7 6 3 2
*/
