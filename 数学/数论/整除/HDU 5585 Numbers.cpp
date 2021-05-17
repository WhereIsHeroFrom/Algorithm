#include <iostream>

using namespace std;

char s[1010];

int main() {
    while(scanf("%s", s) != EOF) {
        int sum = 0;
        char last = 0;
        for(int i = 0; s[i]; ++i) {
            sum += s[i] - '0';
            last = s[i];
        }
        if(sum%3 == 0 || (last-'0')%2 == 0 || (last-'0')%5 == 0) {
            puts("YES");
        }else {
            puts("NO");
        }
    }    
    return 0;
} 
