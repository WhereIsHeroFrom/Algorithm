#include <iostream>
#include <algorithm>
using namespace std;

int t;

struct Triple {
    int buy;
    int price;
    int sell;
    int index;
}p[100010];

int n;
int c[100010];
int val[100010];
int cmp(Triple a, Triple b) {
    return b.price < a.price;
}

int i, j;

int lowbit(int u) {
    return u & (-u);
}

void add(int u, int buy) {
    while(u <= 100000) {
        c[u] += buy;
        u += lowbit(u);
    }
}

int Sum(int u) {
    int sum = 0;
    while(u > 0) {
        sum += c[u];
        u -= lowbit(u);
    }
    return sum;
}

int main() {

    scanf("%d", &t);
    while( t-- ) {
        scanf("%d", &n);
        memset(c, 0, sizeof(c));
        for(i = 0; i < n ; i++) {
            scanf("%d %d %d", &p[i].buy, &p[i].price, &p[i].sell);
            p[i].index = i + 1;
            add( p[i].index, p[i].buy );
            val[ i+1 ] = p[i].buy;
        }

        sort(p, p+n, cmp);

        int sum = 0;
        for(i = 0; i < n; i++) {
            int buf = Sum( p[i].index );
            if(buf >= p[i].sell) {
                sum += p[i].price * p[i].sell;
                buf = p[i].sell;
            }else {
                sum += p[i].price * buf;
            }

            for(j = p[i].index; j >= 1; j--) {
                if(val[j] >= buf) {
                    val[j] -= buf;
                    add(j, -buf);
                    break;
                }else {
                    buf -= val[j];
                    add(j, -val[j]);
                    val[j] = 0;
                }    
            }
        }

        printf("%d\n", sum);
    }
}
