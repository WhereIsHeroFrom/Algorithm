#include <iostream>
#include <cstring>
using namespace std;

#define MAXL 30

char dict[5100][MAXL];
int len[5100];
char str[MAXL];
int m;

int ismatch(int l1, char* str1, int l2, char* str2) {
    int i, j = 0;
    for(i = 0; i < l2; ++i) {
        if(str1[j] == str2[i]) {
            ++j;
            if(j == l1) return 1;
        }
    }
    return 0;
}
int main() {
    int i;
    while(scanf("%d", &m) != EOF) {
        for(i = 0; i < m; ++i) {
            scanf("%s", dict[i]);
            len[i] = strlen(dict[i]);
        }
        int q;
        scanf("%d", &q);
        while(q--) {
            scanf("%s", str);
            int l = strlen(str);
            int ans = 0;
            for(i = 0; i < m; ++i) {
                ans += ismatch(l, str, len[i], dict[i]);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
