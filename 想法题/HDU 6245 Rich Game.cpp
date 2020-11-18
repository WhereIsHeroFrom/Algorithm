/*
题意：
    小明和老王进行羽毛球比赛。规则如下：
        1、对于每一场比赛，如果小明赢了1分，则小明付给老王X块钱；如果小明输了1分，则老王付给小明Y块钱；
        2、谁先拿到11分并且领先对方2分，则为该场比赛的赢家；
    假设小明有无限多的钱，而老王没钱，但是老王聪明啊，可以自由掌控每场比赛的得分。
    问K场比赛下来，老王最多可以赢几场。

题解：
    分情况讨论：
        1、当 X > Y 时，答案为K。
            对于每一局，都可以这么干：
            让老王先输1分（获得X），再赢一分（失去Y），再输1分（获得X），再赢一分（失去Y）... 依次往复...
            2n回合以后老王积累了n(X-Y)，然后一举赢掉2分获取该局比赛胜利（因为当n足够大，可以保证资金（n(X-Y) - 2Y）还是大于0的）。
        2、当 9X - 11Y >= 0，答案为K。
            对于每一局，老王以11:9赢下比赛还能获得额外的钱，所以K场都赢即可。
        3、剩下的情况，
            令A = 11X，B = 9X - 11Y
            n代表赢的场数，那么K-n就是输的场数，需要保证 A(K-n) + nB >= 0得 n <= AK / (A - B)
            所以答案就是 AK / (A - B) 的下取整。
*/


#include <iostream>

using namespace std;

int solve(int X, int Y, int K) {
    if(X > Y) {

        return K;
    }
    int A = 11*X;             // Mr. Panda lose
    int B = 9*X - 11*Y;       // Mr. Panda win
    if(B >= 0) {
        return K;
    }
    return A * K / (A - B);
}

int main() {
    int t = 0, cases;
    int X, Y, K;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d%d", &X, &Y, &K);
        printf("Case #%d: %d\n", ++t, solve(X, Y, K));
    }
    return 0;
} 