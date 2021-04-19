#include <iostream>
#include <cmath>
using namespace std;

#define ll long long

ll n;
int ansSize;

struct Interval {
    int l, r;
    Interval() {
        l = r = 0;
    }
    Interval(int _l, int _r) : l(_l), r(_r) {
    }
    void print() {
        printf("%d", r-l+1);
        for (int i = l; i <= r; ++i) {
            printf(" %d", i);
        }
        puts("");
    }

}I[1000000];

int main() {
    while (scanf_s("%lld", &n) != EOF) {
        ll s = 0;
        ll i = 1, j = 0;
        ansSize = 0;
        while (j * j <= n) {
            ++j;
            s += j * j;
            while (s > n) {
                s -= i * i;
                ++i;
            }
            if (s == n) {
                I[ansSize++] = Interval(i, j);
            }
        }
        printf("%d\n", ansSize);
        for (int i = 0; i < ansSize; ++i) {
            I[i].print();
        }
    }
    return 0;
}

