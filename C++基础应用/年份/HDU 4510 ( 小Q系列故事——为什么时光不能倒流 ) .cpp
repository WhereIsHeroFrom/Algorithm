#include <iostream>

using namespace std;

char str1[100], str2[100];
const int MOD = 60*60*24;

int val(char *str) {
    int x, y, z;
    sscanf(str, "%d:%d:%d", &x, &y, &z);
    return x*60*60+y*60+z;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", str1, str2);
        int v = ((val(str1) - val(str2)) % MOD + MOD) % MOD;
        int h = v/3600;
        int m = (v - h*3600) / 60;
        int s = v - h*3600 - m*60;
        if(h >= 12) {
            h -= 12;
        }
        printf("%02d:%02d:%02d\n", h, m, s);
    }
    return 0;
} 
/*
10
05:00:00 04:59:59
*/
