#include <iostream>

using namespace std;

int hash[10000];
int i;
char str[10000], ch[10000];

int main() {
    while( gets(ch) ) {
        memset(hash, 0, sizeof(hash));
        int len = strlen( ch );

        int top = 0;
        for(i = 0; i < len; i++) {
            if(ch[i] != ' ')
                str[ top++ ] = ch[i];
        }        

        len = top;


        for(i = 0; i < len; i++) {
            if(!hash[i] && ( i + 1 ) % 3 == 0 ) {
                hash[ i ] = 1;
                printf("%c", str[i]);
            }
        }
        for(i = 0; i < len; i++) {
            if(!hash[i] && ( i + 1 ) % 2 == 0 ) {
                hash[ i ] = 1;
                printf("%c", str[i]);
            }
        }    
        for(i = 0; i < len; i++) {
            if(!hash[i] ) {
                hash[ i ] = 1;
                printf("%c", str[i]);
            }
        }

        puts("");
    }
}
