#include <iostream>
#include <algorithm>
using namespace std;

char str[100];

int main() {
    int t;
    int c;
    scanf("%d", &t);
    
    while(t--) {
        scanf("%d %s", &c, str);
        int i, j;
        int len = strlen(str);
        for(i = len-1; i >= 0; i--) {
            int minBig = -1;
            for(j = i+1; j < len; j++) {
                if(str[j] >str[i]) {
                    if(minBig == -1 || str[j] < str[ minBig ]) {
                        minBig = j;
                    }
                }
            }
            if(minBig != -1) {
                char ch = str[ minBig ];
                str[ minBig ] = str[i];
                str[i] = ch;
                sort( str+i+1, str+len );
                break;
            }
        }
        printf("%d ", c);
        if(i == -1) {
            printf("BIGGEST\n");
        }else {
            printf("%s\n", str);
        }
    }
    
    return 0;
}

