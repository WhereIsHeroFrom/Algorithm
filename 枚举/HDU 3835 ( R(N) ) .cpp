#include <iostream>
#include <cmath>
using namespace std;

#define eps 1e-6

int main() {
    int n, A, B, BB, maxA;
    while(scanf("%d", &n) != EOF) {
        if(!n) {
            printf("1\n");
            continue;
        }else if(n < 0) {
            printf("0\n");
            continue;
        }
        
        maxA = int(sqrt(n*1.0) + eps);
        int ans = 0;
        for(A = 0; A <= maxA; ++A) {
            BB = (n - A*A);
            if(BB < 0) {
                break;
            }
            B = int(sqrt(BB*1.0) + eps);
            if(B * B == BB) {
                if(A == 0 || B == 0) {
                    ans += 2;
                }else {
                    ans += 4;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
} 
