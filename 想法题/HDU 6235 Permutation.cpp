/*
题意：
    对于一个排列p1, p2, ... , pn，如果满足任意的pi使得pi mod |pi - pi-1| == 0，则称这个排列为完美排列。
    给定1个n，求一个长度为n的完美排列。

题解：
    因为，任何数被1模都为0，所以相邻两个自然数（差为1）一定满足pi mod |pi - pi-1| == 0（如 6 % |6-5| == 0）
    所以，可以将排列的第1,3,5...这些位置用 [n/2+1, n]进行填充，第2,4,6...这些位置用[1, n/2]进行填充。
*/

#include <iostream>

using namespace std;

int main() {
    int cases;
    int n, i;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            int v = 0;
            if(i & 1) {
                v = (i+1) >> 1;
            }else {
                v = ((n+i) >> 1) + 1;
            }
            printf("%d%c", v, i==n-1?'\n':' ');
        }
    }
    return 0;
} 