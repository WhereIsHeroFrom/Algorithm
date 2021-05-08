#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
#pragma warning(disable : 4996)
const int mod = 8;
char ch[1000010];

bool multipleof(char* ch, int mod) {
    int s = 0;
    for (int i = 0; ch[i]; ++i) {
        s = s * 10 + ch[i] - '0';
        s %= mod;
    }
    return !s;
}
bool issumdigit_multipleof(char* ch, int mod) {
    int s = 0;
    for (int i = 0; ch[i]; ++i) {
        s = s + ch[i] - '0';
        s %= mod;
    }
    return !s;
}
int sqr(int x) {
    return x * x;
}

bool issumdigit_square_multipleof(char* ch, int mod) {
    int s = 0;
    for (int i = 0; ch[i]; ++i) {
        s = s + sqr(ch[i] - '0');
        s %= mod;
    }
    return !s;
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", ch);

        if (multipleof(ch, mod) || issumdigit_multipleof(ch, mod) || issumdigit_square_multipleof(ch, mod)) {
            puts("Lucky number!");
        }
        else {
            puts("What a pity!");
        }

    }
    return 0;
}