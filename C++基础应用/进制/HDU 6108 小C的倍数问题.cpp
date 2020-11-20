/*
    题意：给定进制P，求有多少个B满足P进制下，一个正整数是B的倍数的充分必要条件是每一位加起来的和是B的倍数。
    题解：求P-1的因子数
*/
#include <iostream>

using namespace std;

int P;

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &P);
        --P;
        int ans = 0;
        for(i = 1; i*i <= P; ++i) {
            if(P % i == 0) {
                if(i*i == P) {
                    ++ans;
                }else {
                    ans += 2;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}