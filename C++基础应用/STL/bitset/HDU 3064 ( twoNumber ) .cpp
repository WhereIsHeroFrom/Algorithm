#include <iostream>
#include <bitset>
using namespace std;

bitset<1000001> f;
int n;
int st, end;

int main() {
    while(scanf("%d", &n) != EOF) {
        scanf("%d %d", &st, &end);
        f.reset();
        while(n--) {
            int x, y;
            scanf("%d %d", &x, &y);
            for(int i = x; i <= y; i++) {
                f[i] = 1;
            }
        }
        int bf = 0;
        for(int i = st; i <= end; i++) {
            if(f[i] != 1) {
                if(bf) printf(" ");
                bf = 1;
                printf("%d", i);
            }
        }
        puts("");
    }
    return 0;
}
