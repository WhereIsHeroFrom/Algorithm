#include <iostream>

using namespace std;


#define MAXN 200000

int pre[MAXN];
int sum[MAXN], down[MAXN];

int unionset_find(int p) {
    int x = p;
    int sumd = 0; 
    while(pre[p] != p) {
        sumd += down[p];
        p = pre[p];
    }

    while(x != p) {
        int tmp = pre[x];
        pre[x] = p;
        sumd -= down[x];
        down[x] += sumd;
        x = tmp;
    }
    return p;
}

int unionset_union(int x, int y) {
    int fx = unionset_find(x);
    int fy = unionset_find(y);
    if(fx == fy) {
        return false;
    }else {
        pre[fx] = fy;
        down[fx] = sum[fy];
        sum[fy] += sum[fx];
        return true;
    }
}

int get_down(int p) {
    int s = 0;
    while(pre[p] != p) {
        s += down[p];
        p = pre[p];
    }
    return s;
}

int main() {
    int i, j;
    int n, P;
    while( scanf("%d", &P) != EOF ) {
        for(i = 0; i <= 30000; i++) {
            pre[i] = i;
            sum[i] = 1;
            down[i] = 0;
        }
        for(i = 0; i < P; i++) {
            char str[10];
            int x, y;
            scanf("%s", str);
            if(str[0] == 'M') {
                scanf("%d %d", &x, &y);
                unionset_union(x, y);
                /*for(j = 1; j <= 10; j++) {
                    printf("%d ", get_down(j) );
                }
                puts("");*/
            }else {
                scanf("%d", &x);
                printf("%d\n", get_down(x));
            }
        }
        
    }
    return 0;
}