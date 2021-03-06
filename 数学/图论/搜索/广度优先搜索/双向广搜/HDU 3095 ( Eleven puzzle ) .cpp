#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define LL long long

#define BASE 13
#define BLOCK_CNT 13
#define HASH_MAX ((1<<19)-1)
int hashCases;
int hashKey[HASH_MAX+1];
LL hashValue[HASH_MAX+1];
LL basePower[BLOCK_CNT];

void initBasePower() {
    int i;
    basePower[0] = 1;
    for(i = 1; i < BLOCK_CNT; ++i) {
        basePower[i] = basePower[i-1] * BASE;
    }
}

int encode(int src[BLOCK_CNT]) {
    int i;
    LL value = 0;
    for(i = 0; i < BLOCK_CNT; ++i) {
        value += basePower[i] * src[i];
    }
    int now = (value & HASH_MAX);
    while(1) {
        if(hashKey[now] < hashCases) {
            hashKey[now] = hashCases;
            hashValue[now] = value;
            return now;
        }else {
            if(hashValue[now] == value) {
                return now;
            }
            now = (now + 1) & HASH_MAX;
        }
    }
}

void decode(int state, int src[BLOCK_CNT]) {
    LL nstate = hashValue[state];
    int i;
    for(i = 0; i < BLOCK_CNT; ++i) {
        src[i] = nstate/basePower[i]%BASE;
    }
}

void swapValue(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

int swapList[BLOCK_CNT][5] = {
    {2, -1},
    {2, 5, -1},
    {0, 1, 3, 6, -1},
    {2, 7, -1},
    {5, -1},
    {1, 4, 6, 9, -1},
    {2, 5, 7, 10, -1},
    {3, 6, 8, 11, -1},
    {7, -1},
    {5, 10, -1},
    {6, 9, 11, 12, -1},
    {10, 7, -1},
    {10, -1},
};

int step[2][HASH_MAX+1];
#define MAX_STEP 20

int bfs(int src[BLOCK_CNT], int tar[BLOCK_CNT]) {
    queue <int> Q[2];
    memset(step, -1, sizeof(step));
    int startState = encode(src), endState = encode(tar);
    step[0][startState] = step[1][endState] = 0;

    Q[0].push(startState);
    Q[1].push(endState);

    int p = 0;
    int i, j;
    int ans = -1;
    while(!Q[0].empty() || !Q[1].empty()) {
        while(!Q[p].empty()) {
            int now = Q[p].front();
            Q[p].pop();

            if(step[p^1][now] != -1) {
                int nAns =step[p^1][now] + step[p][now];
                if(nAns <= MAX_STEP) {
                    return nAns;
                }
            }            
            if(step[p][now] == MAX_STEP/2+1) break;

            // 将now状态分拆到src数组
            decode(now, src);
            for(i = 0; i < BLOCK_CNT; ++i) {
                for(j = 0; j < 5; ++j) {
                    int u = i, v = swapList[i][j];
                    if(v == -1) break;
                    if(src[u] == src[v]) continue;
                    if(src[u] && src[v]) continue;
                    // 交换
                    swapValue(src[u], src[v]);

                    // 生成新的状态
                    int next = encode(src);
                    if(step[p][next] == -1) {
                        step[p][next] = step[p][now] + 1;
                        Q[p].push(next);
                    }
                    // 交换回来
                    swapValue(src[u], src[v]);
                }
            } 

        }
        p ^= 1;
    }
    return ans;
}

int state[2][BLOCK_CNT];
int main() {
    int t;
    int i;
    initBasePower();
    for(i = 0; i < BLOCK_CNT; ++i) {
        state[1][i] = (i==BLOCK_CNT-1)?0 : i;
    }
    scanf("%d", &t);
    while(t--) {
        ++hashCases;
        for(i = 0; i < BLOCK_CNT; ++i) {
            scanf("%d", &state[0][i]);
        }
        int ans = bfs(state[0], state[1]);
        if(ans == -1) {
            printf("No solution!\n");
        }else {
            printf("%d\n", ans);
        }
    }
    return 0;
}
/*
1212
0 1 2 3 4 5 6 7 8 9 10 11 0
2 1 0 3 4 5 6 7 8 9 10 11 0
2 0 1 3 4 5 6 7 8 9 10 11 0
2 5 1 3 4 0 6 7 8 9 10 11 0
2 5 1 3 0 4 6 7 8 9 10 11 0
2 5 1 3 0 4 6 7 8 9 0 11 10
2 5 1 3 0 4 6 7 8 9 11 0 10
2 5 1 3 0 4 6 0 8 9 11 7 10
2 5 1 3 0 4 6 8 0 9 11 7 10

*/

