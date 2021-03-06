#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 100010

LL GCD(LL a, LL b) {
    return b ? GCD(b, a%b) : a;
}

int n;
double d;
int b[1010];

int main() {
    int t,i;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf %d", &d, &n);
        int V = int((d + 1e-6) * 100);
        LL G = 0;
        for(i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
            G = GCD(b[i], G);
        }
        while(G % 2 == 0) G /= 2;
        while(V % 2 == 0) V /= 2;
        if(V % (25*G) == 0) {
            printf("yes\n");
        }else {
            printf("no\n");
        }
        
    } 
    return 0;
}

