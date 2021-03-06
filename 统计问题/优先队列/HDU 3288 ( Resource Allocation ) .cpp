#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 10010

struct Item {
    int pri, time;

    Item() {}

    Item(int p, int t) {
        pri = p;
        time = t;
    }
    friend bool operator < (Item now, Item other);

};
bool operator < (Item now, Item other) {
    if(now.pri == other.pri) {
        return now.time > other.time;
    }
    return now.pri > other.pri;
}
priority_queue <Item> Q[MAXN];

int main() {
    int t;
    int i;
    while(scanf("%d", &t) != EOF) {
        for(i = 0; i < MAXN; ++i) {
            while(!Q[i].empty()) Q[i].pop();
        }
        int T = 0;
        while(t--) {
            char cmd[10];
            scanf("%s", cmd);
            if(strcmp(cmd, "R") == 0) {
                ++T;
                int x, y;
                scanf("%d %d", &x, &y);
                Q[x].push(Item(y, T));
            }else {
                int x;
                scanf("%d", &x);
                if(Q[x].empty()) {
                    printf("No one fits!\n");
                }else {
                    Item v = Q[x].top();
                    Q[x].pop();
                    printf("%s gets Num %d: %d %d!\n", cmd, v.time, x, v.pri);
                }
            }
        }
    }
    return 0;
}
