#include <iostream>

using namespace std;

char str[1000000];

class infos {
public:
    int cnt;
    int val;
    infos() {
        cnt = val = 0;
    }

    infos cmpinfos(const infos& other) {
        infos ret;
        if( val > other.val ) {
            ret.val = val;
            ret.cnt = (cnt + other.cnt) + cnt;
        }else {
            ret.val = other.val;
            ret.cnt = (cnt + other.cnt) + other.cnt;            
        }
        return ret;
    }

    void add(const infos& other) {
        val += other.val;
        cnt += other.cnt;
    }
};

int isNumber(char c) {
    return c >= '0' && c <= '9';
}


infos dfs(int& pos) {
    
    infos left, right;
    bool isleft = true;

    for(int i = pos; i < strlen(str); i ++) {
        if(str[i] == 'M') {
            // 进入递归
            pos = i+4;    // ignore 'MAX('
            infos t = dfs(pos);

            if( isleft ) {
                left.add(t);
            }else {
                right.add(t);
            }
            i = pos;
        }else if( str[i] == ')' ) {
            // 回溯
            pos = i;
            return left.cmpinfos(right);
        }else if(str[i] == ',') {
            isleft = false;
        }else if( str[i] == '+' ) {
            if( isleft ) {
                left.cnt++;
            }else {
                right.cnt++;
            }            
        }else if( str[i] >= '0' && str[i] <= '9' ) {
            int val;
            sscanf(&str[i], "%d", &val);
            while( isNumber(str[i]) ) i++;
            i--;
            if( isleft ) {
                left.val += val;
            }else {
                right.val += val;
            }
        }
    }
    if( isleft ) return left;
    
    return left.cmpinfos(right);
}

int main() {
    int t;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%s", str);
        int pos = 0;
        infos x = dfs( pos );
        printf("%d %d\n", x.val, x.cnt);
    }    
    return 0;
}


/*
6
MAX(1,0)
1+MAX(1,0)
MAX(2+1,3)
MAX(4,2+2)
MAX(1+1,2)+MAX(2,3)
MAX(MAX(1+2,3),MAX(4+5+6,MAX(7+8,9)))+MAX(10,MAX(MAX(11,12),13))
*/

