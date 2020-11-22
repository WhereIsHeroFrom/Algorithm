#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAXL 110
#define NULL_POS -1

int len;
char v[] = "1234567890";
char str[MAXL];
int dp[10][10][MAXL];

struct state {
    int l, r, pos;
    int step;
    state() {
    }
    state(int _l, int _r, int _pos, int _step) {
        l = _l;
        r = _r;
        pos = _pos;
        step = _step;
    }
    bool isEnd() {
        return pos == len;
    }

    bool inValid() {
        return (l >= r) || l < 0 || l > 9 || r < 0 || r > 9;
    }
};

int dir[2] = {-1, 1};
int exdir[3] = {-1, 0, 1};

int bfs() {
    int i, j;
    int ans = 10000000;
    queue <state> Q;
    Q.push(state(4, 5, 0, 0));

    state ns;
    while(!Q.empty()) {
        state s = Q.front();
        Q.pop();

        if(s.isEnd()) {
            if(s.step < ans) {
                ans = s.step;
            }
            continue;
        }
        
        // 移动左、右手指
        for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
                ns = state(NULL_POS, s.r, s.pos, s.step+1);
                ns.l = (s.l + dir[i]);
                ns.r = (s.r + dir[j]);
                if(ns.inValid()) continue;
            
                if(ns.step < dp[ns.l][ns.r][ns.pos]) {
                    dp[ns.l][ns.r][ns.pos] = ns.step;
                    Q.push(ns);
                }
            }
        }

        // 左手指按下同时，右手指移动
        ns = state(s.l, s.r, s.pos + 1, s.step + 1);
        if(v[ns.l] == str[ns.pos]) {
            for(i = 0; i < 3; i++) {
                ns.r = s.r + exdir[i];
                if(ns.inValid()) continue;

                if(ns.step < dp[ns.l][ns.r][ns.pos]) {
                    dp[ns.l][ns.r][ns.pos] = ns.step;
                    Q.push(ns);
                }
            }
        }

        // 右手指按下同时，左手指移动
        ns = state(s.l, s.r, s.pos + 1, s.step + 1);
        if(v[ns.r] == str[ns.pos]) {
            for(i = 0; i < 3; i++) {
                ns.l = s.l + exdir[i];
                if(ns.inValid()) continue;

                if(ns.step < dp[ns.l][ns.r][ns.pos]) {
                    dp[ns.l][ns.r][ns.pos] = ns.step;
                    Q.push(ns);
                }
            }
        }
        
    }
    return ans;
}

void init() {
    int i, j, k;
    for(i = 0; i < 10; ++i) {
        for(j = 0; j < 10; ++j) {
            for(k = 0; k < MAXL; ++k) {
                dp[i][j][k] = 10000000;
            }
        }
    }
}

int main() {
    while(scanf("%s", &str[1]) != EOF) {
        init();
        len = strlen(&str[1]);
        printf("%d\n", bfs());
    }
    return 0;
}
