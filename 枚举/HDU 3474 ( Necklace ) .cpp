#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1000010

char str[2*MAXN];
int len;

struct Item {
    int val, index;
    
    Item() {
    }
    
    Item(int _v, int _i) {
        val = _v;
        index = _i;
    }
};

int front, rear;
Item Q[2*MAXN];
int visit[MAXN];

int getval(char c) {
    return c == 'C' ? 1 : -1;
}

// 左游标向右移 
void slideLeft(int& l, int& r, int& sumv, int& fixv ) {
    // 左游标右移的两个条件： 
    // con1. r - l == len
    // con2. sumv < 0
    do{
        sumv -= getval( str[l] );
        fixv += getval( str[l] );
        l++;
        
        // 单调队列里面存的值的下标范围一定是在[l, r]上的 
        while( front < rear && l > Q[front].index ) {
            front++;
        }
    }while( front < rear && Q[front].val - fixv < 0 && l < len );
}
 
void getCount(int reverse) {
    int i;
    int l = 0, r = 0;
    int sumv = 0, fixv = 0;
    front = rear = 0;
    
    while(l < len) {
        if(r - l == len) {
            // hash 切断位置 
            if(reverse) {
                if(l) {
                    visit[len-l] = 1;
                }else {
                    visit[0] = 1;
                }
            }else {
                visit[l] = 1;
            } 
            slideLeft(l, r, sumv, fixv);
            if( l >= len ) break;
        }
        
        sumv += getval( str[r] );
        while( front < rear && sumv + fixv <= Q[rear-1].val ) {
            rear --;
        }
        Q[rear++] = Item(sumv + fixv, r++);
        if(sumv < 0) {
            slideLeft(l, r, sumv, fixv);
        }
    }
}

void reserveStr() {
    for(int i = 0; i < len; i++) {
        char c = str[i];
        str[i] = str[2*len-1-i];
        str[2*len-1-i] = c; 
    }    
}

int calcTest() {
    int i, j;
    int ans = 0;
    for(i = 0; i < len; i++) {
        int s = 0;
        for(j = i; j < i + len; j++) {
            s += getval(str[j]);
            if(s < 0) break;
        }
        if(j == i+len) ans ++;
    }
    return ans;
}

int main() {
    int i, t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        //scanf("%d", &len);
        scanf("%s", str);
        //for(i = 0;i < len; i++) str[i] = rand()<100000?'C' : 'J';
        len = strlen(str);

        for(i = 0; i < len; i++) {
            str[i+len] = str[i];
            visit[i] = 0;
        }
        str[2*len] = '\0';
        getCount(0);
        reserveStr();
        getCount(1);
        int ans = 0;
        for(i = 0;i < len; i++) ans += visit[i];
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}

/*
10
CCJJCJC
CJCJJCC
CJCJCJ
CCJJCCJJCCJJCCJJ
CJJCCCJC
CJCCCJJC
*/

