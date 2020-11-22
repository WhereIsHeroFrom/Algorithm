#include <iostream>

using namespace std;

#define MAXN 1000010
 
int a[MAXN];
int n;

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        a[n] = 0;
        int idx = 0;
        bool flag = 0;
        while(idx < n) {
            if(a[idx] > a[idx+1]) {
                flag = 1;
                printf("I will never go out T_T\n");
                break;
            }else {
                a[idx+1] -= a[idx];
                a[idx] = 0;
                ++idx;
            }
        }
        
        if(!flag) {
            printf("yeah~ I escaped ^_^\n");
        }
    }    
    return 0;
} 
