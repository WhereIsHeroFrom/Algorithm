#include <iostream>

using namespace std;

char str[100];

char changeUpper(char c) {
    if(c >= 'A' && c <= 'Z') return c;
    return c - 'a' + 'A';
}

char changeLower(char c) {
    if(c >= 'a' && c <= 'z') return c;
    return c - 'A' + 'a';
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        int i = 0;
        while(str[i]) {
            if(str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' ||
               str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u') {
                   str[i] = changeUpper(str[i]);
            }else {
                str[i] = changeLower(str[i]);
            }
            ++i;
        }
        puts(str);
    }
    return 0; 
}
