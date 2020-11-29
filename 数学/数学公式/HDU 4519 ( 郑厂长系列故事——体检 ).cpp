#include <iostream>

using namespace std;
int n, m, k;
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d", &n, &k, &m);
        if(m > n) {
            m = n;
        }
        printf("%d\n", (n*k+m-1)/m );
    }
}

