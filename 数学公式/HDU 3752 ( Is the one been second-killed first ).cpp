#include <iostream>

using namespace std;

bool check(int m, int n) {
    if(m < 2*n) {
        return false;
    }
    return (m-2*n) % 2 ? false : true; 
}

int main() {
    int t;
    int m, n;
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &m, &n);
        printf("%s\n", check(m,n) ? "YES": "NO");
    }
    return 0;
} 
