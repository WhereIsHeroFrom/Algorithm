#include <iostream>
#include <cmath>
using namespace std;

int m;

int main() {
    int cas = 0;
    while(scanf("%d", &m) != EOF) {
        int ans = m * log(2.0) / log(10.0);
        printf("Case #%d: %d\n", ++cas, ans);
    }
    return 0;
} 
