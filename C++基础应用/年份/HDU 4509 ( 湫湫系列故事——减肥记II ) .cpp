#include <iostream>
#include <cstring>
using namespace std;

char str1[100], str2[100];
int Time[24*60+1];

int v(char *str) {
    int x, y;
    sscanf(str, "%d:%d", &x, &y);
    return x * 60 + y;
}

int main() {
    int n;
    int i;
    while(scanf("%d", &n) != EOF) {
        memset(Time, 0, sizeof(Time));
        for(i = 0; i < n; i++) {
            scanf("%s %s", str1, str2);
            int x, y;
            x = v(str1);
            y = v(str2);
            ++Time[x];
            --Time[y];
        }
        int sum = 0;
        int ans = 1440;
        for(i = 0; i < 1440; ++i) {
            sum += Time[i];
            if(sum > 0) {
                --ans;
            }
        }
        printf("%d\n", ans);
        
    }
    return 0;
} 
