#include <iostream>

using namespace std;

struct point {
    char name[30];
    char size[30];
    int price;
    int quality;
}p[10000];

int n, b;

int cmp(const void *a, const void *b) {
    point *c = (point *)a;
    point *d = (point *)b;
    return strcmp( c->name, d->name );
}

int low, high, mid;


int Fit( int key ) {
    int i;
    int rt = 0, Min = 2000000000;
    if(p[0].quality >= key) {
        Min = p[0].price;
    }
    for(i = 1; i < n; i++) {
        if( strcmp( p[i].name, p[i-1].name) ) {
            if( Min > b)
                return 0;
            rt += Min;
            if( rt > b )
                return 0;
            Min = 2000000000;
            if(p[i].quality >= key) {
                Min = p[i].price;
            }
        }else {
            if( p[i].price < Min && p[i].quality >= key) {
                Min = p[i].price;
            }
        }
    }

    if(Min > b)
        return 0;
    rt += Min;
    if( rt > b)
        return 0;
    return 1;
}
int main() {
    int t;
    scanf("%d", &t);

    int i;
    while( t-- ) {
        scanf("%d %d", &n, &b);
        for(i = 0; i < n; i++) {
            scanf("%s %s %d %d", p[i].name, p[i].size, &p[i].price, &p[i].quality);
        }

        qsort( p, n, sizeof( point ), cmp);

        low = 0;
        high = 1000000000;

        while( low < high ) {
            mid = ( low + high ) / 2;
            if( Fit(mid) ) 
                low = mid + 1;
            else
                high = mid - 1;
        }

        int op = mid + 3;

        for(i = op; i >= op - 6 &&  i >= 0; i--) {
            if( Fit(i) )
                break;
        }

        printf("%d\n", i);
    }
}
