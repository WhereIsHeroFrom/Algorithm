#include <iostream>
#include <algorithm>
using namespace std;


int a[110];

bool findv(int l, int r, int val) {
    if(val > a[r]) {
        return false;
    }    
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(val == a[mid]) return true;
        if(val > a[mid]) {
            l = mid + 1;
        }else {
            r = mid - 1;
        }
    }
    return false;
}

bool findit(int n) {
    for(int i = 0;i < n;  ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(findv(j+1, n-1, a[i] + a[j]) ) {
                return true;
            }
        }
    }     
    return false;
}
int main() {
    int n;
    while( scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }        
        sort(a, a + n);
        printf("%s\n", findit(n) ? "YES": "NO");
    }
    
    return 0;
} 
