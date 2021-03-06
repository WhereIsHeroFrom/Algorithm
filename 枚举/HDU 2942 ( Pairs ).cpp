#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 110
#define MAXV 100010

int a[MAXN], sum;
int n;

bool solve() {
    if(n & 1) {
        return false;
    }
    int sum = a[0] + a[n-1];
    for(int i = 0; i < n/2; i++) {
        if(a[i] + a[n-i-1] != sum) {
            return false;
        }
    }
    return true;
}
 
int main() {
    int i;
    while(scanf("%d", &n) != EOF && n) {
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        printf("%s\n", solve() ? "Yes": "No");
    }
    return 0;
}
