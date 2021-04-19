#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;


#pragma warning(disable : 4996)

const int maxn = 10000010;
char c[maxn];
int n;
int h[256];

int getmaxlen(int n, char *str, int& l, int& r) {
    int ans = 0, i, j, len;
    memset(h, 0, sizeof(h));
    for(i = 0; i < n; ++i) {                // 1)
        j = i;
        memset(h, false, sizeof(h));        // 2)
        while(j < n && !h[str[j]]) {
            h[ str[j] ] = true;             // 3)
            len = j - i + 1;
            if(len > ans)
                ans = len, l = i, r = j;
            ++j;
        }
        printf("[%d %d]\n", i, j - 1); 
    }
    return ans;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        scanf("%s", c);
        int l, r;
        int ans = getmaxlen(n, c, l, r);
        printf("%d %d %d\n", ans, l, r);
    }
    return 0;
}

/*
3
abc
5
aaaba
8
hdugirls

8
abcaedca

*/
