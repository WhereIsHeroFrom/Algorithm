#include <iostream>
#include <cstring>

using namespace std;

int has[1010];

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        memset(has, 0, sizeof(has));
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            has[x] = 1;
        }
        int c[3] = {0};
        for(int i = 1; ; ++i) {
            if(!has[i]) {
                c[++c[0]] = i;
                if(c[0] == 2) break;
            }
        }
        printf("%d %d\n", c[1], c[2]);
    }
    
    
    return 0;
} 
