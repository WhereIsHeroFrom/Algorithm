#include <iostream>

using namespace std;

int s, a;
int n, i;

int main() {
    int t;
    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &n);
        a = 0;
        for( i = 0; i < n; i ++ ) {
            scanf("%d", &s );
            if( s % 4 == 3 )
                s ++;
            else if( s % 4 == 0 )
                s --;
            a ^= s; 
        }
        printf("%s\n", a ? "Alice" : "Bob" );
    }
    return 0;
}

