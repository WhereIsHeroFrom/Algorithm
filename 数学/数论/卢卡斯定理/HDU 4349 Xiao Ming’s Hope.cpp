#include <iostream>

using namespace std;

int exp(int a, int b) {
    if(b == 0) {
        return 1;
    }
    int tmp = exp(a*a, b/2);
    if(b & 1) tmp *= a;
    return tmp;
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        int cnt = 0;
        while(n) {
            n &= n - 1;
            ++cnt;
        }
        printf("%d\n", exp(2, cnt));
    }
    return 0;
}
