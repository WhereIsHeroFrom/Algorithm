#include <iostream>
#include <algorithm>
using namespace std;

int A[20];

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int c;
        scanf("%d", &c);
        for(int i = 0; i < 10; i++) {
            scanf("%d", &A[i]);
        }
        sort(A, A+10);
        printf("%d %d\n", c, A[7]);
    }
    return 0;
}

