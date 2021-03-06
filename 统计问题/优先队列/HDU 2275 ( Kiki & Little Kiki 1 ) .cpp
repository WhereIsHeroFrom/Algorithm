#include <iostream>
#include <queue>
using namespace std;


struct MinQ {
    int v;
    friend bool operator < (MinQ a, MinQ b) {
        return a.v > b.v;
    }
}temp1, temp2;

struct MaxQ {
    int v;
    friend bool operator < (MaxQ a, MaxQ b) {
        return a.v < b.v;
    }
}tt1, tt2;

priority_queue < MinQ > Min;
priority_queue < MaxQ > Max;

char str[10];
int m;

int main() {
    int n;

    while(scanf("%d", &n) != EOF) {
        
        while(!Min.empty())
            Min.pop();
        
        while(!Max.empty())
            Max.pop();

        while(n --) {
            scanf("%s %d", str, &temp1.v);

            if( strcmp(str, "Push") == 0 )
                Min.push( temp1 );
            else {
                while( !Min.empty() ) {
                    temp2 = Min.top();

                    if( temp2.v > temp1.v )
                        break;

                    Min.pop();
                    tt2.v = temp2.v;
                    Max.push( tt2 );
                }

                if(Max.empty())
                    printf("No Element!\n");
                else {
                    tt1 = Max.top();
                    printf("%d\n", tt1.v);
                    Max.pop();
                }
            }
        } 

        puts("");
    }
    return 0;
}
