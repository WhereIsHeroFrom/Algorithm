#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 50
int has[MAXN];

int main() {
    int n;
    int i, j;
    while(scanf("%d", &n) != EOF && n) {
        memset(has, 0, sizeof(has));
        for(i = 0; i < n; ++i) {
            for(j = 0; j < 6; ++j) {
                int v;
                scanf("%d", &v);
                if(v >= 1 && v <= 49) has[v] ++;
            }
        }
        for(i = 1; i< 50; ++i) {
            if(has[i] == 0) break;
        }
        printf("%s\n", i==50 ? "Yes": "No");
    }
    return 0;
}
