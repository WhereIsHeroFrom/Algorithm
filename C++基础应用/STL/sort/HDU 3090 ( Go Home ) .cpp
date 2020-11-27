#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100010

struct Point {
    int d, p;
    void read() {
        scanf("%d %d", &d, &p);
    }
    bool operator<(const Point& other) {
        return p > other.p;
    }

    int value() {
        return d * p;
    }

}P[MAXN];

int n, m;

int main() {
    int i;
    while(scanf("%d %d", &n, &m) != EOF) {
        if(!n && !m) break;
        for(i = 0; i < n; ++i) {
            P[i].read();
        }
        sort(P, P + n);
        int ans = 0;
        for(i = 0; i < n; ++i) {
            if(!P[i].p) continue;
            if(m >= P[i].d) {
                m -= P[i].d;
            }else {
                P[i].d -= m;
                m = 0;
                ans += P[i].value();
            }
        }
        printf("%d\n", ans);

    }
    return 0;
}
