#include <iostream>

using namespace std;

#define MAXN 100010

int pre[MAXN][3];
int nex[MAXN][3];

int monthDay[13] = {
    0,
    31, 28, 31, 30, 31, 30, 
    31, 31, 30, 31, 30, 31, 
};

bool isLeapYear(int y) {
    return y % 4 == 0 && y % 100 || y % 400 == 0;    
}

bool isValidDay(int y, int m, int d) {
    if(d <= 0) {
        return false;
    }
    int dv = isLeapYear(y) ? 1 : 0;
    if(m == 2) {
        if(d > dv + monthDay[m]) {
            return false;
        }
    }else {
        if(d > monthDay[m]) {
            return false;
        }
    }
    return true;
}

int main() {
    int i;
    int year, month, day;
    year = 2013;
    month = 3;
    day = 24; 
    for(i = 1; i < MAXN; i++) {
        ++day;
        while(1) {
            if( isValidDay(year, month, day) ) {
                nex[i][0] = year;
                nex[i][1] = month;
                nex[i][2] = day;
                break;
            }else {
                day = 1;
                ++month;
                if(month > 12) {
                    month = 1;
                    ++year;
                }
            }
        }
    }
    
    year = 2013;
    month = 3;
    day = 24;
    for(i = 1; i < MAXN; i++) {
        --day;
        while(1) {
            if( isValidDay(year, month, day) ) {
                pre[i][0] = year;
                pre[i][1] = month;
                pre[i][2] = day;
                break;
            }else {
                if(month == 1) {
                    --year;
                    month = 12;
                    day = monthDay[month];
                }else if(month == 3) {
                    --month;
                    day = monthDay[month];
                    if(isLeapYear(year)) {
                        day ++;
                    }
                }else {
                    --month;
                    day = monthDay[month];
                }
            }
        }
    }
    int D;
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &D);
        printf("%d/%02d/%02d %d/%02d/%02d\n", nex[D][0], nex[D][1], nex[D][2], pre[D][0], pre[D][1], pre[D][2]);
    }
    return 0;
} 
