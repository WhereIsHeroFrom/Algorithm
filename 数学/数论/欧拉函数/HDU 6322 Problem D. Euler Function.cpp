#include <iostream>
using namespace std;

int main() {
    int t, n;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d", &n);
        if(n == 1) {
            printf("%d\n", 5);
        }else {
            printf("%d\n", n + 5);
        }
    }
    return 0;
} 
