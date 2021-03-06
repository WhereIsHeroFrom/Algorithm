#include <iostream>

using namespace std;

char str[ 10000 ];
int hash[ 300 ];
int RT[ 300 ];
int i, j;
int n;

int main() { 
    int t;
    scanf("%d", &t);

    while( t-- ) {

        memset( hash, 0, sizeof( hash ));
        scanf("%s", str);
        for(j = 0; str[j]; j++) {
            hash[ str[j] ] ++;
        }
        scanf("%d", &n);

        while( n-- ) {
            memset( RT, 0, sizeof( RT ));
            scanf("%s", str);
            for(i = 0; str[i]; i++) {
                RT[ str[i] ] ++;
                if( RT[ str[i] ] > hash[ str[i] ] )
                    break;
            }

            if( str[i] == '\0' )
                printf("YES\n");
            else
                printf("NO\n");
        }

    }
    return 0;
}
