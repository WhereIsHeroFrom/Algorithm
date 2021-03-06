#include <iostream>
#include <queue>
#include <cstring>

//#include <windows.h>
using namespace std;

#define MAXR 4
#define MAXC 6 
#define p2(x) (1<<(x))

// 2^21 - 1
#define MOD ((1<<21)-1)

char colors[4] = "BGW";

int getcode(char c) {
    for(int i = 0; i < 3; i++) {
        if(c == colors[i]) return i;
    }
}
// 取二进制的某一位的值
// pos = [0, MAXC)
int getBit(int v, int pos) {
    return (v & (1<<pos)) ? 1 : 0;
}
 
// 六位的二进制整数循环左移一位 
int getLeftShift(int v) {
    int cycBit = getBit(v, MAXC-1);
    return ( v & ( p2(MAXC-1)-1 ) ) << 1 | cycBit;
} 

// 六位的二进制整数循环右移一位
int getRightShift(int v) {
    return (v&1) << (MAXC-1) | (v >> 1);    
}

// 四个六位的二进制整数的第k位进行循环上(下)移
void upDownShiftK(int v[MAXR], int k, bool up) {
    int i, kbit[MAXR];
    int dir = up ? 1 : MAXR-1;
    
    for(i = 0; i < MAXR; i++) {
        kbit[i] = getBit(v[i], k);
    }
    for(i = 0; i < MAXR; i++) {
        int nb = getBit(v[i], k);
        if( nb != kbit[ (i+dir)%MAXR ] ) {
            v[i] ^= 1<<k;
        }
    }
}

void swap_int(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int packState(int v[MAXR]) {
    int i, tmp[MAXR];
    
    for(i = 0; i < MAXR; i++) {
        tmp[i] = v[i];
    }
    // 状态最小表示 
    if(v[0] > v[3] || v[0] == v[3] && v[1] > v[2] ) {
        swap_int(&tmp[0], &tmp[3]);
        swap_int(&tmp[1], &tmp[2]);    
    }
    
    int now = 0;
    for(i = MAXR-1; i >= 0; i--) {
        now = now | tmp[i];
        if(i)
            now <<= MAXC;
    }
    return now;
}

void unpackState(int now, int v[MAXR]) {

    
    for(int i = 0; i < MAXR; i++) {
        v[i] = now & ( p2(MAXC) - 1 );
        now >>= MAXC;
    }
    
    // 状态最小表示 
    if(v[0] > v[3] || v[0] == v[3] && v[1] > v[2] ) {
        swap_int(&v[0], &v[3]);
        swap_int(&v[1], &v[2]);    
    }    
}

int stateTransform(int now, int idx) {
    int v[MAXR];
    unpackState(now, v);
    
    if(idx < 4) {
        // 横向0-4的左移
        v[idx] = getLeftShift( v[idx] );
    }else if(idx < 8) {
        // 横向0-4的右移
        v[idx-4] = getRightShift( v[idx-4] );
    }else if( idx < 14 ) {
        upDownShiftK(v, idx-8, 1);
    }else {
        upDownShiftK(v, idx-14, 0);
    }

    return packState(v);
}

void statePrint(int now) {
    int v[MAXR];
    unpackState(now, v);
    int i, j;
    for(i = 0; i < MAXR; i++) {
        for(j = 0; j < MAXC; j++) {
            int d = getBit(v[i], j);
            printf("%d", d);
        }
        puts("");
    }
}

int getInner1Count(int now) {
    int v[MAXR];
    unpackState(now, v);
    int i, j, c = 0;
    for(i = 1; i < MAXR-1; i++) {
        for(j = 1; j < MAXC-1; j++) {
            int d = getBit(v[i], j);
            c += d;
        }
    }    
    return c;
}

int endState() {
    int v[4] = {0, 30, 30, 0};
    return packState(v);
}

int n;
char str[MAXR][MAXC+1];


struct HashValue {
    int key, value;
    HashValue() {
    }
    HashValue(int _k, int _v) {
        key = _k;
        value = _v;
    }
}H[MOD+1];
int T;

int dis[MOD+1];

int stateCount;

int getHashCode(int v) {
    int s = v & MOD;
    while(1) {
        if(H[s].key != T) {
            H[s] = HashValue(T, v);
            stateCount++;
            return s;
        }else {
            if(H[s].value == v) {
                return s;
            }
            s ++;
            if(s >= MOD) s = 0;
        }
    }
}

int s[3];

void bfs() {
    memset(dis, -1, sizeof(dis));
    queue <int> Q;
    T++;
    // 从后往前搜 
    int now = endState();
    
    int codenow = getHashCode(now);

    Q.push(now);
    dis[codenow] = 0;

    while( !Q.empty() ) {
        now = Q.front();
        codenow = getHashCode(now);
        Q.pop();
        
        for(int i = 0; i < 20; i++) {
            int nex = stateTransform(now, i);
            
            if(nex == now) {
                continue;
            }
            
            int nex_code = getHashCode(nex);
            
            if(dis[nex_code] == -1) {
                dis[ nex_code ] = dis[codenow] + 1;
                Q.push( nex );
            }
        }
    }
    //printf("%d\n", stateCount);
}

void doColorSearch(int c, int & step) {
    int v[4];
    int i, j;
    for(i = 0; i < MAXR; i++) {
        v[i] = 0;
        for(j = 0; j < MAXC; j++) {
            int bit = colors[c] == str[i][j] ? 1 : 0;
            v[i] |= (bit * p2(j));
        }
    }
    int state = packState(v);
    state = getHashCode(state);
    
    if(dis[state] != -1 && dis[state] < step) {
        step = dis[state];
    }
}

int main() {
    bfs();
    
    int c, i, j;
    int t, cases = 0;
    
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < MAXR; i++) {
            scanf("%s", str[i]);
        }
        int step = 100000;
        for(c = 0; c < 3; c++) {
            doColorSearch(c, step);
        }
        printf("Case %d: %d\n", ++cases, step);
    }
    return 0;
}

/*
30
GWGGWW
BBBBBW
GBBBGW
WGGGWW

GWGGWW
BWBBBB
GBBBGW
WGGGWW

WWWWWW
BGGGGB
WGGGGW
BBBBBB

BGWBGW
BGWBGW
BGWBGW
BGWBGW

BGWBGW
BGWBGW
BGWBBW
BGWBGW


GBWBGW
BGWBGW
BGWBGW
BGWBGW

BGWBGW
BGWBGW
BGWBGW
BGWBGW

GBWBGW
BGWBGW
BGWBGW
BGWBGW

BGWBGW
BGWBGW
BGWBGW
BGWBGW

GBWBGW
BWBBGG
BGWWGW
BGWBGW

BGWBGW
BGWBGW
BGWBGW
BGWBGW

GBWBGW
BGWBGW
BGWBGW
BGWBGW

BGWBGW
BGWBGW
BGWBGW
BGWBGW

GBWBGW
WBGWBG
BGWBGW
BGWBGW

GWGWWB
GBWGBW
BWGBWG
WBBGGB
*/
