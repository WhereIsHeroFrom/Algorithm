#include <iostream>
#include <algorithm>
using namespace std;

int a[110];
int n;
int main() {
    int t;
    int i;
    scanf("%d", &t); 
    while(t--) {
        scanf("%d", &n);
        int pre = 0;
        int sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a + n);
        for(i = 0; i < n; i++) {
            if(a[i] > pre) {
                sum += (a[i] - pre) * 6;
                sum += 5;
                ++sum;
            }else if(a[i] == pre) {
                ++sum;
            }
            pre = a[i]; 
        }
        sum += pre * 4;
        printf("%d\n", sum);
    } 
    return 0;
}
