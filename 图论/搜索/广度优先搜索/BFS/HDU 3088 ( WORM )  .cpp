#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

char str[20];

int code(char c) {
    if(c == 'r') return 0;
    if(c == 'g') return 2;
    if(c == 'b') return 1;
}

int state(char *str) {
    int i;
    int st = 0, base = 1;
    for(i = 0; str[i]; ++i) {
        st += code(str[i]) * base;
        base *= 3;
    }
    return st;
}

int step[11][3][59050];

int getInitState(int len, int c) {
    int i, st = 0;
    for(i = 0; i < len; ++i) {
        st = st * 3 + c;
    }
    return st;
}

int p[11];

int get_bit(int state, int pos) {
    return state / p[pos] % 3;
}

int change_to(int state, int pos, int nowbit, int idx) {
    int d[2];
    if(nowbit == 0) {
        d[0] = 1;
        d[1] = 2;
    }else if(nowbit == 1) {
        d[0] = 0;
        d[1] = 2;
    }else if(nowbit == 2) {
        d[0] = 0;
        d[1] = 1;
    }
    if(idx) {
        int tmp = d[0]; d[0] = d[1]; d[1] = tmp;
    }
    return state + (d[0] - nowbit)*p[pos]  + (d[1] - nowbit)*p[pos+1];
}

void bfs(int state, int len, int idx) {
    queue <int> Q;
    Q.push(state);
    int i, j;
    int bit[11];
    step[len][idx][state] = 0;


    while(!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for(i = 0; i < len; ++i) {
            bit[i] = get_bit(now, i);
        }
        for(i = 0; i < len - 1; ++i) {
            if(bit[i] == bit[i+1]) {
                for(j = 0; j < 2; ++j) {
                    int next = change_to(now, i, bit[i], j);
                    if(step[len][idx][next] == -1) {
                        step[len][idx][next] = step[len][idx][now] + 1;
                        Q.push(next);
                    }
                }
            }    
        }
    }
}

int main() {
    int t;
    int i, j, k;
    p[0] = 1;
    for(i = 1; i < 11; ++i) {
        p[i] = p[i-1] * 3;
    }
    memset(step, -1, sizeof(step));
    for(i = 1; i <= 10; ++i) {
        for(j = 0; j < 3; ++j) {
            int st = getInitState(i, j);
            bfs(st, i, j);
        }
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        int len = strlen(str);
        int st = state(str);
        int min = -1;
        for(i = 0; i < 3; ++i) {
            if(step[len][i][st] == -1) continue;
            if(step[len][i][st] < min || min == -1) {
                min = step[len][i][st];
            }
        }
        if(min == -1) printf("No solution!\n");
        else printf("%d\n", min);
    }
    return 0;
}
