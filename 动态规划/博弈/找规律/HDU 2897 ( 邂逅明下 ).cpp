#include <iostream>

using namespace std;

int main() {
    int n, p, q;
    while( scanf("%d%d%d", &n, &p, &q) != EOF) {
        n %= (p+q);
        if(n==0) n += (p+q);
        printf("%s\n", n>p? "WIN": "LOST");
    }
    return 0;
}

