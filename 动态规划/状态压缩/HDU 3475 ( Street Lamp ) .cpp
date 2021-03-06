#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

#define MAXN 210
#define MAXM 10
#define MAXL 2000
#define INV -1 
#define DIR 8

int n, m;
char mat[MAXN][MAXN];
int Mask[MAXN];
int Lamp[MAXN][MAXM][DIR];
int dp[2][1<<MAXM][1<<MAXM];
int isDp[2][1<<MAXM][1<<MAXM], cases;
int midx[MAXM+1][MAXM+1];

vector <int> stateOp[1<<MAXM];
vector <int> states[2];

int opOneCnt[1<<MAXM];

/*
    获取每一行灯的开关情况，以二进制表示存储在mask中
    如：*-*-*-o-o-o-* 的二进制表示为 1110001 
*/
void getMask() {
    int i, j;
    for(i = 0; i < 2*n - 1; ++i) {
        j = 0;
        Mask[i] = 0;
        while(mat[i][j]) {
            if(mat[i][j] == '*' || mat[i][j] == 'o') {
                Mask[i/2] = Mask[i/2] << 1 | (mat[i][j] == '*'?1:0);
            }
            ++j;
        }
    }
}


/*
    Lamp是一个八向链表
     0 1 2
     3 * 4
     5 6 7 
*/
int dir[8][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
};

/*
    对八向链表进行链接 
*/
void getLink() {
    int i, j;
    memset(Lamp, 0, sizeof(Lamp));
    
    for(i = 0; i < 2*n - 1; ++i) {
        j = 0; 
        while(mat[i][j]) {
            char c = mat[i][j];
            if(c == '-') {
                Lamp[i/2][ (j-1)/2 ][4] = 1;
                Lamp[i/2][ (j+1)/2 ][3] = 1;
            }else if(c == '|') {
                Lamp[i/2][ j/2 ][6] = 1;
                Lamp[i/2+1][ j/2 ][1] = 1;
            }
            if(c == '\\' || c == 'X') {
                Lamp[i/2][ j/2 ][7] = 1;
                Lamp[i/2+1][ j/2+1 ][0] = 1;
            }
            
            if(c == '/' || c == 'X') {
                Lamp[i/2][ j/2+1 ][5] = 1;
                Lamp[i/2+1][ j/2 ][2] = 1;
            }
            ++j;
        }
    }
}

/*
    单个操作的枚举 
*/
void enumSingleOp(int row, int op) {
    int oMask = (1<<m)-1; 
    for(int col = 0; col < m; ++col) {
        int isNeed = (op >> (m-1-col) & 1);
        if(!isNeed) continue;
        // 只负责检查上一行的影响情况 
        for(int i = 0; i < 3; ++i) {
            if( Lamp[row][col][i] ) {
                oMask ^= 1<<(m-(col+dir[i][1])-1);
            }
        }
    }
    stateOp[oMask].push_back(op);
}

/*
    枚举第row行的所有操作op，生成上一行的被影响情况，
那么，将这个被影响情况取反，得到的就是上一行应该有的状态
将这个操作op插入到对应状态的链表中 
*/ 
void enumOp(int row) {
    int opcnt = (1<<m);
    int i;
    for(i = 0; i < opcnt; ++i) {
        enumSingleOp(row, i);
    }    
}

void stateTranslate(int row, int p, int effect, int op, int ans) {
    int now = effect;
    int next = 0;
     
    for(int col = 0; col < m; ++col) {
        int isNeed = (op >> (m-1-col) & 1);
        if(!isNeed) continue;
        
        // 自己改变状态别忘了
        now ^= 1<<(m-col-1);
 
        for(int i = 3; i < 8; ++i) {
            if( Lamp[row][col][i] ) {
                int dr = dir[i][0];
                if(dr == 0)
                    now ^= 1<<(m-(col+dir[i][1])-1);
                else if(dr == 1) 
                    next ^= 1<<(m-(col+dir[i][1])-1);
            }
        }
    }
    int &dpv = isDp[p^1][now][next];
    if(dpv < cases || ans < dp[p^1][now][next]) {
        if(dpv < cases) {
            states[p^1].push_back(now << 16 | next);
        }
        dpv = cases;
        dp[p^1][now][next] = ans;
    }
}

int solve() {
    int i, j, k;
    int tot = (1<<m);
    // 初始化状态
    states[0].clear();
    states[1].clear();
    ++cases;
    dp[0][tot-1][0] = 0;
    isDp[0][tot-1][0] = cases;
    states[0].push_back( (tot-1) << 16 | 0 ); 
    ++cases;
    int p = 0; 
    for(i = 0; i < n; ++i) {
        for(j = 0; j < tot; ++j) {
            stateOp[j].clear();
        }
        states[p^1].clear();
        enumOp(i);
        
        for(j = states[p].size()-1; j >= 0; --j) {
            // 上一行的状态 
            int state = states[p][j] >> 16;
            // 对当前行的影响 
            int effect = states[p][j] & 65535;
            
            if(stateOp[state].size()) {
                //printf("state = %d\n", state);
                for(k = stateOp[state].size()-1; k >= 0; --k) {
                    int &op = stateOp[state][k];
                    //printf("%d ", op);
                    stateTranslate(i, p, (effect^Mask[i]), op, dp[p][state][effect] + opOneCnt[op]);
                }
                //puts("");
            } 
        }
        p ^= 1; 
        ++cases;
    }
    if(isDp[p][tot-1][0] < cases - 1) {
        return -1;
    }
    return dp[p][tot-1][0]; 
}
int main() {
    int t;
    int i;
    int cc = 0;
    for(i = 0; i < 1<<MAXM; ++i) {
        opOneCnt[i] = 0;
        int v = i;
        while(v) {
            opOneCnt[i] += (v&1);
            v >>= 1;
        }
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        getchar();
        for(i = 0; i < 2*n - 1; i++) {
            gets(mat[i]);
        }
        getMask();
        getLink();
        printf("Case %d: %d\n", ++cc, solve());
    }
    return 0;
}

/*
45
2 2
*-o
 \ 
o-*

40
3 3
o-o-o
|X|X|
o-o-o
|X|X|
o-o-o
*/
